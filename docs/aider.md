# aider

`aider` 是目前公认最强的终端 AI 编程助手，它能直接理解你的本地代码库并自动修改代码、提交 Git。

针对你正在进行的 **嵌入式驱动开发（C 语言/内核/U-Boot）**，以下是完整的环境配置指南：

## 使用

### 1. 基础环境安装

`aider` 是基于 Python 的，建议安装在虚拟环境中以保持系统干净。

```bash
# 1. 安装 pip（如果还没有）
sudo apt update
sudo apt install python3-pip python3-venv git -y

# 2. 创建并激活虚拟环境（推荐）
python3 -m venv ~/.aider-env
source ~/.aider-env/bin/activate

# 3. 安装 aider
pip install aider-chat
```

---

### 2. 配置 API Key (核心步骤)

`aider` 默认推荐使用 **Claude 3.5 Sonnet**（编程能力目前最强）。

你需要将你的 Anthropic API Key 写入环境变量（建议放入 `~/.bashrc` 或 `~/.zshrc` 中）：

```bash
# 编辑配置文件
nano ~/.bashrc

# 在末尾添加（替换为你自己的 Key）
export ANTHROPIC_API_KEY=sk-ant-xxxxxxxxxxxxxx

# 保存退出后刷新
source ~/.bashrc
```

_注：如果你想使用 OpenAI 或 OpenRouter（省钱或用国内模型），可以对应设置 `OPENAI_API_KEY` 或 `OPENROUTER_API_KEY`。_

---

### 3. 在项目中使用 aider

`aider` 必须在 **Git 仓库** 中运行，因为它会根据 AI 的修改自动生成 Commit。

```bash
# 进入你的内核或驱动代码目录
cd ~/work/axera_driver_project

# 确保已经初始化 git
git init  # 如果还没初始化的话

# 启动 aider
aider
```

---

### 4. 针对嵌入式开发的 Aider 进阶配置

由于驱动开发涉及大量底层宏定义和头文件，建议通过配置文件优化 aider。

#### A. 创建全局配置文件

在你的家目录下创建 `~/.aider.conf.yml`：

```yaml
# 使用模型
model: anthropic/claude-3-5-sonnet-20240620

# 自动提交 Git（建议开启，方便回滚）
auto-commits: true

# 自动检查 lint（如果是 Python 很有用，C 语言可以手动通过 Makefile 检查）
# lint-cmd: make -j4

# 是否启用实时监控文件变化
watch: true

# 界面风格
theme: dark
```

#### B. 配合 C 语言开发的技巧

在进入 `aider` 后，使用命令添加上下文：

1. **添加相关文件**：
    `/add board.c gpio.h` (把这两个文件喂给 Claude)。
2. **参考头文件**：
    如果你需要它参考内核头文件但不想让它改头文件，可以使用 `/read-only include/linux/gpio.h`。
3. **让它修编译错误**：
    如果你 `make` 报错了，直接把错误贴给它：
    `"/run make -j4"` (它会运行编译命令并根据报错自动改代码)。

---

### 5. 常用快捷指令

在 `aider` 的对话框内：

- `/add <file>`: 添加文件到对话（让 AI 看得见）。
- `/drop <file>`: 从对话中移除文件（节省 Token）。
- `/git`: 执行 git 命令。
- `/undo`: **神器！** 撤销上一次 AI 的修改和 Commit（写错代码瞬间恢复）。
- `/exit`: 退出。

---

### 6. 嵌入式开发典型工作流示例

假设你要给你的 **Axera ADC 驱动** 增加一个平均值滤波算法：

1. 运行 `aider`。
2. 输入：`/add drivers/adc/ax_adc.c`。
3. 对话：`"请给 adc_read 函数增加一个 10 次采样的平均值滤波算法，注意不要阻塞中断。"`。
4. Aider 会展示代码 Diff，确认后自动写回文件并 `git commit`。
5. 对话：`"/run make"`（检查是否编译通过）。

### 7. 解决网络问题（如果在中国国内）

如果你无法直接连接 Anthropic 服务器，可以在启动前设置代理：

```bash
export https_proxy=http://127.0.0.1:你的代理端口
aider
```

或者使用 **OpenRouter** 作为中转（支持 Claude 3.5）：

```bash
export OPENROUTER_API_KEY=你的Key
aider --model openrouter/anthropic/claude-3.5-sonnet
```

配置完成后，你只需输入 `aider` 就能像带了一个精通驱动开发的专家一样写代码了。
