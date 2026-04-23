# aider

`aider` 是目前公认最强的终端 AI 编程助手，它能直接理解你的本地代码库并自动修改代码、提交 Git。

针对你正在进行的 **嵌入式驱动开发（C 语言/内核/U-Boot）**，以下是完整的环境配置指南：

## 安装

```bash
python -m pip install aider-install
aider-install
```

## 对接LLMs

### OpenRouter

```bash
export OPENROUTER_API_KEY=<key> # Mac/Linux
setx   OPENROUTER_API_KEY <key> # Windows, restart shell after setx

aider --list-models openrouter
```

### GitHub Copilot

```bash
# macOS/Linux
export OPENAI_API_BASE=https://api.githubcopilot.com
export OPENAI_API_KEY=<oauth_token>

# Windows (PowerShell)
setx OPENAI_API_BASE https://api.githubcopilot.com
setx OPENAI_API_KEY  <oauth_token>
# …restart the shell after setx commands

# oauth_token 获取
~/.config/github-copilot/apps.json
~\AppData\Local\github-copilot\apps.json


# 查询支持模型
curl -s https://api.githubcopilot.com/models \
  -H "Authorization: Bearer $OPENAI_API_KEY" \
  -H "Content-Type: application/json" \
  -H "Copilot-Integration-Id: vscode-chat" | jq -r '.data[].id'

```

## 配置文件

```bash
project/.aider.conf.yml
~/.aider.conf.yml
```

### 配置项说明

| 参数             | **类型** | **含义&技巧**      | **示例** |
| ---------------- | -------- | ------------------ | -------- |
| **model**        | 字符串   | 模型选择           |          |
| **auto-commits** | bool     | 自动commit消息模板 | true     |

参考

```yaml
# ~/.aider.conf.yml（复制粘贴，重启 Aider）
model: qwen2.5-coder:72b # 免费国产 GPT-4o
api-base: https://dashscope.aliyuncs.com/compatible-mode/v1
api-key: $DASHSCOPE_API_KEY # 环境变量

# Git 自动化（生产力核心）
auto-commits: true
auto-commits-message: "feat: {{changes}} by Aider ({{model}})"
message-match: "aider:"

# 文件过滤（Python 项目）
include:
  - "*.py"
  - "*.md"
exclude:
  - "**/__pycache__/**"
  - "tests/**"

# LLM 调优（代码质量+）
temperature: 0.1
top-p: 0.9
max-tokens: 8192

# Ooutput settings

## Use colors suitable for a dark terminal background (default: False)
dark-mode: false

## Use colors suitable for a light terminal background (default: False)
light-mode: false

## Enable/disable pretty, colorized output (default: True)
pretty: true # Rich 高亮

## Enable/disable streaming responses (default: True)
stream: true

verbose: true # 调试日志
```

### 常用快捷指令

在 `aider` 的对话框内：

- `/add <file>`: 添加文件到对话（让 AI 看得见）。
- `/drop <file>`: 从对话中移除文件（节省 Token）。
- `/git`: 执行 git 命令。
- `/undo`: **神器！** 撤销上一次 AI 的修改和 Commit（写错代码瞬间恢复）。
- `/exit`: 退出。

### 控制简体中文
