# Caloude Cookbooks

## 简介

**Claude Cookbooks**（<https://github.com/anthropics/claude-cookbooks）是> Anthropic 官方维护的一个代码示例仓库，
主要收集各种使用 Claude 的实用 notebook 和 recipes（食谱）。
内容以 **Jupyter Notebook** 为主（约 95%），辅以 Python 脚本。

### 顶层目录结构（主要文件夹）

| 目录                    | 说明                                                                               |
| ----------------------- | ---------------------------------------------------------------------------------- |
| **capabilities/**       | 核心能力示例：分类（classification）、RAG（检索增强生成）、Summarization（摘要）等 |
| **tool_use/**           | 工具调用（Tool Use）和函数集成示例                                                 |
| **multimodal/**         | 多模态能力（Vision、图像处理、图表解读、表单提取等）                               |
| **managed_agents/**     | 托管代理（Managed Agents）和多代理协调                                             |
| **patterns/agents/**    | 代理模式相关示例                                                                   |
| **claude_agent_sdk/**   | Claude Agent SDK 相关代码                                                          |
| **extended_thinking/**  | 扩展思考 / 长链推理模式                                                            |
| **finetuning/**         | 微调相关示例                                                                       |
| **observability/**      | 可观测性、监控与评估                                                               |
| **third_party/**        | 第三方集成（Pinecone、Voyage AI、Wikipedia 等）                                    |
| **coding/**             | 代码生成与编程相关示例                                                             |
| **skills/**             | 技能（Skills）相关 notebook                                                        |
| **misc/**               | 杂项工具：JSON mode、prompt caching、PDF 处理、moderation filter 等                |
| **tool_evaluation/**    | 工具评估相关                                                                       |
| **tests/**              | 测试脚本                                                                           |
| **scripts/**            | 辅助脚本（如验证、构建等）                                                         |
| **images/**             | 图片资源                                                                           |
| **anthropic_cookbook/** | 可能用于包或内部组织结构                                                           |
| **.claude/**            | Claude Code / 项目特定配置、skills 和命令                                          |
| **.github/**            | GitHub workflows、issue templates 等                                               |

### 根目录重要文件

- **README.md**：项目总说明、食用指南和 recipes 目录索引
- **CLAUDE.md**：项目结构说明和 Claude 相关配置
- **CONTRIBUTING.md**：贡献指南
- **LICENSE**（MIT）
- **pyproject.toml / uv.toml / uv.lock**：Python 项目依赖管理（使用 uv）
- **requirements-dev.txt**：开发依赖
- **.env.example**：环境变量模板（API Key 等）
- **Makefile / tox.ini**：构建和测试命令
- **registry.yaml / authors.yaml**：注册表和作者信息

### 特点总结

- 大部分示例都是**可直接运行的 Jupyter Notebook**，复制粘贴即可使用。
- 重点覆盖：**Tool Use、Multimodal、Agents、RAG、Prompting 最佳实践** 等。
- 代码以 Python 为主，但概念可迁移到其他语言。
- 仓库活跃，持续更新（目前数百次提交）。

你想深入了解某个具体子目录（如 `tool_use` 或 `multimodal`）的结构吗？或者需要某个 notebook 的详细内容，我可以帮你进一步查看。

## 安装使用

> **仓库下载后环境搭建和入门操作（推荐步骤）**

### 1. 下载仓库

```bash
git clone https://github.com/anthropics/claude-cookbooks.git
cd claude-cookbooks
```

### 2. 环境搭建（推荐使用 uv）

项目使用 **uv**（现代 Python 包管理器，速度极快）进行依赖管理。

#### 安装 uv（如果没有）

- **macOS / Linux**：

  ```bash
  curl -LsSf https://astral.sh/uv/install.sh | sh
  ```

- **Windows**：使用 PowerShell 或 Winget 安装。

#### 安装项目依赖

```bash
# 安装所有依赖（包含 extras）
uv sync --all-extras

# 安装 pre-commit hooks（推荐，用于代码质量检查）
uv run pre-commit install
```

### 3. 配置 API Key（必须）

```bash
# 复制环境变量模板
cp .env.example .env

# 编辑 .env 文件，填入你的 Anthropic API Key
# 使用 vim / nano / VS Code 等编辑器
nano .env
```

在 `.env` 中添加：

```env
ANTHROPIC_API_KEY=sk-ant-你的真实key在这里
```

> 获取 API Key：访问 [https://console.anthropic.com](https://console.anthropic.com) 注册并创建。

### 4. 验证安装（可选）

```bash
# 运行测试
uv run pytest

# 或使用 Makefile（更方便）
make check     # 检查格式和 lint
make test
```

### 5. 入口操作 - 运行 Notebook（最常用方式）

大多数示例都是 **Jupyter Notebook**，推荐以下方式打开：

#### 方式一：使用 uv 启动 Jupyter（推荐）

```bash
uv run jupyter lab
# 或
uv run jupyter notebook
```

#### 方式二：使用 VS Code（最方便）

1. 用 VS Code 打开仓库文件夹
2. 安装 Jupyter 扩展
3. 选择 Python 解释器（uv 创建的虚拟环境，通常在 `.venv` 文件夹）
4. 直接打开任意 `.ipynb` 文件运行

### 推荐入门 Notebook（建议顺序）

1. **multimodal/getting_started_with_vision.ipynb** —— 多模态入门
2. **tool_use/** 目录下的基础 tool use 示例
3. **capabilities/** 目录下的 RAG、分类、摘要等
4. **misc/** 下的 prompt caching、JSON mode 等实用技巧

### 其他常用命令（Makefile）

```bash
make format     # 格式化代码
make lint       # 检查代码
make fix        # 自动修复
make test       # 运行测试
```

---

**提示**：

- 大部分 notebook 顶部会有 `load_dotenv()`，会自动读取 `.env` 中的 key。
- 如果遇到依赖问题，可运行 `uv sync --all-extras --reinstall` 重新安装。
- 仓库持续更新，建议定期 `git pull`。

需要我详细说明某个具体目录（如 `tool_use` 或 `multimodal`）的运行方式吗？或者遇到报错可以贴出来我帮你排查。
