**OpenClaw 简介**

OpenClaw（曾用名 Clawdbot、Moltbot）是一款2025年底开源的**自主式个人AI代理（AI Agent）**，由奥地利开发者 Peter Steinberger（一位资深 Mac/iOS 开发者）创建。项目以龙虾（lobster）为图标和主题，Slogan 是 **“The AI that actually does things”**（真正会干活的AI）。

它最核心的特点是：**不是只能聊天的机器人，而是能“动手”帮你完成真实任务的本地AI助手**，强调**本地优先、自托管、隐私可控**。

简单一句话概括：  
你通过微信/Telegram/WhatsApp/Discord/iMessage 等你本来就在用的聊天软件发一条自然语言指令，OpenClaw 就能在你的电脑/服务器上替你真正去执行复杂任务，而不是只回复文字。

**主要技术特点**

- 开源（MIT 许可），GitHub 主仓库：openclaw/openclaw
- 用 TypeScript 编写，支持 macOS / Windows / Linux
- 支持几乎所有主流大模型（Claude、GPT、Gemini、DeepSeek、千问、通义等）
- 本地长期记忆（向量数据库）
- 通过“Skills”插件机制无限扩展能力
- 支持多渠道接入（WhatsApp、Telegram、Signal、Discord、Slack、Teams、iMessage、Matrix、甚至部分国内渠道）

**典型真实应用场景**（2026年用户最常用来干的事）

| 场景类别         | 具体例子                                                             | 实用程度（主观） |
| ---------------- | -------------------------------------------------------------------- | ---------------- |
| 个人生产力       | 自动清理邮箱、标记重要邮件、起草回复、安排日历、设置提醒             | ★★★★★            |
| 信息收集与研究   | “帮我把过去一周 Hacker News 前50的文章总结成中文思维导图发我”        | ★★★★★            |
| 旅行/生活服务    | 帮我值机、查航班、订外卖、比价机票酒店、监控签证进度                 | ★★★★☆            |
| 内容创作         | 批量处理图片/视频、写推文/小红书/知乎回答、润色英文邮件、做周报      | ★★★★★            |
| 开发者/编程      | 帮我修 bug、写测试、看代码库、自动提交 PR、管理 GitHub issue、写文档 | ★★★★★            |
| 苹果生态重度用户 | 操作本地 Mac 应用、批量处理照片、iMessage 自动回复、管理 iCloud 文件 | ★★★★★            |
| 团队/小型企业    | 当“AI 员工”：处理工单、回复常见客户咨询、监控服务器、做日报、周报    | ★★★★☆            |
| 自动化工作流     | 连接 MCP（如 Zapier 风格的工具链）、定时抓取竞品数据、价格监控       | ★★★★☆            |
| 极客玩法         | 自己写 Skill 让它炒币、做量化交易监控、管 NAS、远程控制智能家居      | ★★★☆☆            |

**一句话总结它的独特定位**

在 ChatGPT / Claude 还主要停留在“会聊天、会写代码”阶段时，OpenClaw 已经把“会干活”这件事做到了极致——它真正把大模型的智能和电脑的执行力连接起来了，而且是完全跑在你自己设备上的。

目前（2026年2月）它仍然处于非常快速迭代期，社区 Skill 生态正在爆炸式增长，但安全性和稳定性也需要自己把控（建议用 Docker 沙箱、专用小服务器或云 Mac 部署，不要直接用主力工作机跑）。

如果你想要一个**真正能替你干活、越用越懂你、隐私不给云厂商**的 AI 秘书，OpenClaw 目前几乎是开源领域里体验最激进、最接近“钢铁侠 Jarvis”的选择之一。

在 Linux 上搭建 **OpenClaw**（一个自主运行的个人 AI Agent）目前（2026年2月）最推荐、最简单的方式是使用官方的一行安装脚本。它会自动处理 Node.js 检测/安装、依赖、全局 CLI 安装，并启动 onboarding 向导。

### 推荐方式：一键安装脚本（最简单，适合绝大多数人）

```bash
# 在终端直接执行（需要 curl，已安装的系统基本都有）
curl -fsSL https://openclaw.ai/install.sh | bash
```

执行后会发生什么：

- 自动检测/安装 Node.js（推荐 v22+）
- 通过 npm 全局安装 openclaw CLI
- 启动交互式 onboarding 向导（onboarding wizard）
- 在向导中你需要完成：
  1. 选择主要模型提供商（OpenAI、Anthropic、Google、DeepSeek、Groq、OpenRouter、Ollama 本地等）
  2. 输入对应的 API Key（强烈建议先用 OpenRouter 聚合多家模型，便于切换）
  3. 选择主要聊天接入渠道（Telegram 机器人最常用，其次 WhatsApp/Signal/Discord/Slack 等）
  4. 配置长期记忆（默认用本地向量数据库，已内置）
  5. 是否安装为系统服务/守护进程（**非常推荐选 yes**，这样关终端也能后台运行）

安装完成后，OpenClaw 会以守护进程方式运行（systemd 或其他方式），你可以用微信/Telegram 等发消息直接指挥它。

### 手动安装方式（适合想自己控制或有特殊需求时）

```bash
# 1. 确保有 Node.js 22+（用 nvm 管理最方便）
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
source ~/.bashrc   # 或 source ~/.zshrc
nvm install 22
nvm use 22

# 2. 全局安装 OpenClaw CLI（最新版）
npm install -g openclaw@latest

# 3. 启动 onboarding（第一次必须跑这个）
openclaw onboard

# 4. 安装为后台服务（强烈推荐）
openclaw service install   # 或 openclaw daemon install（视版本）

# 5. 查看状态 / 日志 / 重启
openclaw status
openclaw logs
openclaw restart
```

### Linux 服务器 / VPS 推荐做法（安全性 & 稳定性）

大多数人最终会把 OpenClaw 跑在云服务器上（Hetzner、DigitalOcean、Linode、Vultr 5–15 美元/月的机器即可）。

安全 & 最佳实践（2026 年社区共识）：

| 事项               | 推荐做法                                | 为什么重要                           |
| ------------------ | --------------------------------------- | ------------------------------------ |
| 用户权限           | **新建普通用户**运行，绝不 root         | 防止 agent 执行 rm -rf / 等灾难命令  |
| 隔离方式           | Docker / Podman / Firejail / bubblewrap | 限制文件、网络、进程访问范围         |
| 网络出口           | 只允许必要的域名（api.openai.com 等）   | 防数据泄露 + 防恶意 skill 打电话回家 |
| API Key 管理       | 环境变量 + .env 文件（chmod 600）       | 防止泄露                             |
| 模型选择           | 先用 OpenRouter + 限额                  | 便宜、切换模型快                     |
| 技能（Skills）安装 | 只从 ClawHub 官方或信任来源安装         | 很多 skill 有 prompt injection 风险  |
| 定期备份           | ~/.openclaw / 记忆向量库 + 配置         | 数据不容易重建                       |
| 监控               | healthchecks.io 或 uptime kuma 检查心跳 | 知道它是否还活着                     |

最常见的 Docker 快速启动方式（社区常用）：

```bash
# 简单版（官方有更完整的 docker-compose 示例）
docker run -d \
  --name openclaw \
  -v ~/.openclaw:/home/claw/.openclaw \
  -e OPENCLAW_MODEL_PROVIDER=openrouter \
  -e OPENROUTER_API_KEY=sk-or-v1-xxxx \
  -p 3000:3000 \   # 如果你想用 web dashboard
  ghcr.io/openclaw/openclaw:latest
```

### 快速验证是否跑起来了

1. 安装完后，用你绑定的 Telegram / WhatsApp 发消息：

   ```
   @openclaw 你好，我是光辉
   ```

   或直接发自然语言指令：

   ```
   帮我搜索一下今天东京的天气，然后总结成一句话发给我
   ```

2. 如果没反应，检查：

```bash
openclaw logs --tail 50
openclaw status
```

### 常见坑 & 建议（2026年2月真实用户反馈）

- 不要直接给它 root 权限或主机的全部文件访问
- 第一次 onboarding 选 Telegram Bot 最快上手（5分钟出 bot token）
- 想本地跑大模型 → 先装 Ollama + 好的 embedding 模型
- 社区最活跃地方：Discord（discord.gg/clawd）、GitHub Discussions
- 官方文档（最准）：<https://docs.openclaw.ai>
- 安全 checklist：搜索 “OpenClaw security hardening” 或看 Reco.ai / Hostinger 的文章

祝你顺利部署出自己的“龙虾 Jarvis”！🦞  
有具体报错或想接哪个渠道/模型，再贴日志我帮你 debug。
