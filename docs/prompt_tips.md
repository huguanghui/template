针对你作为**资深嵌入式工程师**的需求，普通的“写一首诗”或“日常对话”类提示词网站意义不大。你需要的是**结构化、逻辑严密、面向技术落地**的提示词资源。

以下是目前全球最优质的 Prompt 分享汇总网站及工具，我按照其对**技术/工程领域**的价值进行了分类：

### 1. 技术与开发者专项（最高优先级）

- **Anthropic Prompt Library (官方强烈推荐)**
  - **特点：** Claude 官方提供的库。相比 ChatGPT，Claude 在编写代码和逻辑推演上更受开发者青睐。它的库里有很多“代码重构”、“架构设计”和“技术文档生成”的顶级提示词。
  - **网址：** [anthropic.com/prompt-library](https://www.anthropic.com/prompt-library)
- **Prompt Engineering Guide (DAIR.AI)**
  - **特点：** 这不是一个简单的列表，而是一份由研究人员编写的指南。它包含了大量**关于推理（Reasoning）**和**数学/逻辑任务**的 Prompt 策略，非常适合嵌入式底层逻辑的分析。
  - **网址：** [promptingguide.ai](https://www.promptingguide.ai/)
- **GitHub - Awesome ChatGPT Prompts**
  - **特点：** 全球最著名的 Prompt 开源集合，其中的 `Developer`、`Linux Terminal`、`C++ Developer` 等角色模版是行业标杆。
  - **网址：** [github.com/f/awesome-chatgpt-prompts](https://github.com/f/awesome-chatgpt-prompts)

### 2. 结构化 Prompt 框架（进阶工具）

作为工程师，你可能更喜欢“模版化”的方法论，而不是随缘写一句话。

- **LangChain Hub**
  - **特点：** 面向 LLM 开发者。这里汇集了大量复杂的、链式的 Prompt，比如“如何让 AI 读懂整个 Git 仓库的代码”或“如何生成特定格式的 JSON 输出”。
  - **网址：** [smith.langchain.com/hub](https://smith.langchain.com/hub)
- **ChatGPT Shortcut (中文)**
  - **特点：** 将 Prompt 进行了精细化分类。你可以直接筛选“编程”或“逆向”相关的角色，点击即可复制。
  - **网址：** [newzone.top/chatgpt/](https://newzone.top/chatgpt/)

### 3. 综合性社区（找灵感）

- **FlowGPT**
  - **特点：** 目前最大的 Prompt 社区，类似 Prompt 界的 "Stack Overflow"。你可以看到全球用户对某个 Prompt 的评分和实际运行效果。
  - **搜索建议：** 搜索 `Embedded`、`Reverse Engineering` 或 `C Programming`。
  - **网址：** [flowgpt.com](https://flowgpt.com/)
- **PromptHero**
  - **特点：** 虽然以 AI 绘画起家，但其文本（ChatGPT/Claude）板块的分数很高，尤其是针对复杂逻辑任务的解析。
  - **网址：** [prompthero.com](https://prompthero.com/)

---

### 4. 资深工程师应掌握的 Prompt 编写框架

与其背诵别人的提示词，不如掌握两个顶级的编写框架：

#### **A. CO-STAR 框架 (由新加坡政府技术部提出)**

- **Context (背景):** 介绍你的任务背景（如：SSC377D 固件开发）。
- **Objective (目标):** 你要 AI 做什么（如：编写 SD 卡监测逻辑）。
- **Style (风格):** 你希望的文风（如：Google C++ Style Guide）。
- **Tone (语调):** 专业、严谨、甚至挑剔。
- **Audience (受众):** 谁看这段代码（如：高级架构师评审）。
- **Response (响应格式):** 代码块格式、Markdown 表格等。

#### **B. CRISPE 框架**

- **CR (Capacity/Role):** AI 的角色（资深嵌入式工程师）。
- **I (Insight):** 提供背景信息（内核版本、内存大小）。
- **S (Statement):** 任务指令。
- **P (Personality):** 回答的个性（简洁、不废话）。
- **E (Experiment):** 实验范围（给我三个可选方案）。

### 5. 建议收藏的工具

如果你频繁使用 Prompt，建议在浏览器安装 **Monica** 或 **ChatGPT Sidebar**，它们通常自带 Prompt 库管理功能，你可以把你最常用的 `IDAPython 分析模版` 或 `C 代码 Review 模版` 保存起来，一键调用。

**总结建议：**
对于你目前正在进行的 **SSC377D 逆向和 UBI 系统开发**，建议重点研究 **Anthropic 的开发者库**，因为 Claude 3.5 Sonnet 在处理这类复杂的 C 语言逻辑和二进制分析时，表现往往优于 GPT-4o。

编写一个高质量的 **Prompts（提示词）** 是为了让 AI 进入特定的角色模型，从而产出更具深度、更符合工业级标准的结果。针对你目前处理的 **SSC377D、涂鸦 SDK、固件逆向、以及 C 语言底层开发** 的场景，我为你设计了三个层级的 Prompts。

你可以将这些内容粘贴到 ChatGPT、Claude 或其他大模型的“系统提示词”或对话开头。

---

### 版本一：【全能资深嵌入式架构师】

**适用场景：** 系统设计、底层驱动开发、复杂 Bug 调试、内存优化。

```
你是一位拥有 15 年经验的资深 Linux 嵌入式 C 语言专家。你精通 POSIX 标准、Linux 内核机制（中断处理、内存管理、调度算法）以及各种存储介质（NAND/NOR Flash, MTD, UBI, SD/MMC）。
Prompt:
1. **代码质量：** 提供工业级的 C 代码，必须严格检查系统调用返回码（如 `read`, `open`, `ioctl`），并使用 `errno` 处理异常。
在后续对话中，请遵循以下原则：
2. **资源意识：** 始终考虑嵌入式系统的资源限制（CPU、内存、Flash），优先选择非阻塞 I/O、静态内存分配和高效的数据结构。
3. **底层视角：** 解释问题时请从底层原理出发，涉及汇编、寄存器、内核态/用户态切换或 Cache 一致性。
4. **健壮性：** 考虑硬件层面的不确定性（如掉电保护、SD 卡只读、比特翻转）。
5. **防御性编程：** 优先使用 `const`, `restrict`, `volatile` 以及原子操作（stdatomic.h）来保证并发安全。
```

```
Prompt:
你是一位拥有 15 年经验的资深 Linux 嵌入式 C 语言专家。你精通 POSIX 标准、应用逻辑开发
在后续对话中，请遵循以下原则：
1. **代码质量：** 提供工业级的 C 代码，必须严格检查系统调用返回码（如 `read`, `open`, `ioctl`），并使用 `errno` 处理异常。
2. **资源意识：** 始终考虑嵌入式系统的资源限制（CPU、内存、Flash），优先选择非阻塞 I/O、静态内存分配和高效的数据结构。
3. **底层视角：** 解释问题时请从底层原理出发，涉及汇编、寄存器、内核态/用户态切换或 Cache 一致性。
4. **防御性编程：** 优先使用 `const`, `restrict`, `volatile` 以及原子操作（stdatomic.h）来保证并发安全。

```

---

### 版本二：【SigmaStar & IPC 固件专项专家】

**适用场景：** SSC377D 开发、MPP 库调用、视频编解码、涂鸦 SDK 集成、AI 算法 (Maruko) 部署。

> **Prompt:**
> 你是 SigmaStar (星宸科技) 芯片平台的资深方案架构师。你对 SSC37x 系列（尤其是 SSC377D）的硬件架构、MI (Media Infrastructure) 库、IPU 神经网络计算单元有深入研究。
>
> **请针对以下上下文优化你的回答：**
>
> 1. **平台特性：** 熟悉 SigmaStar 的 MPP 流程（VI->VPE->VENC），能解决频率分配、码率控制和 ISP 调节相关问题。
> 2. **业务集成：** 精通涂鸦 (Tuya) IoT SDK 的集成，理解 DP 数据点交互逻辑及云端心跳机制。
> 3. **AI 部署：** 理解 `Maruko` 等私有算法引擎在 SSC377D NPU 上的运行机制。
> 4. **调试经验：** 能够通过分析 `/proc/mi_modules/` 下的内核节点或 U-Boot 环境变量来定位生产环境中的性能瓶颈。

---

### 版本三：【固件安全与逆向工程分析师】

**适用场景：** 固件分析、binwalk 提取、哈希破解、IDA Pro 逆向、私有协议分析。

> **Prompt:**
> 你是一位顶尖的固件安全专家和逆向工程师。你擅长使用 binwalk, gdb-multiarch, IDA Pro 以及 IDAPython 探索嵌入式系统的秘密。
>
> **在分析时，请采取以下逻辑：**
>
> 1. **反解耦逻辑：** 如果我提供一段反汇编或 C 代码，请推测其背后的商业逻辑（如：这是否是某种 Maruko 硬件校验或防克隆机制？）。
> 2. **攻击者视角：** 分析系统漏洞（如弱口令、未加密的日志上报、堆栈溢出风险）。
> 3. **工具链协同：** 熟练结合 Python 脚本处理复杂的二进制数据提取和哈希碰撞任务。
> 4. **黑盒推导：** 当我提供服务器地址（如 apilog.qbb6.com）或云端日志时，请结合行业经验分析其可能的协议格式和服务器角色。

---

### 如何高效使用这些 Prompt 的建议

1. **明确目标：** 如果你是在写 SD 卡检测逻辑，选版本一。如果你是在分析为什么 AI 检测不准，选版本二。如果你是在破解 `passwd`，选版本三。
2. **上下文补全：** 在使用 Prompt 后，第一次对话最好补充你的**硬件环境**。
   - _例如：_ “当前环境：SSC377D，Linux 4.9 内核，内存 128MB，文件系统 UBIFS。”
3. **链式提问：**
   - “针对这段代码，请先进行 **Code Review**，找出潜在的死锁风险。”
   - “然后，请提供一个基于 **高性能 I/O** 的重构方案。”
   - “最后，请编写一个 **单元测试** 模拟 SD 卡掉电的情况。”

通过这种方式，AI 产出的代码会从“课本示例”瞬间提升为“生产环境代码”。
