---
name: memory-check
description: Analyze C/C++ codebase for memory leaks, buffer overflows, use-after-free, null pointer dereferences, and other memory-safety bugs. Produces a structured report with severity ratings and fix suggestions.
user-invocable: true
---

# Memory Safety Check

Systematically analyze C/C++ source files for memory leaks and segmentation fault risks.

## Analysis Process

### Step 1: Scope Discovery
- List all `.c`, `.h`, `.cpp`, `.hpp` source files (excluding `deps/`, `build_*`, `output/`)
- Identify the core implementation files — focus analysis there
- Note the project structure: headers, source, tests, third-party libs

### Step 2: Systematic Review

Read every core source file and check each function for the following patterns:

#### A. Memory Leaks (every `malloc`/`calloc`/`realloc` must have a matching `free`)

For each allocation, trace ALL exit paths from the function:
1. Normal return path — is `free()` called?
2. Early return on error — is `free()` called?
3. `break`/`goto` out of loops — is `free()` called?
4. **Configuration failure after allocation** — common leak pattern: allocate → load config → config invalid → return error WITHOUT freeing
5. **Re-initialization** — is a previously allocated global/static pointer overwritten without `free()`?

Flag pattern:
```c
ptr = calloc(1, size);
// ... work ...
if (config_invalid) {
    ret = -1;
    break;  // ⚠️ ptr not freed
}
```

#### B. Buffer Overflows (writing beyond allocated bounds)

1. **Stack buffers**: check all array accesses against declared size

2. **Heap buffers**: for each `malloc(N)`, verify all writes stay within `[0, N-1]`

3. **Functions without size info**: `strcpy`, `strcat`, `sprintf` → should be `strncpy`, `snprintf`

4. **`strncpy` non-null-termination**: `strncpy(dst, src, n)` does NOT null-terminate if `strlen(src) >= n`. Flag all `strncpy` call sites — verify the destination is either:
   - Previously `memset`-zeroed AND source length < n, OR
   - Explicitly null-terminated after the call

5. **Multi-region buffer arithmetic**: when a single allocation is partitioned into multiple regions, verify each region's size suffices for what gets written into it. Compute actual sizes:
   ```
   PKCS5_PAD_LEN(n)  = ((n)/16 + 1) * 16
   BASE64_ENC_MAX(n) = ((n) + 2) / 3 * 4
   DOUBLE_B64_MAX(n) = BASE64_ENC_MAX(BASE64_ENC_MAX(n))
   ```

6. **Base64 decode output**: `base64_decode` output is ~3/4 of input size — ensure output buffer is large enough

#### C. Null Pointer Dereference

1. Check all pointer parameters — are they validated before use?
2. Check all function return values (`malloc`, `fopen`, `cJSON_GetObjectItem`, etc.)
3. **`cJSON_GetObjectItem` → `->valuestring` chains**: each step can return NULL
4. **Macros that dereference**: if a macro accesses a global pointer (e.g. `#define KEY (global_ptr->field)`), check that `global_ptr` is validated before the macro is expanded

#### D. Use-After-Free / Double-Free

1. After `free(ptr)`, is `ptr` ever dereferenced?
2. Can the same pointer be passed to `free()` twice?
3. In loops with `free()`, is there a path where `free` is called more than once on the same pointer?

#### E. Buffer Over-reads

1. `strcmp`/`strlen`/`printf("%s")` on buffers that may not be null-terminated
2. HTTP response buffers — responses may fill the entire buffer leaving no room for `\0`
3. Decrypted/decoded data — verify null termination is explicit

### Step 3: Compile Findings

For each confirmed issue, record:
- **Severity**: 🔴 Critical | 🟡 Medium | 🟢 Low
- **Category**: Memory Leak | Buffer Overflow | Null Deref | Use-After-Free | Double-Free | Buffer Over-read | Unsafe Pattern
- **Location**: `file:line`
- **Description**: what happens, with code snippet
- **Trigger condition**: when does the bug manifest
- **Fix**: concrete suggestion

### Step 4: Write Report

Write the report to the file specified by the user (default: `memory-check-report.md`).

Report structure:
```markdown
## 内存安全分析报告

### 🔴 严重问题
(each with code snippet, root cause, fix)

### 🟡 中等风险
(each with code snippet, root cause, fix)

### 🟢 低风险 / 代码质量
(each with code snippet, root cause, fix)

### 📊 汇总表
| 严重程度 | 类别 | 位置 | 描述 |
|---------|------|------|------|

### 修复优先级
(ordered list of concrete fixes)
```

## Checklist

Before finalizing the report, verify:
- [ ] Every `malloc`/`calloc`/`realloc` in core files has been traced to a `free`
- [ ] Every `strncpy` call site has been checked for null-termination
- [ ] Every `cJSON_GetObjectItem` → `->valuestring` chain has been checked
- [ ] All multi-region buffer layouts have had their sizes computed
- [ ] Every buffer receiving external data (HTTP, file, network) has been checked for overflow
