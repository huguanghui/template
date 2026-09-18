# Codex

OpenAI 官方开源的终端编码 Agent（Codex CLI），用 Rust 实现，直接跑在本机：可读取仓库、修改文件、执行命令。
支持使用 ChatGPT 账号登录，也支持 API Key。

## 简介

- **定位**：OpenAI 生态的本地编码 Agent，速度快、Token 效率高，同时提供云端沙盒与后台任务。
- **模型**：主要使用 GPT-5.x Codex 系列，也可通过自定义 provider 接入兼容 OpenAI 接口的模型。
- **登录方式**：`Sign in with ChatGPT`（Plus / Pro / Business / Edu / Enterprise 套餐）或 API Key。
- **入口**：交互式 TUI `codex`、一次性执行 `codex exec`、云端任务 `codex cloud`。

## 安装

macOS / Linux 官方脚本：

```bash
curl -fsSL https://chatgpt.com/codex/install.sh | sh
```

包管理器：

```bash
# npm
npm install -g @openai/codex

# Homebrew
brew install --cask codex
```

Windows：使用官方提供的 PowerShell 安装脚本，或通过 WSL2 运行。

更新（脚本安装直接重跑安装命令即可）：

```bash
curl -fsSL https://chatgpt.com/codex/install.sh | sh
brew upgrade --cask codex
```

安装完成后运行 `codex`，按提示登录，或提前设置 `OPENAI_API_KEY`。

## 使用

### 交互模式

```bash
codex                        # 进入 TUI
codex "解释这个项目的结构"     # 带首轮提示进入
codex resume                 # 恢复历史会话
codex --image error.png      # 附带截图等多模态上下文
codex --search               # 开启实时联网搜索（默认走缓存）
```

常用交互命令：

| 命令           | 作用                                 |
| -------------- | ------------------------------------ |
| `/permissions` | 调整本次运行的沙盒与审批范围         |
| `/model`       | 切换模型与推理强度                   |
| `/approve`     | 重试一次被自动审查拒绝的操作         |
| `/raw`         | 切换 raw 滚动模式，方便复制（alt-r） |
| `/exit`        | 退出                                 |

### 非交互 / 脚本

`codex exec` 适合 CI、管道等无人值守场景，退出码可用于判断成败：

```bash
codex exec "给这个函数补单元测试"
codex exec --json "修复 lint 错误" --output-last-message result.txt
```

### 权限与沙盒

用 `--sandbox` 和 `--ask-for-approval` 控制自主程度：

```bash
# 低摩擦本地开发：可写工作区，需要时再询问
codex --sandbox workspace-write --ask-for-approval on-request

# 只读审查，不产生任何写入
codex --sandbox read-only
```

`sandbox` 取值：`read-only`、`workspace-write`、`danger-full-access`。

> 除非在专用沙盒 VM 内，否则不要使用 `--dangerously-bypass-approvals-and-sandbox`。

### 常用参数

| 参数                | 说明                                       |
| ------------------- | ------------------------------------------ |
| `-m, --model`       | 指定模型                                   |
| `--search`          | 开启实时联网搜索                           |
| `--image`           | 附带截图 / 架构图等多模态上下文             |
| `--add-dir`         | 追加可写的额外目录                         |
| `codex cloud`       | 浏览 / 提交 Codex 云端任务                 |
| `codex mcp`         | 管理本地或远程 MCP 服务器                  |

### 项目规则

在项目根目录放置 `AGENTS.md`，Codex 会自动读取作为项目规范（也可由 `CLAUDE.md` 迁移）。

### 配置文件

主配置位于 `~/.codex/config.toml`：

```toml
model = "gpt-5.5-codex" # 以官方文档当前可用模型为准
approval_policy = "on-request"
sandbox_mode = "workspace-write"

[history]
persistence = "save-all"

[tui]
theme = "catppuccin-mocha"
status_line = ["model", "token-usage", "git-branch"]
```

也可在命令行临时覆盖：

```bash
codex --config tui.alternate_screen=always
```

## 接入第三方模型 / OpenRouter

通过 OpenRouter 官方工具 `ori` 一键启动并复用账号下的全部模型：

```bash
ori codex
ori codex --model openai/gpt-5.2
ori codex --model google/gemini-3.6-flash --full-auto
```

## 开启终端全屏

Codex TUI 默认使用备用屏幕缓冲区（alternate screen）。`auto` 会在 Zellij 中跳过，以保留回滚历史。
需要强制全屏：

```toml
[tui]
alternate_screen = "always"
```

取值说明：

- `auto`（默认）：根据终端环境自动决定。
- `always`：始终使用备用屏幕，进入全屏。
- `never`：不使用备用屏幕，保留终端本身的回滚历史。

等效命令行参数 `codex --no-alt-screen`（需要在终端中保留历史输出时使用）。

> 在 tmux / Zellij 下若全屏后无法滚动回看历史，改用 `never` 即可。
