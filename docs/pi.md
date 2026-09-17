我整理了一份 Pi 和 Oh My Pi 的安装与使用文档，核心区别在于：**Pi 是极简的画布，Oh My Pi 是开箱即用的装甲车**。

### 🛠️ Pi 安装与使用

Pi 的哲学是“**Primitives, not features**”，默认只给模型 4 个工具，其余全凭你自行配置。

**安装**
推荐使用官方脚本或 npm 全局安装：

```bash
# 推荐方式
curl -fsSL https://pi.dev/install.sh | sh

# 或使用 npm (--ignore-scripts 更安全)
npm install -g --ignore-scripts @earendil-works/pi-coding-agent
```

安装后，在项目目录输入 `pi` 即可启动。

**配置模型**

- **订阅登录**：在 Pi 内运行 `/login`，可选择 Claude Pro/Max、ChatGPT Plus 或 GitHub Copilot 完成 OAuth 认证。
- **API Key**：直接设置环境变量，如 `export ANTHROPIC_API_KEY=sk-ant-...`，Pi 支持 15+ 家提供商。

**核心用法**
Pi 默认提供 `read`、`write`、`edit`、`bash` 四个工具，足以让模型通过 bash 调用系统命令完成大部分工作。

- **交互模式**：直接输入 `pi` 进入 TUI。常用快捷键：`Ctrl+L` 切换模型，`@文件名` 引用文件，`Ctrl+V` 粘贴图片。
- **单次执行**：适合脚本或 CI，例如 `pi -p "给这个函数加单元测试"`。
- **项目规则**：在项目根目录创建 `AGENTS.md`（或 `CLAUDE.md`）来定义项目规范，Pi 会自动加载。

### 🚀 Oh My Pi 安装与使用

Oh My Pi（`omp`）是 Pi 的增强分支，内置了 LSP、DAP、子代理等大量实用工具，实现“**电池已包含**”。

**安装**
需要 Bun >= 1.3.14，推荐官方脚本或 Bun 全局安装：

```bash
# 官方脚本
curl -fsSL https://omp.sh/install | sh

# 或使用 Bun
bun install -g @oh-my-pi/pi-coding-agent
```

安装后的命令为 `omp`。

**配置模型**
Oh My Pi 有自己的配置目录 `~/.omp`，与 Pi 相互独立。

- **环境变量**：支持约 40 个提供商，例如设置 `export ORCA_KEY="sk-orca-..."` 或 `export AI_GATEWAY_API_KEY="..."`。
- **指定模型启动**：使用 `provider/model` 格式，如 `omp --model vercel-ai-gateway/anthropic/claude-opus-5`。

**核心增强**

- **内置丰富工具**：自带 LSP（语义重命名）、DAP（真实调试器）、浏览器操作、子代理等 31+ 工具，无需自行组装。
- **Hashline 编辑**：用内容哈希锚点定位，大幅减少“字符串未找到”的编辑错误。
- **无缝迁移**：首次运行会自动读取 `.claude`、`.cursor`、`.codex` 等目录下的规则和 MCP 配置，无需手动迁移。

### 📊 关键差异速览

| 维度         | Pi                           | Oh My Pi (omp)                  |
| ------------ | ---------------------------- | ------------------------------- |
| **设计哲学** | 极简画布，按需扩展           | 全能装甲，开箱即用              |
| **默认工具** | 4 个（read/write/edit/bash） | 31+ 个（含 LSP、DAP、浏览器等） |
| **配置目录** | `~/.pi/`                     | `~/.omp/`                       |
| **编辑方式** | 基础文本替换                 | **Hashline 哈希锚点编辑**       |
| **配置迁移** | 需手动设置                   | **自动继承**现有 AI 工具配置    |
| **资源开销** | 轻量，Token 消耗低           | 较重，Token 消耗和成本更高      |

**简单选型建议**：如果你享受掌控感、想完全自定义工作流，选 **Pi**；如果你想要一个功能齐全、拿起就能干活的终端工作台，选 **Oh My Pi**。
