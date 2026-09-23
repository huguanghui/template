---
name: heap-analyze
description: 使用 pprof 分析 gperftools(tcmalloc) 采集的堆内存数据，对比两次快照定位内存泄漏和分配热点。
user-invocable: true
allowed-tools:
  - Bash(head *)
  - Bash(pprof *)
  - Bash(export PPROF_BINARY_PATH=*)
  - Bash(date *)
  - Bash(ls *)
  - Write
---

# /heap-analyze [heap1] [heap2] [--bin <path>] [--so <path>]

## 参数解析

Arguments: `$ARGUMENTS`

```
/heap-analyze res/prof.0004.heap res/prof.0017.heap
/heap-analyze res/prof.0004.heap
/heap-analyze res/prof.0004.heap --so output/ax615d_debug/lib
```

| 参数 | 默认值 |
|------|--------|
| `heap1` | 第 1 个无前缀参数；缺失则询问 |
| `heap2` | 第 2 个无前缀参数；缺失则单文件分析 |
| `--bin` | `output/ax615d_debug/bin/apps` |
| `--so` | `output/ax615d_debug/lib`   |

空 args 时走交互确认（复用上次分析的文件）。

## 流程

### 1. 确认输入 + 生成输出文件名

解析 args，提取进程名和 prof 标识用于文件命名：

```
进程名 = basename(--bin)                   # e.g. "apps"
prof标识 = basename(heap1 去 .heap 后缀)    # e.g. "prof.0004"
          [+ "-" + basename(heap2 去 .heap)] # e.g. "prof.0004-prof.0017"
时间戳 = date +%Y%m%d_%H%M%S
输出文件 = res/<进程名>_<prof标识>_<时间戳>.md
```

示例：`res/apps_prof.0004-prof.0017_20260702_113000.md`

### 2. 读取 heap 头部

```bash
head -1 <heap>
# heap profile: <inuse_objs>: <inuse_bytes> [<alloc_objs>: <alloc_bytes>] @ heapprofile
```

### 3. 运行分析

```bash
export PPROF_BINARY_PATH=<so_dir>
BIN=<bin>

pprof --text --inuse_space  $BIN <heap>
pprof --text --inuse_objects $BIN <heap>
pprof --text --alloc_space $BIN <heap>
```

两个文件时追加差异：

```bash
pprof --text --base=<heap1> --inuse_space  $BIN <heap2>
pprof --text --base=<heap1> --alloc_space $BIN <heap2>
```

### 4. 按需深入

对 flat/cum TOP1 函数：

```bash
pprof --list=<func> $BIN <heap2>
```

### 5. 输出结论

| 指标 | heap1 | heap2 | 变化 |
|------|-------|-------|------|
| inuse | X MB | Y MB | ±Z MB |
| alloc 累计 | X MB | Y MB | ±Z MB |

- inuse 增长 < 5% → 无明显泄漏
- alloc 量大 inuse 稳 → 高频分配/释放，建议内存池

**热点 TOP**（flat 排序）和**调用链**（cum 还原关键路径）。

### 6. 导出结果文件

将完整分析报告写入 `res/<进程名>_<prof标识>_<时间戳>.md`，用 markdown 格式，包含：

```markdown
# Heap 分析报告

- **进程**: <进程名>
- **二进制**: <bin>
- **Heap 文件**: <heap1> [, <heap2>]
- **分析时间**: <时间戳>

## 概要

| 指标 | ... | ... | 变化 |
|------|-----|-----|------|
| ...  |     |     |      |

## 常驻内存 (inuse_space)

... pprof 输出 ...

## 累计分配 (alloc_space)

... pprof 输出 ...

## 增长差异 (--base)

... diff 输出 ...

## 热点函数分析

... --list 输出 ...

## 结论与建议

...
```

## 速查

| 模式 | 用途 |
|------|------|
| `--inuse_space` | 当前未释放 → 查泄漏 |
| `--alloc_space` | 累计分配量 → 查热点 |
| `--base=A B` | B - A 增量 → 两快照差异 |
| `flat` | 函数自身分配 |
| `cum` | 函数+子调用 |
