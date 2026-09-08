**在 DeepSeek Harness（dsh）中配置 OpenRouter 使用 DeepSeek 模型**，有两种主要方式：

### 方法一：推荐（最简单）——使用 OpenRouter 的 Ori 工具

OpenRouter 官方提供了一键配置 DeepSeek Harness 的工具：

```bash
# 1. 安装 Ori
curl -fsSL https://openrouter.ai/labs/ori/install.sh | bash

# 2. 配置 DeepSeek Harness 指向 OpenRouter
ori dsh
```

执行后会：

- 自动把你的全局 DeepSeek Harness 配置指向 OpenRouter
- 打开浏览器让你用 OpenRouter 账号登录（OAuth，无需手动粘贴 Key）
- 配置完成后，正常运行 `dsh` 或 `npx @deepseek-ai/dsh web` 即可

也可以指定默认模型：

```bash
ori dsh --model deepseek/deepseek-v4-flash
# 或
ori dsh --model deepseek/deepseek-v4-pro
# 或使用自动路由
ori dsh --model openrouter/auto
```

---

### 方法二：手动在 Web UI 中配置

1. 启动 DeepSeek Harness：

   ```bash
   npx @deepseek-ai/dsh web
   ```

   浏览器打开 `http://127.0.0.1:3080`

2. 进入 **设置 → 模型（Settings → Models）**

3. 点击 **添加提供方（Add provider）**，选择 **OpenRouter**（如果目录里有的话）

4. 如果没有 OpenRouter 预置选项，则选择 **添加自定义提供方（Add a custom provider）**，填写：

   | 字段                    | 填写内容                                                                                                          |
   | ----------------------- | ----------------------------------------------------------------------------------------------------------------- |
   | **Provider ID**         | `openrouter`（小写）                                                                                              |
   | **基础 URL (Base URL)** | `https://openrouter.ai/api/v1`                                                                                    |
   | **API 协议**            | `openai-completions`                                                                                              |
   | **API Key**             | 你的 OpenRouter API Key（从 [openrouter.ai/keys](https://openrouter.ai/keys) 获取）                               |
   | **模型**                | 至少添加一个，例如：<br>`deepseek/deepseek-v4-flash`<br>`deepseek/deepseek-v4-pro`<br>`deepseek/deepseek-chat` 等 |

5. 保存后，在模型选择器中选择对应的 DeepSeek 模型即可使用。

---

### 常用 DeepSeek 模型 ID（OpenRouter）

- `deepseek/deepseek-v4-flash`（推荐日常使用，便宜快速）
- `deepseek/deepseek-v4-pro`（更强性能）
- `deepseek/deepseek-chat`
- `deepseek/deepseek-r1`（推理模型）

---

**建议优先使用方法一（`ori dsh`）**，最省事，而且能直接使用你 OpenRouter 账号下的全部模型和路由策略。

**是的，`ori` 还有很多其他用法。**

它是 OpenRouter 官方推出的工具，核心作用是：**让你现有的各种 Agent / Harness 一键接入 OpenRouter**，自动处理登录、密钥、模型配置、优化设置等。

### 1. 支持的 Agent 一览

目前官方支持以下命令：

| 命令                            | 对应 Agent       | 说明                       |
| ------------------------------- | ---------------- | -------------------------- |
| `ori claude`                    | Claude Code      | Anthropic 官方终端 Agent   |
| `ori codex`                     | Codex CLI        | OpenAI 官方开源 Agent      |
| `ori grok`                      | Grok Build       | xAI 的 Grok 编程 Harness   |
| `ori hermes`                    | Hermes           | Nous Research 的开源 Agent |
| `ori opencode`                  | OpenCode         | 开源编码 Agent             |
| `ori pi`                        | Pi               | 另一个流行的 Agent         |
| `ori prime-agent` / `ori prime` | Prime Agent      | Prime Intellect 的 Agent   |
| `ori dsh`                       | DeepSeek Harness | 只做配置，不直接启动       |

如果本机没有对应的 Agent，Ori 会自动提示并帮你安装。

### 2. 常用命令示例

```bash
# 安装 / 更新
curl -fsSL https://openrouter.ai/labs/ori/install.sh | bash
ori update

# 登录（OAuth，不需要手动粘贴 Key）
ori login

# 启动各种 Agent
ori claude
ori codex
ori grok
ori hermes
ori opencode
ori pi
ori prime-agent
ori dsh          # 只配置 DeepSeek Harness
```

### 3. 指定模型

可以给任何 Agent 指定 OpenRouter 上的任意模型：

```bash
ori claude --model anthropic/claude-sonnet-4.6
ori codex --model openai/gpt-5.2
ori grok --model x-ai/grok-4.5
ori hermes --model openrouter/auto
ori dsh --model deepseek/deepseek-v4-flash
```

后面还可以继续跟原来 Agent 自己的参数，例如：

```bash
ori codex --model google/gemini-3.6-flash --full-auto
```

### 4. 其他实用功能

- **Live 模型目录**：在 Pi、Prime Agent、DeepSeek Harness 中，`/model` 会显示你 OpenRouter 账号真实可用的模型列表（会自动过滤组织策略禁止的模型）。
- **快速路由开关**：
  - `/fast`：开启高速路由（Claude 用 fast mode，OpenAI 用 priority tier，其他用 `:nitro`）
  - `/zdr`：只走 Zero Data Retention（不保留数据）的供应商
- **统一计费 & 权限**：所有通过 Ori 跑的请求都走你的 OpenRouter 账号，享受统一账单、Guardrails、Workspace 预算等功能。
- **不污染原有配置**：大部分情况下不会改写你原来的配置文件，只是临时注入 OpenRouter 的凭证。

### 总结

`ori` 本质上是一个**多 Agent 的 OpenRouter 启动器 + 配置器**。  
你不需要再为每个 Agent 手动设置环境变量、Base URL、模型映射，直接 `ori xxx` 就能用 OpenRouter 上的 500+ 模型。

想继续深入某个具体 Agent（比如 `ori claude` 或 `ori grok`）的用法，可以告诉我。
