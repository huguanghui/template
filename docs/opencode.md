# Opencode

## opencode2

### 安装

```
curl -fsSL https://opencode.ai/v2/install | bash
```

### 配置方案

**1. `oh-my-opencode`：最出名的多 Agent 协作方案**
如果你想让 OpenCode 从“单打独斗”变成“团队协作”，这是目前社区里最主流的选择。它通过多个分工明确的 Agent（如探索、规划、审查）并行处理任务，能明显提升处理复杂需求时的稳定性和效率。`opencode-antigravity-config` 这个 GUI 安装器就集成了它，可以一键配置多模型策略。

**2. `znlgis/my-opencode-deepseek-config`：专注 DeepSeek 的固定模型方案**
如果你主要使用 DeepSeek，或者追求配置的极简和稳定，这个方案很值得参考。它锁定特定模型版本以保证输出稳定，并区分了“思考”与“快速”模型，配置结构清晰，适合直接拿来用。

**3. `Jonathan0823/opencode-config`：强调工作流控制的方案**
这个配置的核心是“审批优先”和“最小可行信息加载”。它内置了规划、实现、测试、审查等子代理，并强制在修改代码前先提出方案，适合对代码质量和流程规范要求较高的团队或个人。

**4. `markerikson/opencode-config-example`：来自资深开发者的日常参考**
这是作者日常在用的配置清理后的版本，包含了完整的 `AGENTS.md`、子代理定义、自定义命令和技能库。如果你想看看一个“真实生产力环境”下的 OpenCode 可以配置到什么程度，这是一个很好的学习样本。

### 如何选择

这些方案没有绝对的好坏，关键看你的场景：

- **想体验多 Agent 协作**：优先看 `oh-my-opencode`。
- **主用 DeepSeek，想要稳定省心**：直接参考 `znlgis` 的配置。
- **重视流程规范和代码审查**：`Jonathan0823` 的方案更合适。
- **想学习高级用法，自己定制**：从 `markerikson` 的示例入手。

### 启用LSP

### WebUI使用

```bash
OPENCODE_SERVER_PASSWORD=12345678 opencode2 serve --port 4096 --hostname 0.0.0.0
```
