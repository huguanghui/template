**✅ claude-code-proxy 安装与使用指南（Linux）**

`claude-code-proxy` 是一个热门的 Anthropic 协议代理，能让 **Claude Code** 使用 OpenAI 兼容模型（DeepSeek、Qwen、Ollama、本地模型、OpenRouter 等）。

以下推荐两个最活跃的项目：

### 1. **推荐：1rgs/claude-code-proxy**（功能丰富，支持 Gemini/OpenAI）

```bash
# 1. 克隆仓库
git clone https://github.com/1rgs/claude-code-proxy.git
cd claude-code-proxy

# 2. 安装 uv（推荐的 Python 包管理器）
curl -LsSf https://astral.sh/uv/install.sh | sh

# 3. 配置环境变量
cp .env.example .env
nano .env
```

**常用 .env 配置示例（DeepSeek）：**

```env
OPENAI_API_KEY=sk-你的DeepSeek密钥
OPENAI_BASE_URL=https://api.deepseek.com/v1

# 可选：模型映射
BIG_MODEL=deepseek-chat
SMALL_MODEL=deepseek-chat
PREFERRED_PROVIDER=openai
```

**启动代理：**

```bash
uv run uvicorn server:app --host 0.0.0.0 --port 8082
```

**使用 Claude Code：**

```bash
ANTHROPIC_BASE_URL=http://localhost:8082 ANTHROPIC_API_KEY=任意字符串 claude
```

---

### 2. **备选：fuergaosi233/claude-code-proxy**（对本地模型/Ollama 友好）

```bash
git clone https://github.com/fuergaosi233/claude-code-proxy.git
cd claude-code-proxy

uv sync
cp .env.example .env
nano .env
```

**启动：**

```bash
uv run claude-code-proxy
# 或
python start_proxy.py
```

---

### Docker 方式（最方便）

**对于 1rgs 项目：**

```bash
docker run -d --env-file .env -p 8082:8082 ghcr.io/1rgs/claude-code-proxy:latest
```

---

### 永久设置（推荐）

```bash
# 在 ~/.bashrc 或 ~/.zshrc 中加入
export ANTHROPIC_BASE_URL=http://localhost:8082
export ANTHROPIC_API_KEY=dummy-key

# 然后直接运行
claude
```

---

**你想用哪种后端模型？**  
（DeepSeek / Qwen / Ollama 本地 / OpenRouter / Gemini 等）

告诉我具体需求，我给你对应的 `.env` 配置和完整命令。
