# skills

## brooks-lint

> 它本质上是一个 **Agent Skill 集合**，用 12 本经典软件工程书作为审查依据，对代码做架构、技术债、测试质量等检查。官方仓库目前有 **241 次 commits、68 forks**，并且仓库里明确包含 `.codex-plugin`。([GitHub][1])

### 1. 在 Codex 里安装

#### 方法 A：直接让 Codex 安装

进入 Codex CLI 后直接输入：

```text
Install the brooks-lint skill from hyhmrright/brooks-lint
```

官方 README 明确支持这种方式。([GitHub][2])

#### 方法 B：命令行安装

如果你的 Codex 已经有 `$skill-installer`，可以执行：

```bash
python3 ~/.codex/skills/.system/skill-installer/scripts/install-skill-from-github.py \
  --repo hyhmrright/brooks-lint \
  --path skills \
  --name brooks-lint
```

这是项目官方给出的 Codex 安装方式。([GitHub][2])

#### 方法 C：安装脚本

也可以：

```bash
git clone https://github.com/hyhmrright/brooks-lint.git /tmp/brooks-lint
cd /tmp/brooks-lint
./scripts/install.sh codex
```

项目的安装脚本会把 Skills 放到 Codex 的 Skills 目录。([GitHub][2])

---

### 2. 安装以后怎么用？

这是最重要的部分。

它提供 **6 个模式**：

| 命令             | 用途                |
| ---------------- | ------------------- |
| `$brooks-review` | Review PR / Diff    |
| `$brooks-audit`  | 架构审计            |
| `$brooks-debt`   | 技术债分析          |
| `$brooks-test`   | 测试质量分析        |
| `$brooks-health` | 综合健康度          |
| `$brooks-sweep`  | 全面扫描 + 自动修复 |

这些都是 Codex 官方 README 中列出的 Codex 调用方式。([GitHub][2])

---

### 3. 最推荐的用法：直接让它 Review

假设你现在就在项目目录：

```bash
cd my-project
codex
```

然后：

```text
$brooks-review
```

它会针对当前代码变更进行 Review。

也可以直接自然语言：

```text
Review this PR using brooks-lint.
```

或者：

```text
请使用 brooks-lint 审查当前 git diff。
重点关注架构、重复逻辑、依赖关系和测试问题。
```

官方说明里，Skills 也支持自然语言自动触发，例如：

> review this PR
> audit the architecture

([GitHub][2])

---

### 4. 如果你想检查整个项目

使用：

```text
$brooks-audit
```

它主要看**架构层面的问题**，包括：

- Cognitive Overload
- Change Propagation
- Knowledge Duplication
- Accidental Complexity
- Dependency Disorder
- Domain Model Distortion

也就是说，它不是传统意义上的：

```text
lint
↓
报错
↓
改格式
```

而更像：

```text
代码库
 ↓
理解架构
 ↓
寻找结构性衰退
 ↓
解释为什么是问题
 ↓
给出重构方案
```

这六类生产代码风险是项目自己定义的核心诊断维度。([GitHub][1])

---

### 5. 查技术债

运行：

```text
$brooks-debt
```

这个比较适合老项目。

例如：

```text
请运行 $brooks-debt，
分析当前项目最严重的技术债，
并按照风险和修改成本给出处理顺序。
```

它会把问题组织成：

**Symptom → Source → Consequence → Remedy**

也就是：

> 症状 → 根源 → 后果 → 对策

并附上对应工程书籍的依据。([GitHub][3])

---

### 6. 检查测试代码

运行：

```text
$brooks-test
```

它专门分析测试体系。

例如：

```text
$brooks-test

重点检查：
1. 测试是否真正验证行为
2. 是否存在脆弱测试
3. 是否存在重复测试
4. 测试结构是否容易维护
5. 哪些关键代码缺少测试
```

它使用的参考资料包括：

- _The Art of Unit Testing_
- _How Google Tests Software_
- _Working Effectively with Legacy Code_
- _xUnit Test Patterns_

([GitHub][1])

---

### 7. 最适合长期项目：`$brooks-health`

如果你第一次把它装进一个项目，我建议先运行：

```text
$brooks-health
```

它相当于做一个**整体健康检查**。

最终会给出：

```text
Health Score: XX/100
```

以及具体问题。

官方示例中，一个存在职责混杂、逻辑错误和 SQL 注入问题的示例代码得到 **28/100**，并逐项解释问题、来源、后果和修复建议。([GitHub][1])

---

### 8. `$brooks-sweep` 要谨慎

这个命令：

```text
$brooks-sweep
```

是六种模式里面最激进的。

它会：

> 全维度分析 + 自动修复 findings

所以我**不建议第一次就直接跑 sweep**。

更合理的流程：

```text
$brooks-health
       ↓
看问题
       ↓
$brooks-review
       ↓
选择需要处理的问题
       ↓
让 Codex 修改
       ↓
跑测试
       ↓
$brooks-sweep
       ↓
再次检查
```

官方也明确把 `sweep` 定义为 **full sweep + auto-fix**。([GitHub][2])

---

### 9. 我比较推荐的 Codex 工作流

如果你是拿 Codex 做实际项目开发，可以把它和普通 coding agent 分开：

```text
                 ┌──────────────┐
                 │   Codex      │
                 │  写/改代码    │
                 └──────┬───────┘
                        ↓
                 ┌──────────────┐
                 │  Playwright  │
                 │   测试/UI     │
                 └──────┬───────┘
                        ↓
                 ┌──────────────┐
                 │ Brooks-Lint  │
                 │ 代码质量/架构 │
                 └──────┬───────┘
                        ↓
                 ┌──────────────┐
                 │    Tests     │
                 │  回归验证     │
                 └──────────────┘
```

实际可以这样：

#### 开发前

```text
$brooks-health
```

了解代码库目前的健康状况。

#### 开发过程中

让 Codex 正常写代码。

#### 完成一个功能

```text
$brooks-review
```

检查当前 diff。

#### 大规模重构

```text
$brooks-audit
```

先看架构问题。

#### 老项目治理

```text
$brooks-debt
```

建立技术债路线图。

#### 最后

```text
$brooks-test
```

确认测试体系没有跟着重构一起恶化。

---

### 10. 它和普通 `lint` 最大的区别

这个名字很容易让人误解。

**brooks-lint ≠ ESLint / Ruff / golangci-lint。**

传统 lint 更偏：

```text
语法
格式
类型
静态规则
安全规则
```

而 brooks-lint 更偏：

```text
             代码
              ↓
        ┌─────────────┐
        │ 理解设计意图 │
        └──────┬──────┘
               ↓
       架构/维护性分析
               ↓
     ┌─────────┼─────────┐
     ↓         ↓         ↓
  复杂度     耦合      重复
     ↓         ↓         ↓
       长期维护风险
```

项目明确把自己定位为基于经典工程著作的 **AI code review / decay-risk diagnostics**，而不是传统静态 lint 工具。([GitHub][1])

#### 我建议你第一次这样试

在一个**已经有一定代码量的项目**里：

```text
$brooks-health
```

跑完后，把结果交给 Codex：

```text
根据刚才的 brooks-lint 结果，
不要一次性修改所有问题。

先选择影响最大的 3 个问题，
逐个给出修改方案。
每修改一个问题后运行相关测试，
确认通过后再继续。
```

这样比直接 `$brooks-sweep` 更容易控制修改范围，也更适合观察这个 Skill 到底有没有给你的项目带来实际价值。

[1]: https://github.com/hyhmrright/brooks-lint "GitHub - hyhmrright/brooks-lint: AI code reviews grounded in 12 classic engineering books — decay risk diagnostics with book citations, severity labels, and 6 analysis modes including full-sweep auto-fix · GitHub"
[2]: https://github.com/hyhmrright/brooks-lint?utm_source=chatgpt.com "GitHub - hyhmrright/brooks-lint: AI code reviews grounded in 12 classic engineering books — decay risk diagnostics with book citations, severity labels, and 6 analysis modes including full-sweep auto-fix · GitHub"
[3]: https://github.com/hyhmrright/brooks-lint/blob/main/README.zh-CN.md?utm_source=chatgpt.com "brooks-lint/README.zh-CN.md at main · hyhmrright/brooks-lint · GitHub"
