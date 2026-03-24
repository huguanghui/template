**Ollama** 是一款极其火爆的开源工具，旨在让用户能够**在本地（自己的电脑上）极简地运行、管理和部署大语言模型（LLM）**。

如果把 Docker 类比为容器管理的标准，那么 Ollama 就可以被看作是 **“大模型领域的 Docker”**。

以下是 Ollama 的核心特点和功能简介：

### 1. 核心定位：极简主义

在 Ollama 出现之前，本地运行大模型通常需要复杂的 Python 环境配置、CUDA 驱动调试以及大量的依赖安装。

- **开箱即用**：Ollama 将模型权重、配置和依赖打包成一个单一的命令。
- **一键运行**：只需一行命令 `ollama run llama3`，它就会自动下载模型并开启交互界面。

### 2. 主要功能与优势

- **本地化与隐私**：所有数据都在你的本地设备上处理，无需联网，不泄露隐私，且完全免费（不消耗 Token 费用）。
- **模型库（Library）**：提供了一个类似 Docker Hub 的官方模型库，支持目前主流的所有开源模型：
  - **Llama 3** (Meta)
  - **Mistral / Mixtral**
  - **Gemma** (Google)
  - **Qwen / 通义千问** (Alibaba)
  - **DeepSeek** (深度求索)
  - **Phi-3** (Microsoft)
- **跨平台支持**：原生支持 **macOS** (支持 Apple Silicon 硬件加速)、**Linux** 和 **Windows**。
- **资源优化**：底层基于 `llama.cpp`，支持量化技术（Quantization），使得 8GB 甚至更低内存的电脑也能流畅运行 7B 或 8B 规模的模型。

### 3. 对于开发者：强大的 API 支持

这是 Ollama 能够与 **`avante.nvim`**、**`Continue.dev`** 或 **`Page Assist`** 等工具集成的关键。

- **本地服务器**：Ollama 启动后会在后台运行一个轻量级服务器，默认监听 `11434` 端口。
- **兼容性**：它提供 REST API，甚至支持 **OpenAI 兼容的 API 接口**。这意味着你可以轻松地把原本调用 GPT-4 的插件改为调用你本地的 DeepSeek 或 Llama 3。

### 4. 常用命令示例

- `ollama serve`：启动后台服务。
- `ollama run llama3`：下载并运行 Llama 3 模型。
- `ollama list`：查看本地已下载的模型。
- `ollama pull qwen`：仅下载模型而不立即运行。
- `ollama rm <model>`：删除本地模型。

### 5. 与 `avante.nvim` 的结合

如果你想在 `avante.nvim` 中使用本地模型，Ollama 是最佳选择。你可以配置 Avante 使用 `ollama` 作为 provider，例如：

```lua
-- avante.nvim 配置片段
opts = {
  provider = "ollama",
  vendors = {
    ollama = {
      ["local"] = true,
      endpoint = "127.0.0.1:11434/v1",
      model = "deepseek-v2:lite", -- 或者 "llama3"
      parse_curl_args = function(opts, code_opts)
        return {
          url = opts.endpoint .. "/chat/completions",
          headers = {
            ["Accept"] = "application/json",
            ["Content-Type"] = "application/json",
          },
          body = {
            model = opts.model,
            messages = require("avante.providers").copilot.parse_messages(code_opts), -- 借用解析逻辑
            max_tokens = 2048,
            stream = true,
          },
        }
      end,
      parse_stream_data = function(data, handler_opts)
        -- 解析逻辑...
      end,
    },
  },
}
```

### 总结

**Ollama** 是目前普通用户和开发者进入本地 AI 世界的最短路径。它屏蔽了底层的复杂性，让你能像使用普通软件一样在本地操控顶级 AI 模型。
