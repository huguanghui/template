# ClaudeAI

Claude CLI（命令行界面）是开发者提高生产力的利器，尤其是在你处理代码、日志分析和自动化脚本时。

## 相关链接

[reddit话题](https://www.reddit.com/r/ClaudeAI/)
[中文社区](https://claudecn.com/)

---

## 相关技巧

目前主流的 Claude CLI 使用方式有两种：一种是 **Anthropic 官方提供的 SDK/CLI**，另一种是社区广受好评的 **Aider**（专门针对编程）.
以下是针对开发者（特别是像你这样涉及内核、驱动开发的工程师）的实用技巧：

### 1. 核心技巧：管道（Piping）与重定向

这是 CLI 最大的优势。你可以直接将代码、日志或命令输出通过管道传给 Claude，而无需手动复制粘贴。

- **分析内核日志**：

  ```bash
  dmesg | claude "分析这个内核日志中的报错原因，并给出修复建议"
  ```

- **解释复杂的 C 函数**：

  ```bash
  cat drivers/gpio/gpio-axera.c | claude "解释这个驱动的初始化逻辑"
  ```

- **格式化输出并保存**：

  ```bash
  claude "写一个读取 /proc/adc 的 shell 脚本" > test_adc.sh
  ```

---

### 2. 使用 System Prompt 设定“专家身份”

在 CLI 中，你可以通过参数快速切换 Claude 的“大脑”模式。

- **设定为内核专家**：

  ```bash
  claude --system "你是一名精通 Linux Kernel 5.10 的嵌入式驱动工程师，回答尽量简练，多给代码示例" -p "如何实现一个字符设备驱动？"
  ```

---

### 3. 多文件上下文（Context）管理

如果你在调试 `board_init` 相关的 Bug，可能需要同时让 Claude 看到多个文件。

- **读取多个文件**：

  ```bash
  claude -f board.c -f memory.h "检查这两个文件中的 GPIO 定义是否冲突"
  ```

---

### 4. 结合 `Aider` 进行“结对编程”

如果你在做深度的代码重构或 Bug 修复，强烈建议使用基于 Claude 3.5 Sonnet 的 **Aider**。它是目前最强的编程 CLI 工具。

- **安装**：`pip install aider-chat`
- **使用技巧**：
  - 在 Git 项目目录下直接运行 `aider`。
  - 使用 `/add <filename>` 把相关代码加入上下文。
  - **直接让它改代码**：`"把 board_init 里的所有 gpio_set_value 换成 gpio_direction_output"`。它会自动帮你写好代码并**自动提交 Git Commit**。

---

### 5. 自定义别名（Aliases）提高效率

在你的 `~/.bashrc` 或 `~/.zshrc` 中添加一些高频使用的短命令：

```bash
# 解释代码
alias cl-explain='claude "请详细解释以下代码的逻辑："'

# 优化代码
alias cl-opt='claude "请重构并优化这段代码的性能和可读性："'

# 检查日志错误
alias cl-check='claude "请找出这段日志中的所有 Error 和 Warning，并分析原因："'
```

使用时只需：`cat main.c | cl-explain`

---

### 6. 模型切换（省钱与提速）

根据任务复杂度切换模型：

- **Claude 3.5 Sonnet**（默认/推荐）：用于写代码、逻辑推理。
- **Claude 3 Haiku**：用于简单的格式转换、文本翻译、提取关键词（速度极快且极其便宜）。
  - 命令：`claude --model claude-3-haiku-20240307`

---

### 7. 结合 Shell 变量处理动态任务

你可以编写一个简单的脚本来自动化任务：

```bash
#!/bin/bash
# 自动分析最近 50 行内核打印并给出建议
LOG=$(dmesg | tail -n 50)
claude "以下是最近的内核日志：$LOG。请判断系统是否稳定。"
```

---

### 8. 进阶：处理 Token 限制

如果你处理的是巨大的驱动文件，直接输入可能会超过 Context Window（虽然 Claude 现在支持 200k，但一次性传太多会变慢或变贵）。

- **技巧**：使用 `grep` 或 `sed` 截取关键代码段再传入。

  ```bash
  sed -n '100,200p' large_driver.c | claude "解释这 100 行代码的作用"
  ```

## window上使用

### 安装

```powershell
winget install Anthropic.ClaudeCode
```

cc-switch配置文件

```yaml
# ~/.claude\settings.json
{
  "env": {
    "ANTHROPIC_BASE_URL": "https://api.deepseek.com/anthropic",
    "ANTHROPIC_AUTH_TOKEN": "{key}",
    "ANTHROPIC_MODEL": "deepseek-v4-flash",
    "ANTHROPIC_DEFAULT_HAIKU_MODEL": "deepseek-v4-flash",
    "ANTHROPIC_DEFAULT_SONNET_MODEL": "deepseek-v4-flash",
    "ANTHROPIC_DEFAULT_OPUS_MODEL": "deepseek-v4-flash"
  },
  "theme": "dark-daltonized",
  "enabledPlugins": {
    "pyright-lsp@claude-plugins-official": true
  }
}
```
