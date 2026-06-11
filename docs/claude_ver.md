# Claude版本记录

## 2.2.172

**✅ Claude Code v2.1.172 版本更新整理（简体中文）**

### 一、主要新功能

- **子代理（Sub-agents）支持嵌套创建子代理**  
  现在子代理可以继续创建自己的子代理，最深支持 **5 层嵌套**，大幅增强了多层代理协同能力。

- **Amazon Bedrock 区域配置优化**  
  当未设置 `AWS_REGION` 环境变量时，会自动读取 `~/.aws` 配置文件中的区域设置（符合 AWS SDK 优先级规则）。  
  `/status` 命令会显示当前区域的来源。

- **插件市场新增搜索栏**  
  在 `/plugin` 浏览 marketplace 插件时，新增搜索功能，极大提升查找效率。

- **新增 OTEL 指标属性**  
  `claude_code.lines_of_code.count` 指标增加了 `model` 属性，便于按模型维度统计代码行数。

### 二、重要 Bug 修复（共 15+ 项）

**会话与代理相关修复：**

- 修复使用 1M 上下文但没有足够 credits 的会话被永久卡住的问题，现在会自动压缩回标准上下文限制。
- 修复背景代理读取其他目录项目设置（.mcp.json、信任配置）的问题。
- 修复嵌套子代理停止后，主代理面板中仍显示 “active” 状态的问题。
- 修复从旧版本启动的会话在 daemon 自动更新后 attach 失败（EAUTH）的问题。

**模型选择与 Bedrock 相关修复：**

- 修复 `/model` 建议显示错误斜杠前缀、显示组织禁用模型的问题。
- 修复 `availableModels` 限制未正确应用于子代理、dispatch picker 和 advisor 的问题。
- 修复 Bedrock `/model` picker 提供不支持模型的问题。
- 修复模型 ID 出现重复 `[1M]` 后缀的问题。
- 修复 `opusplan` 在计划模式下未启用 1M 上下文的问题。

**其他重要修复：**

- 修复对话中包含多张图片时反复出现 “image could not be processed” 错误的问题。
- 修复 agents view 中 worker 已回复但仍显示忙碌 spinner 长达 30 秒的问题。
- 修复 `/code-review` 在未登录 claude.ai 时隐藏 ultra 选项的问题。
- 修复 PowerShell 工具调用在 VS Code 中显示为原始 JSON 的问题。
- 修复鼠标跟踪在部分 Windows 控制台上的兼容性问题。

### 三、性能与体验优化

- 长对话性能显著提升：移除冗余消息标准化，减少不必要的消息历史转换。
- 降低空闲 CPU 使用率：`/goal` 状态芯片不再高频重绘，子代理并行运行时 UI 重绘更少。
- Claude in Chrome 工具加载优化：批量加载而非单个加载。
- 改进非交互式 Usage Policy 拒绝提示。
- 缩短 Remote Control 底部提示为 “/rc active”，窄终端时自动隐藏。
- 停止在远程会话中推广 `/loop`（因无法保持容器存活）。
- 工作流验证逻辑改进，不再因提示中仅提及 `Date.now()`/`Math.random()` 而拒绝。
- 修复内存召回无法找到团队共享内存存储的问题。
- 修复提示历史（up-arrow）在子代理 Tab 打开时显示主代理历史的问题。

### 四、总结

**v2.1.172 核心亮点**：

- **代理能力重大升级**：支持 5 层嵌套子代理，极大增强复杂任务分解能力。
- **稳定性与兼容性** 大幅提升，尤其针对 Bedrock、多模型管理、1M 上下文、嵌套代理等高阶使用场景。
- **性能优化** 明显，适合长对话和多代理并行场景。

**推荐**：强烈建议所有使用代理功能、Bedrock 或 1M 上下文的用户尽快更新至 **v2.1.172**。

---

## 2.2.170

**✅ Claude Code v2.1.170 版本更新整理（简体中文）**

### 一、重大新功能

- **重磅发布：Claude Fable 5（Mythos 级模型）**  
  推出了全新 **Claude Fable 5** 模型，这是 Anthropic 目前能力最强的通用可用模型（Mythos-class）。  
  其性能超越了以往所有公开可用的 Claude 模型。  
  **使用方式**：更新到 **v2.1.170** 即可立即访问。  
  详情链接：<https://www.anthropic.com/news/claude-fable-5-mythos-5>

### 二、Bug 修复

- **修复会话记录保存问题**  
  修复了从 **VS Code 集成终端** 或任何继承了 Claude Code 环境变量的 Shell 中启动会话时，出现的以下问题：
  - 会话 Transcript（对话记录）无法保存
  - 使用 `--resume` 时无法找到该会话

### 三、总结

此版本**核心亮点**是正式引入了能力大幅提升的 **Claude Fable 5** 模型，属于一次重要的模型升级。

同时修复了一个较为常见的启动场景 Bug（尤其是 VS Code 用户），提升了会话持久化和恢复的可靠性。

**建议**：  
所有用户尽快更新至 **v2.1.170**，以体验全新 Fable 5 模型并避免会话记录丢失的问题。

---

## 2.2.169

**✅ Claude Code v2.1.169 版本更新整理（简体中文）**

### 一、主要新增功能

- **新增 `--safe-mode` 安全模式**  
  启动时可通过 `--safe-mode` 参数或 `CLAUDE_CODE_SAFE_MODE` 环境变量，**禁用所有自定义内容**（包括 CLAUDE.md、插件、Skills、Hooks、MCP 服务等），便于故障排查。

- **新增 `/cd` 命令**  
  在会话中途切换工作目录，不会破坏 Prompt Cache。

- **新增 `disableBundledSkills` 设置**  
  可通过设置 `disableBundledSkills` 或 `CLAUDE_CODE_DISABLE_BUNDLED_SKILLS` 环境变量，隐藏所有内置 Skills、工作流和斜杠命令，适合极简使用场景。

### 二、重要修复（共 15+ 项）

**核心体验修复：**

- 修复长输入行时 Up/Down 箭头无法按视觉行移动的问题，现在体验更自然。
- 修复 macOS 使用 claude.ai 账号登录时，每轮对话开始有 30-50ms UI 卡顿的问题。
- 修复 Windows 下 `claude -p` 命令启动缓慢或假死的问题。
- 修复 Remote Control 在 OAuth token 刷新时卡在 “reconnecting” 的问题。

**企业/MCP 相关修复：**

- 修复企业管理的 MCP 策略（allowed/denied）在多种场景下未生效的问题。
- 修复背景 Agent 忽略项目级环境变量（如 `ANTHROPIC_MODEL`）的问题。
- 修复 untrusted 项目设置可绕过信任确认设置证书路径的安全问题。

**其他重要修复：**

- 修复 Git Credential Manager 在 Windows 启动时弹出 “Connect to GitHub” 窗口的问题。
- 修复插件 .in_use PID 锁文件无限累积的问题（现每日清理一次）。
- 修复背景会话在某些情况下丢失 `--ide`、`--chrome` 等启动参数的问题。
- 修复 Agents --json 输出不完整的问题，新增 `--all` 参数和 `id`、`state` 字段。
- 修复 WSL + Windows Terminal 下 Agent 界面残留乱码的问题。

### 三、优化与改进

- 降低响应流式输出和加载动画时的 CPU 使用率。
- `/workflows` 命令即使在对话进行中也能立即打开。
- TaskCreate 可靠性提升：自动修复格式错误输入，错误提示更清晰。
- 改进组织禁用 API Key 认证时的错误提示。
- 背景会话状态验证更严格，保留更多启动参数。
- Windows 自动更新器在 claude.exe 被占用时不再无限重试。
- 技能标签颜色对比度提升，视觉效果更好。
- “CLAUDE.md 过长” 警告阈值随模型上下文窗口大小动态调整。
- Vertex/Foundry 默认增加 5 分钟空闲超时，防止流卡死。

### 四、其他

- 为 Apple/Google 账单但未添加支付方式的用户，优化了促销额度领取提示。
- 新增提示：建议用户在运行多个会话时使用 **Claude Agents**。

---

**总体评价：**  
此版本以**稳定性、故障排查能力和企业可用性**为重点，修复了大量用户反馈的体验问题和边缘 Bug，同时提供了更灵活的安全与自定义控制选项，推荐所有用户更新。

## 2.2.168

Bug修复和稳定性提升

## 2.2.167

Bug修复和稳定性提升

## 2.1.166

**版本号**：v2.1.166  
**更新重点**：**模型容错能力大幅增强** + **权限控制更灵活** + **稳定性与兼容性修复**。

---

### **一、新功能与重要改进**

1. **Fallback Model（备用模型）支持** ★★★★★
   - 新增 `fallbackModel` 设置，最多可配置**三个备用模型**。
   - 当主模型过载或不可用时，会按顺序自动尝试备用模型。
   - `--fallback-model` 参数现在也对**交互式会话**生效。

2. **权限规则支持 Glob 通配符**
   - `deny` 规则的工具名称位置现在支持 Glob 模式（如 `*` 表示拒绝所有工具）。
   - `allow` 规则仍不允许非 MCP 的 Glob。
   - 未知工具名的 deny 规则会在启动时给出警告。

3. **跨会话消息（SendMessage）安全性强化**
   - 从其他 Claude 会话中转发的消息不再携带用户权限。
   - 接收方会拒绝被转发的权限请求，Auto Mode 也会阻挡此类请求。

4. **思考模式（Thinking）控制增强**
   - `MAX_THINKING_TOKENS=0`、`--thinking disabled` 以及模型开关现在可以强制关闭默认开启思考的模型。

5. **API 错误自动重试**
   - 当 API 返回非重试类错误时，会自动在备用模型上重试一次（认证、限流、请求过大等错误仍立即报错）。

6. **其他体验优化**
   - `claude update` 现在会在下载前提示目标版本。
   - `claude agents` 列表中输入 URL 可快速筛选包含该 URL 的会话。

---

### **二、Bug 修复**

**核心稳定性修复**：

- 修复发送无法处理的图片时反复出现 “image could not be processed” 错误和额外 token 消耗的问题。
- 修复远程会话在启动时 worker 注册短暂中断后永久卡住的问题。
- 修复 JetBrains IDE（IntelliJ、PyCharm 等 2026.1+ 版本）终端闪烁问题。
- 修复 Kitty 键盘协议下 Shift + 非 ASCII 字符输入丢失的问题。
- 修复 PowerShell 命令在 Windows 下偶尔超时挂起的问题。
- 修复 macOS 下后台 daemon 死亡后残留的 `--bg-pty-host` 进程 100% CPU 问题。

**Agents 与后台会话修复**：

- 修复后台 Agent 会话进入 git worktree 后重开出现 “No conversation found” 崩溃循环的问题。
- 修复 Ctrl+O 对话记录视图中思考文本重复显示的问题。
- 修复 `/doctor` 命令在远程会话中显示矛盾错误的问题。
- 修复 Agents 派发和回复输入框中多行提示时光标卡在第一行末尾的问题。

**其他修复**：

- 修复托管设置（managed settings）无效条目导致其他有效策略失效的问题。
- 修复 managed-settings 中使用 `${VAR}` 引用时匹配失败的问题。
- 修复任务列表在不支持 Unicode 的终端下出现多余空行的问题。

---

### **总结评价**

v2.1.166 是一次**企业级可靠性与容错能力**显著提升的版本：

- **最大亮点**：引入多备用模型机制，大幅降低了因模型不可用导致的中断风险。
- **权限控制**更加灵活和安全。
- 修复了多个影响使用体验的顽固问题（尤其是 JetBrains、键盘输入、后台会话等）。

**适合人群**：企业用户、重度依赖 Agents 的用户、对模型可用性要求高的用户。

---

需要我帮你重点提取某个部分（例如 Fallback Model 详细说明、企业管理相关、Agents 修复等）做更深入解读吗？

## 2.1.165

Bug修复和稳定性提升

## 2.1.163

**版本号**：v2.1.163  
**更新重点**：**企业管理能力增强** + **Hooks 与 Agents 稳定性提升** + **细节体验优化**。

---

### **一、新功能与重要改进**

1. **企业管理策略新增版本控制**
   - 新增 `requiredMinimumVersion` 和 `requiredMaximumVersion` 托管设置。
   - 如果当前版本不在允许范围内，Claude Code 将**拒绝启动**，并引导用户更新到合规版本。

2. **插件管理命令**
   - 新增 `/plugin list` 命令，可列出已安装插件，支持 `--enabled` / `--disabled` 过滤。

3. **/btw 命令增强**
   - 新增快捷键 `c`：一键复制 `/btw` 返回的原始 Markdown 内容，方便粘贴到其他地方保留格式。

4. **Hooks 功能升级**
   - `Stop` 和 `SubagentStop` Hook 现在可以返回 `hookSpecificOutput.additionalContext`，用于给 Claude 提供反馈并继续当前对话，而不会被判定为 Hook 错误。

5. **Skills 语法增强**
   - 新增 `\$` 转义语法，可在命令体中插入字面 `$` 符号 + 数字，避免解析错误。

6. **MCP 会话一致性**
   - stdio MCP 服务器现在也能获得 `CLAUDE_CODE_SESSION_ID`，与 Hook / Bash 保持一致（对 `--resume` 更友好）。

---

### **二、Bug 修复**

**核心稳定性修复**：

- 修复 `claude -p` 在后台命令未退出时会永久挂起的问题（现在会在结果返回后约 5 秒停止后台 Shell）。
- 修复在 Bedrock/Vertex/Foundry + CI=true 环境下出现 “ANTHROPIC_API_KEY required” 的问题。
- 修复 Bash 命令在 Bazel、EDR 保护的 Go 工作流中因 `$TMPDIR` 被错误覆盖导致失败的问题。
- 修复 Windows 下 Session-env 目录为只读或在 OneDrive 中导致 “EEXIST” 错误的问题。
- 修复组织管理的权限规则在启动时未能正确应用的问题。

**Agents 相关修复**：

- 修复后台 Agents 会话在 Claude Code 更新后重新附加时丢失正在运行的任务的问题。
- 修复从 Agents 视图按 Esc 退出时终端错位和长时间卡顿的问题。
- 修复后台任务芯片点击 Stop 无效的问题。

**其他修复**：

- 修复 Hook `if: "Bash(...)"` 条件误匹配的问题。
- 修复 Home 目录下的 deny 规则无法阻止 Bash 命令通过 `$HOME` 引用路径的问题。
- 修复关闭 `/mcp`、`/plugins` 等面板后留下多余 “(no content)” 行的问题。
- 修复键盘输入在某些粘贴操作后永久无响应的问题。

---

### **三、其他优化与体验改进**

- 后台 Agent 会话现在支持**后台静默更新**新版本，无需冷启动等待。
- 内置命令和 Skills 在 `/` 菜单中的描述更加清晰。
- 订阅切换建议从 Toast 改为启动公告栏显示。
- 从 Agents 分组视图 dispatch 会话时，会使用当前 Agents 视图所在的目录作为工作目录。

---

### **总结评价**

v2.1.163 是一次**企业友好型**更新：

- **最大亮点**：新增版本强制策略（`requiredMinimumVersion`），对 Team / Enterprise 管理非常实用。
- **Agents 与 Hooks** 进一步成熟，稳定性显著提升。
- 整体以**可管理性 + 细节打磨**为主，适合企业用户和重度 Agents 用户。

---

需要我帮你重点提取**企业管理相关**、**Hooks 相关**或**Agents 稳定性**部分的详细说明吗？

## 2.1.162

**版本号**：v2.1.162  
**更新重点**：**用户体验优化 + Agents 功能增强 + 稳定性修复**。本次更新显著改善了交互流畅度和信息展示，同时修复了多个边缘场景下的问题。

---

### **一、新功能与重要改进**

1. **Agents JSON 输出增强**
   - `claude agents --json` 现在会包含 `waitingFor` 字段，显示等待中的会话当前被什么阻塞（例如权限提示）。

2. **工具调用改进**
   - `--tools` 参数中明确指定 `Grep` / `Glob` 时，现在能正确启用原生嵌入式搜索工具（之前会被静默忽略）。

3. **/effort 命令优化**
   - 使用 `/effort` 设置努力级别时，会明确提示该设置是否会成为**新会话默认值**。

4. **斜杠命令交互优化**
   - 在自动补全菜单中点击斜杠命令（`/command`），现在会**填入输入框**而不是立即执行，按 Enter 后再运行（更安全、更符合用户习惯）。

5. **远程控制（Remote Control）展示优化**
   - 现在以**持久页脚胶囊（footer pill）**形式显示，并提供会话链接，不再是仅启动时的一次性消息。

6. **IDE 名称更新**
   - 将 “Windsurf” 重命名为 “Devin Desktop”（跟随官方品牌重命名）。

7. **启动体验大幅优化**
   - 启动信息更安静：按严重程度分组显示。
   - 启动警告更短、更清晰，并给出具体修复建议。
   - 启动提示和公告合并为一行。

---

### **二、Bug 修复**

**核心稳定性修复**：

- 修复配置目录只读时启动卡死的问题，现在会使用内存配置并显示错误提示。
- 修复 WebFetch 权限规则对内置预批准域名不生效的问题。
- 修复 Windows 下权限规则对反斜杠路径和大小写不匹配的问题。
- 修复会话开始时按 Esc 中断被静默忽略的问题。
- 修复包含 Emoji 的描述导致 API 400 错误的问题。
- 修复 MCP 服务器超时配置低于 1000ms 时被错误处理的问题。

**Agents 相关修复**：

- 修复 Agents 状态文本在宽终端下被截断的问题。
- 修复 Agents 会话名称过长被截断的问题。
- 修复从 Agents 列表附加运行中会话偶尔直接弹回列表的问题。
- 修复 Ctrl+V 粘贴图片在 Agents 视图中无效的问题。
- 修复后台会话启动失败时会话丢失的问题。
- 修复跨会话消息（SendMessage）在深层 TMPDIR 路径下失效的问题。

**其他修复**：

- 修复 LSP 工具 `workspaceSymbol` 操作无结果的问题。
- 修复后台服务重启后首次附加会话卡顿 5 秒的问题。
- 修复失败回复丢失的问题。

---

### **三、其他变更**

- 移除了部分启动消息（“Claude in Chrome enabled”、“marketplace installed”等）。
- 模型自动更新和团队引导提示现在作为安静通知显示在 Logo 下方。
- 提升了整体渲染性能和错误提示的友好度。

---

### **总结评价**

v2.1.162 是一次**体验向**的迭代更新：

- **亮点**：交互更友好（命令填充、进度展示、持久状态）、启动更安静、信息展示更清晰。
- **修复重点**：解决了 Agents 使用中的多个卡顿、截断和边缘 Bug。
- 整体适合重度使用 Claude Agents 的用户，稳定性进一步提升。

---

需要我帮你**突出某个模块**（如 Agents 相关、安全相关、Windows 相关）做更详细说明吗？

## 2.1.161

**版本号**：v2.1.161  
**更新重点**：功能增强 + 大量稳定性修复，重点优化了 **Agents 工作流**、**遥测指标** 和 **多平台兼容性**。

---

### **一、新功能与改进**

1. **OpenTelemetry 指标增强**
   - `OTEL_RESOURCE_ATTRIBUTES` 配置的值现在会作为标签（Labels）添加到指标数据点上。
   - 支持按团队、仓库等自定义维度对使用量进行切片分析。

2. **Claude Agents 界面优化**
   - 当任务被扇出（fanned out）时，列表行现在会显示 `done/total` 进度。
   - Peek 视图会优先显示耗时最长的子任务。

3. **MCP 管理改进**
   - `/mcp` 命令现在会把**从未登录过的 claude.ai connectors** 折叠收起，显示为 “Show unused connectors”。

4. **并行工具调用优化**
   - 并行执行工具时，如果某个 Bash 命令失败，不会再取消同批次的其他工具调用，每个工具独立返回结果。

5. **全屏模式（Fullscreen）改进**
   - Linux 下剪贴板现在优先使用 `wl-copy` / `xclip` / `xsel`。
   - 同时复制到剪贴板和 PRIMARY 选择区（支持鼠标中键粘贴）。
   - 提示信息会根据终端显示正确的快捷键。

---

### **二、Bug 修复（重点修复）**

- 修复了 `forceLoginOrgUUID` / `forceLoginMethod` 管理策略导致第三方供应商（Bedrock、Vertex、Foundry 等）无法登录的问题。
- 修复后台 Subagent 输出在 `--output-format text/json` 时污染标准输出的问题。
- 修复 `/usage-credits` 命令对 Team/Enterprise 管理员跳转错误的问题。
- 修复 `/autofix-pr` 在 git worktree 或非默认分支下误报的问题。
- 修复 `--resume` 选择器在非 git worktree 目录下不显示当前会话的问题。
- 修复 Windows 下直接调用 bash 的 hooks（如 `/usr/bin/bash script.sh`）报错的问题。
- 修复 OpenTelemetry 日志事件在初始化完成前被静默丢弃的问题。
- 修复 `claude mcp list/get/add` 会打印敏感信息（secrets）的问题（现已做脱敏处理）。
- 修复 Workflow agents 在 isolation 模式下无法编辑自身 worktree 文件的问题。
- 修复后台会话启动时使用旧模型的问题。
- 修复恢复会话后渲染 Write 工具结果可能崩溃的问题。
- 修复已完成 Subagent 在出错时仍显示为运行中的问题。
- 修复当 `CLAUDE_CODE_TMPDIR` 设置为深路径时出现的 `EADDRINUSE` 错误。

---

### **三、性能与体验优化**

- 显著提升终端渲染性能（稳定了布局引擎的 JIT 编译）。
- 提升了大文件写入时的渲染性能。
- **[VSCode 插件]** 新增提示：建议关闭终端 GPU 加速（或运行 `/terminal-setup`）来解决乱码问题。

---

### **总结评价**

v2.1.161 是一次**以稳定性和可观测性**为主的更新：

- **亮点**：Agents 进度展示更清晰、并行工具调用更健壮、遥测指标维度更丰富。
- **修复重点**：解决了大量后台会话、权限策略、Windows 兼容性和安全脱敏问题。
- 整体体验更加成熟可靠，尤其适合重度使用 Agents 和后台任务的用户。

---

需要我帮你重点标注**安全相关**、**Agents 相关**或**企业管理策略相关**的变更吗？

## 2.1.160

### **版本概述**

**版本号**：v2.1.160  
**主要亮点**：大幅提升了**安全性**（防止意外命令执行），并修复了大量后台会话（Background Session）和 Windows 平台的稳定性问题。

---

### **一、重要安全改进（重点关注）**

1. **新增写入保护机制**
   - 在修改 shell 启动文件（`.zshenv`、`.zlogin`、`.bash_login`）和 `~/.config/git/` 前会**明确提示**用户，防止恶意或意外命令执行。

2. **acceptEdits 模式加强保护**
   - 现在修改可能授予代码执行权限的构建工具配置文件时（如 `.npmrc`、`.yarnrc`、`.bazelrc`、`.pre-commit-config.yaml` 等）会**主动提示**用户确认。

---

### **二、功能改进**

- **编辑流程优化**：使用 `grep` / `egrep` / `fgrep` 查看单个文件后，无需再单独执行 `Read`，即可直接编辑。
- **动态工作流关键词变更**：原 `workflow` 触发词已废弃，现在统一使用 **`ultracode`** 触发高强度工作流。

---

### **三、主要 Bug 修复**

**后台会话（Background / Agents）相关修复**（占比较大）：

- 恢复已完成会话时不再丢失聊天记录和重复运行原始提示。
- 修复后台会话长时间挂起后重新连接丢失上下文的问题。
- 修复 `claude --bg` 冷启动时偶发的 “socket missing” 错误。
- 优化了后台 Agent 会话的打开性能和状态显示问题。

**Windows 平台修复**：

- 修复 WSL 下复制选中内容无法写入 Windows 剪贴板的问题。
- 修复 Windows 下后台会话占用目录无法删除的问题。
- 修复 Windows 高负载下按键（Esc、方向键、输入）无响应的问题。
- 修复文件链接（file:///）在 Windows 终端下路径错误的问题。

**其他重要修复**：

- 修复语音模式在包含非 ASCII 字符的路径下无法连接的问题。
- 修复 CJK 输入法（IME）输入框位置错乱的问题。
- 修复终端同步输出标记导致的渲染问题（Apple Terminal、tmux 等）。
- 修复 Vim 模式下 `p` 粘贴位置错误的问题。

---

### **四、其他变更**

- 移除了一些过时的环境变量和提示（如 JetBrains 插件建议）。
- 优化了自动模式（Auto Mode）的分类器性能，减少不必要的推理。
- 改进后台进程退出时的清理逻辑（先发送 SIGTERM，再 SIGKILL）。
- 提升了整体稳定性和用户体验。

---

**总结评价**：
此次版本**安全性显著提升**，同时重点修复了**后台会话**和 **Windows 用户** 的痛点，是一次以**稳定性 + 安全**为导向的更新。

---

需要我帮你重点提取某个部分（例如安全相关、后台会话相关、Windows 修复等）做更详细说明吗？

## 2.1.159

优化内部结构

## 2.1.158

一、主要新功能（New Features）

Auto Mode 正式支持更多平台（核心更新）Auto Mode（自动模式）现在已在以下平台可用：
Amazon Bedrock
Google Vertex AI
Anthropic Foundry
支持的模型包括：
Claude Opus 4.7
Claude Opus 4.8
开启方式：
设置环境变量：BashCLAUDE_CODE_ENABLE_AUTO_MODE=1

版本总结

版本类型：功能扩展版本（小更新）
重要程度：对于使用 Bedrock、Vertex 或 Foundry 部署的企业用户和高级用户非常有价值。
影响范围：主要影响在云端平台（非直接 Anthropic API）使用 Opus 4.7 / 4.8 的用户。
其他：本次更新没有新增其他功能、也没有 Bug 修复，仅增加了 Auto Mode 的支持范围。

实际意义

Auto Mode 是 Claude Code 中非常强大的功能，它能让 Claude 自动判断是否需要使用工具、执行代码、创建 Workflow 等，显著提升智能程度和自动化能力。
此前 Auto Mode 仅在直接使用 Anthropic API 时可用，现在扩展到主流企业级部署平台，方便更多公司用户在生产环境中使用。

## 2.1.157

Claude Code v2.1.157 版本更新记录（简体中文整理分析）
以下是对 v2.1.157 版本更新内容的结构化翻译 + 分类整理：

一、主要新功能（New Features）

本地 Skills 插件自动加载（重要更新）
位于 .claude/skills 目录下的插件现在自动加载，无需通过插件市场安装。

插件初始化命令
新增 claude plugin init <name> 命令，可快速在 .claude/skills 目录下创建新插件脚手架。

插件命令自动补全
/plugin 命令的参数现在支持自动补全（子命令、已安装插件、市场插件）。

Agents 配置增强
settings.json 中的 agent 字段现在对 dispatched sessions 生效。
可使用 --agent <name> 参数进行覆盖。

工作树切换能力
EnterWorktree 现在支持会话中途切换 Claude 管理的工作树。

遥测增强
tool_decision 遥测事件在开启 OTEL_LOG_TOOL_DETAILS=1 时，会包含工具参数（bash 命令、MCP/技能名称）。

二、体验与功能优化（Improvements）

Claude 管理的工作树在 Agent 完成后保持解锁状态，方便使用 git worktree remove/prune 清理。
显著提升长会话和恢复会话的性能（减少重复渲染计算）。
/terminal-setup 现在默认在 VS Code / Cursor / Windsurf 集成终端中禁用 GPU 加速，防止文字渲染错乱。
“Feature of the Week” 领取状态移至状态栏显示。
claude agents 中斜杠命令自动补全支持子字符串匹配。
新增 /config 设置 “Workflow keyword trigger”，可关闭单词 “workflow” 自动触发动态工作流。
移除部分启动提示（如沙箱提示、IDE 提示），减少干扰。
按 Backspace 取消 Workflow 触发请求（与 Alt+W 相同）。

三、Bug 修复（Bug Fixes）
本次修复内容较多，重点覆盖了后台 Agent、工作树、WSL、终端渲染等方面：

修复粘贴损坏/零字节图片导致请求崩溃的问题。
修复 Auto 模式和 Bypass-Permissions 模式下仍弹出沙箱网络权限提示的问题。
修复后台 Agent 完成会话后未正确退休的问题。
修复 Esc 键无法取消 “opening…” 状态导致列表卡死的问题。
修复后台工作树在 30 天清理后成为孤儿的问题。
修复从睡眠唤醒后会话日期错误的问题。
修复 tmux 中 copy-on-select 无法复制到系统剪贴板的问题。
修复 --resume 无法显示后台子 Agent 的问题。
修复 WSL 下图片粘贴、截图粘贴支持问题，并新增从 Windows 资源管理器拖拽图片支持。
修复多个终端渲染、快捷键、剪贴板相关 Bug。
修复 VS Code 中 Stop 按钮无法停止后台子 Agent 的问题。
修复 Opus 4.8 的 Fast Mode 指示器不显示的问题。

版本总结
v2.1.157 是一个以开发者体验和易用性为主的版本。
核心亮点：

本地插件系统大幅简化：现在可以直接在 .claude/skills 目录开发和使用插件，无需市场。
插件开发友好度提升（新增 plugin init + 自动补全）。
工作树管理和后台 Agent 稳定性继续加强。
性能和细节体验优化明显，尤其适合长期使用和大项目场景。

建议：
如果你经常开发自定义 Skills/插件，或者大量使用 Agents 和 Worktree，这个版本值得更新。

## 2.1.156

Claude Code v2.1.156 版本更新记录（简体中文整理）

一、主要更新内容
这是一个纯 Bug 修复版本，内容非常简洁且针对性强。
Bug 修复（Bug Fixes）

修复了 Opus 4.8 使用时的一个关键问题：
当使用 Claude Opus 4.8 模型时，思考块（thinking blocks） 被错误修改，导致向 Anthropic API 发送请求时出现错误。

## 2.1.154

Claude Code v2.1.154 版本更新记录（简体中文整理分析）
以下是对 v2.1.154 版本更新内容的结构化翻译 + 分类整理：

一、主要新功能（New Features）

Claude Opus 4.8 正式发布（最大亮点）
Opus 4.8 已上线，默认使用 High Effort（高智能模式）。
新增 /effort xhigh 指令，可用于最难、最复杂的任务。

动态工作流（Dynamic Workflows） —— 重磅功能
你可以直接让 Claude 创建一个 Workflow，它会在后台自动编排数十到数百个 Agent 协同工作。
适合处理大型、复杂任务。
使用 /workflows 命令可查看所有运行中的 Workflow。

Opus 4.8 Fast Mode 价格大幅降低
现在只需标准模式 2倍价格，即可获得 2.5倍速度。

精简系统提示（Lean System Prompt）成为默认
除 Haiku、Sonnet、Opus 4.7 及更早版本外，所有模型默认使用精简系统提示（提升效率）。

Agents 增强
在 claude agents 中输入 ! <命令>，即可作为一个可随时附着/分离的后台会话执行 Shell 命令。
等价命令：claude --bg --exec '<command>'。

插件管理优化
插件可在 plugin.json 中声明 defaultEnabled: false，默认不启用。
/plugin Discover 标签页会根据当前目录相关性推荐插件，并标注“suggested for this directory”。

二、体验与功能优化（Improvements）

/simplify 命令行为变更：现在只执行清理类审查（复用、简化、效率、抽象层次），不再进行完整的 Bug 狩猎审查。
/effort 滑块标签从 “Speed/Intelligence” 改为 “Faster/Smarter”，更清晰。
←← 快捷键打开 Agents 视图，现在在 Bedrock、Vertex、Foundry 以及关闭遥测时均可使用。
Chrome 浏览器集成：支持通过 /chrome → Select browser… 选择要使用的浏览器。
Streaming Tool 执行现在默认始终开启（不再受功能旗标限制）。
/model 选择器在 Fast Mode 开启时会显示对应价格。
改进自动模式的安全分类器，特别加强了对大批量代码库内容外泄的检测。

三、Bug 修复（Bug Fixes）
本次修复重点集中在后台工作流、权限控制、安全性和稳定性：

修复 rm -rf $HOME 在 HOME 路径带斜杠时未被正确拦截的问题。
修复 $TMPDIR 在沙箱与非沙箱命令中解析不一致的问题。
修复大量后台 Agent（Background Agent）相关问题（固定、卡住、重复启动、CPU 100% 等）。
修复 Subagent 绕过工作树隔离保护的问题。
修复 Windows 更新失败时的提示不清晰问题。
修复 VS Code 扩展关闭时进程未正确清理的问题。
修复 /mcp 工具列表在工具名过长时的渲染问题。
修复自动模式在安全分类器 Token 用尽时错误阻挡操作的问题。
其他终端渲染、快捷键、链接点击、计划文件命名等细节修复。

版本总结
v2.1.154 是一个重量级功能更新版本，核心亮点如下：

Opus 4.8 正式到来 + Dynamic Workflows（动态工作流）是本次最大升级，极大提升了处理复杂大型任务的能力。
性能与成本优化显著（Fast Mode 更便宜、精简 Prompt 默认开启）。
Agents 后台执行能力进一步增强（! 命令非常实用）。
整体稳定性和安全性继续打磨。

适合人群：重度用户、需要处理大型项目、喜欢使用 Agent 集群和 Workflow 的开发者会获得明显体验提升。

## 2.1.153

以下是对 v2.1.153 版本更新内容的结构化翻译 + 分类整理：

一、主要新功能（New Features）

插件市场 Git 来源优化
GitHub/Git 插件市场源新增 skipLfs 选项，可在 clone 和 update 时跳过 Git LFS 大文件下载（节省时间和流量）。

npm 全局安装提示
当 npm 全局安装无法自动更新时，Claude Code 会显示一次性提示。
/doctor 命令会列出对应的修复建议。

Status Line 命令增强
Status line 脚本现在会收到 COLUMNS 和 LINES 环境变量，脚本可根据终端实际宽高调整输出格式。

Agents 功能改进
claude agents 的 dispatch 输入自动补全现在会建议原生斜杠命令和内置技能，不再仅限于项目技能。
PR 列显示优化：单个 PR 显示 PR #N，多个 PR 显示 N PRs。

诊断工具增强
claude doctor 现在会显示你上一次更新的结果。

认证提示合并
将 MCP Servers 和 Connectors 分别的“需要认证”启动通知合并为一条消息，避免重复。

macOS 后台 Agent 改进
后台 Agent 在「隐私与安全性」中统一显示为 “Claude Code”。
升级后权限授予继续有效。

二、体验与功能优化（Improvements）

模型选择记忆：
/model 命令现在会保存你的选择作为新会话默认模型（与 IDE 行为一致）。
在模型选择器中按 s 键仅切换当前会话模型（不再是 d）。

键位绑定提醒：
如果你自定义过 modelPicker:setAsDefault，需修改为 modelPicker:thisSessionOnly。

三、Bug 修复（Bug Fixes）
本次修复数量较多，重点集中在后台会话（Background Sessions）、MCP Servers 和 Windows 稳定性上：

修复了 v2.1.147 引入的 stateful MCP 服务器 reconnect 循环问题。
修复自定义 API Gateway 可能收到用户 OAuth 凭证而不是网关自身 Token 的回归 Bug。
修复 Subagent（Agent Tool）在多种模式下忽略 --strict-mcp-config 等配置的问题。
修复 Windows PowerShell 安装器失败时仍显示“安装完成”的问题。
修复 claude update 在 npm 安装时总是安装最新版而非指定通道版本的问题。
修复通过 transcript 文件路径恢复超多会话时内存占用过高（数 GB）的问题。
修复大量后台会话（background agent）相关 Bug：
僵尸会话、状态不同步、剪贴板失效、链接不可点击、键盘快捷键失效等。
修复 Windows 下 IME 候选框位置错误、颜色溢出等问题。

修复 /bg 在模型回复中途执行时的行为问题。
修复 Agent 在临时工作树中可能丢失输出的问题。
修复 VSCode 扩展在 Windows 上关闭时进程未正确退出的问题。
修复 Windows 更新失败后的回滚机制，现在会正确恢复原始可执行文件。

版本总结
v2.1.153 版本重点：

插件市场和 Git 集成更灵活（新增 skipLfs）。
后台 Agent 和长期会话稳定性大幅提升（修复了大量相关 Bug）。
用户体验细节优化（模型默认设置、状态栏适配、提示合并）。
安装与更新流程更可靠（尤其是 npm 和 Windows 用户）。

## 2.1.152

Claude Code v2.1.152 版本更新记录（简体中文整理分析）
以下是对该版本更新内容的结构化翻译 + 分类整理，方便阅读和理解：

一、主要新功能（New Features）

代码审查增强
/code-review --fix 现在支持自动应用审查意见到工作区文件。
会给出代码复用、简化、效率优化等建议。
/simplify 命令现在会调用 /code-review --fix 执行简化。

Skills（技能）能力提升
Skills 和斜杠命令（slash commands）现在可以在 frontmatter 中设置 disallowed-tools，可在技能激活期间禁用特定工具。
新增 /reload-skills 命令，可在不重启会话的情况下重新扫描技能目录。
SessionStart Hook 新增 reloadSkills: true 支持，让 Hook 安装的技能可立即在当前会话生效。
SessionStart Hook 可设置会话标题（sessionTitle）。

Hook 机制扩展
新增 MessageDisplay Hook 事件，允许 Hook 在显示助手消息时进行转换或隐藏。

插件市场管理增强
新增 pluginSuggestionMarketplaces 设置，管理员可白名单允许被推荐的组织插件市场。
claude plugin marketplace remove 命令新增 --scope 参数（user|project|local），与 add/install 等命令保持一致。

模型容错改进
当主模型不可用时，自动切换到配置的 --fallback-model，并在本次会话剩余时间内持续使用，而非每次请求都失败。

二、体验与功能优化（Improvements）

Auto 模式：不再需要手动确认同意即可使用。
Vim 模式：在 NORMAL 模式下按 / 现在会打开反向历史搜索（类似 bash/zsh 的 Ctrl+R）。
用量统计：/usage 命令现在会包含大型会话文件，并采用流式读取，内存占用保持平稳。
思考过程显示优化：
折叠的思考摘要现在至少显示 3 秒，支持 Markdown 渲染，最多显示 10 行（Ctrl+O 显示完整内容）。
全屏模式下，“Thinking for Ns” 指示器会实时计数，并在思考被中断时保留数值。

Workflow 工具：简化了进度显示，实时 Agent 数量仅在下方持久状态栏显示。
响应计时器：当有后台 Agent 或 Workflow 运行时，会显示等待提示，完成后显示累计时间。

三、Bug 修复（Bug Fixes）
较多且重要的修复包括：

修复长时间会话中终端样式退化的问题。
修复 Sandbox 警告在精简启动模式下不显示的问题。
修复加载 spinner 在工具运行时错误显示“仍在思考”的问题。
修复 Focus 模式下错误显示“隐藏消息数量”的问题。
修复点击工具结果中的链接时错误折叠区域的问题。
修复 Markdown 表格样式问题（边框、换行、空表头等）。
修复相同命令但不同环境变量的 MCP 服务器被错误去重的问题。
修复 /doctor 命令对已删除插件/市场的错误报告。
修复 Git 分支跟踪的插件无法更新问题。
修复远程 MCP 服务器在启用出口代理时的连接失败问题。
修复多个边缘场景下的崩溃和卡死问题（Agent 取消、权限提示、缓存统计等）。

版本总结
本次更新重点：

大幅增强代码审查和自动修复能力（/code-review --fix 是亮点）
显著提升 Skills / Hook 的灵活性和可扩展性
改善长时间会话的稳定性和使用体验
修复了较多实用 Bug，整体稳定性提升

适合人群：重度使用 Claude Code 进行代码开发、Agent 构建和长期会话的用户会明显受益。

## 2.1.150

以下是 **v2.1.150** 版本的更新内容整理（简体中文）：

### 🛠️ 内部基础设施改进

- **无用户可见变更**：此版本仅包含内部基础设施的优化和改进，不涉及任何面向终端用户的功能变化或问题修复。

## 2.1.149

以下是 v2.1.149 版本的更新内容整理（简体中文）：

### 🆕 新增功能

- **用量分类明细**：`/usage` 命令现在会按类别（技能、子智能体、插件、各 MCP 服务器的用量）展示限制使用情况的详细分类。
- **差异视图键盘滚动**：`/diff` 详情视图现在支持键盘滚动（方向键、j/k、PgUp/PgDn、空格、Home/End）。
- **任务列表渲染**：Markdown 输出现在支持渲染 GFM 任务列表复选框（`- [ ]` 待办 / `- [x]` 已完成）。
- **企业版新增设置**：添加 `allowAllClaudeAiMcps` 管理设置，支持在 `managed-mcp.json` 旁加载 claude.ai 云 MCP 连接器。

### 🐛 问题修复

#### 安全与权限相关

- **PowerShell 权限绕过修复**：修复了内置 cd 函数（`cd..`, `cd\`, `cd~`, `X:`）会无检测地更改工作目录，导致后续命令可读取工作区外文件的问题。
- **Git worktree 沙箱修复**：修复了沙箱写入允许列表在 git worktree 中覆盖整个主仓库根目录的问题，现在仅限于共享的 `.git` 目录（禁止 `hooks/` 和 `config`）。
- **PowerShell 规则修复**：修复了 PowerShell 前缀/通配符允许规则（如 `PowerShell(dotnet.exe build *)`）无法预批准原生可执行文件和脚本的问题。
- **变量跟踪修复**：修复了权限分析漏洞——解析器在 `cd/pushd/popd` 操作后误信任 `PWD/OLDPWD/DIRSTACK` 的过时变量跟踪值。
- **Bash 工具修复**：修复了 `find` 命令在 macOS 上耗尽系统文件/vnode 表导致主机崩溃的问题。

#### 会话与界面

- **启动卡死修复**：修复了托管设置批准对话框在启动接受后导致终端冻结的问题。
- **会话创建修复**：修复了 `/ultraplan` 和远程会话创建时因工作树无实际更改而失败并提示“无法捕获未提交更改”的问题。
- **脚本路径修复**：修复了 `otelHeadersHelper` 在脚本路径包含空格时静默失败的问题；此类失败现会在 `/doctor` 和调试日志中报告。
- **思考动画修复**：修复了思考转轮在工具调用和新的思考片段间保持琥珀色不变的问题。
- **输出统计修复**：修复了折叠的 Bash 输出对包含许多短行的输出报告错误隐藏行数的问题。

#### 命令与输入

- **命令提示修复**：修复了斜杠命令参数提示在提示溢出输入框时截断末尾键入字符的问题。
- **Tab 补全修复**：修复了技能 frontmatter 名称与目录名不同时，Tab 补全后不显示参数提示和渐进式参数建议的问题。
- **状态栏修复**：修复了状态栏显示用户基准 `/effort` 设置而非技能/智能体的 `effort: frontmatter` 实际生效值的问题。

#### 历史与编辑

- **Ctrl+O 修复**：修复了 Ctrl+O 转录视图打开时直接冻结，无法跟踪新消息的问题。
- **历史编辑修复**：修复了编辑已调用的提示历史条目后，用方向键继续上下导航时丢失编辑内容的问题。
- **/config 修复**：修复了 `/config` 退出摘要中，切换无关设置后错误报告“自动压缩”和“主题”被更改的问题。
- **重复历史修复**：修复了刚提交的提示可能在向上箭头历史中重复出现的竞态条件问题。

#### 其他修复

- **/insights 修复**：修复了缓存的会话元数据缺少可选字段时 `/insights` 崩溃的问题。
- **工具调用修复**：修复了格式错误的 PowerShell 和 History 工具调用（缺少输入）在转录折叠中被错误归类为读取操作的问题。
- **远程会话修复**：修复了从 claude.ai 或 Claude 移动端重命名 Remote Control 会话后，`claude --resume` 不更新本地会话名的问题。
- **全屏按钮修复**：修复了全屏模式下点击“跳到底部”按钮后不立即消失的问题。

### 📈 改进

- **反馈报告增强**：改进了 `/feedback` 报告，现在会包含上下文压缩之前发生的对话内容，便于排查长会话早期的问题。

## 2.1.148

以下是 **v2.1.148** 版本的更新内容：

### 🐛 问题修复

- **Bash 工具退出码错误**：修复了部分用户在使用 Bash 工具时，**所有命令都返回退出码 127** 的问题

### 📌 补充说明

- 此问题是 **v2.1.147 版本引入的回归缺陷**
- 退出码 127 通常表示“命令未找到”，但在该缺陷下即使命令正常执行也会错误地返回 127
- v2.1.148 是一个**补丁修复版本**，仅包含上述修复

### ✅ 建议

如果你当前使用的是 **v2.1.147** 且遇到了 Bash 命令执行异常（所有命令都报错退出），建议立即升级到 v2.1.148。

## 2.1.147

以下是 **v2.1.147** 版本的更新内容，已按类别整理为简体中文：

### 🚀 新功能与行为变更

- **固定后台会话**：按 `Ctrl+T` 固定的后台会话现在支持：空闲时保持存活、在 Claude Code 更新时原地重启以应用更新、仅在内存压力且**非固定**会话被清除后才会被释放
- **`/code-review` 命令升级**：原 `/simplify` 已更名为 `/code-review`。现在可以按选择的努力程度（如 `/code-review high`）报告正确性缺陷；传递 `--comment` 参数可将结果发布为 GitHub PR 内联评论。**原有的清理与修复行为已被移除**
- **自动更新器改进**：
  - 对临时网络故障进行重试
  - 失败时报告具体的错误类别和操作系统错误码
  - 更新失败时显示当前版本
- **提示历史优化**：不再记录连续的重复条目 — 按上箭头调出之前的提示并再次提交，不会再添加一份副本

### 🐛 问题修复

#### 企业登录与策略

- 修复了 `forceLoginOrgUUID` 和 `forceLoginMethod` 托管策略未对第三方身份提供商及 API-Key 会话强制生效的问题

#### 终端与显示

- **HTML 实体转义**：修复了 `!` 命令输出中的 `&` 被错误显示为 `&amp;` 的问题，导致在无头机器上无法正确复制 `gcloud auth login` 等命令返回的 URL
- **`/help` 命令**：修复了小终端在非全屏模式下，帮助页面标签头显示错误且每页只显示一条命令的问题
- **全屏频闪**：修复了 Windows Terminal 中后台附加会话在 Claude 流式输出时的全屏频闪问题
- **GNOME 终端**：修复了右键粘贴与中键粘贴无法插入文本的问题
- **Agent 视图**：修复了 Windows 上后台会话结果包含宽字符（如 CJK 字符）时，Agent 列表中出现的过时行与重复行问题
- **滚动挂起**：修复了 Windows 上等待滚动稳定时罕见的挂起问题

#### Shell 与脚本执行

- **Shell 快照**：修复了丢弃以单下划线开头的用户函数的问题（该问题导致引用这些函数的别名失效）
- **PowerShell 工具**：
  - 修复了依赖默认格式化器的命令输出被丢弃的问题
  - 修复了通过 `winget` 或 Microsoft Store 安装 `pwsh` 后，执行命令以退出码 1 失败的问题（此为回归问题）
  - **Windows**：修复了对 PowerShell 脚本选择“是，不再询问”后，写入的规则无法在后续执行中真正匹配的问题
- **Hook 条件**：修复了类似 `PowerShell(git push*)` 的条件从未匹配的问题（此前只有 `PowerShell(*)` 有效）

#### 后台会话与会话管理

- 修复了 `/background` 拒绝仅包含技能或自定义斜杠命令（无普通文本输入）的会话的问题
- 修复了后台会话再次提示用户已选择“不再询问”的工具权限的问题
- **Windows 工作树**：修复了删除后台任务工作树时，错误地跟随 NTFS 结点进入主仓库的问题

#### MCP 与插件

- **MCP 分页**：修复了分页服务器上 `resources`、`templates` 和 `prompts` 列表丢失第 1 页之后项目的问题
- **插件 Agent**：修复了在 `tools:` 中声明多个 `Agent(...)` 类型的插件 Agent 时，frontmatter 只保留最后一个条目的问题
- **插件组件计数**：修复了当插件清单中列出的路径与其默认目录重叠时，`claude plugin details` 和 `/plugin` 中的组件计数被加倍的问题

#### 其他修复

- **`/effort` 命令**：修复了打开时滑块定位在错误级别的问题 — 现在从**当前** effort 级别开始
- **未知斜杠命令**：修复了无头/SDK 模式中未知斜杠命令静默无效的问题 — 现在会显示错误信息
- **粘贴文本**：修复了粘贴的文本被传递为不可读的 `[Pasted text #N]` 占位符而非实际内容的问题
- **自动模式**：修复了当用户或技能明确依赖 `AskUserQuestion` 时自动模式错误抑制该功能的问题；自动模式分类器现在会将用户回答作为意图信号
- **对话框**：修复了 `/theme` 的“新建自定义主题”与颜色编辑器对话框不响应 `Esc` 键的问题
- **Agent SDK**：修复了流式会话结束时未捕获的异常
- **环境变量**：修复了 `CLAUDE_CODE_SUBAGENT_MODEL` 未应用于 Agent 团队生成的子进程的问题
- **斜杠命令分隔符**：修复了斜杠命令后跟制表符或换行符时被视为未知命令的问题
- **UI 布局**：修复了 `/plugin`、`/status`、`/mobile`、`/sandbox` 和 `/permissions` 菜单中的多处间距和布局异常
- **图片处理**：修复了剥离图片后导致模型反复重新读取已不存在媒体内容的问题

## 2.1.146

以下是 v2.1.146 版本的更新内容，已按类别整理为简体中文：

### 🚀 功能变更

- **命令重命名**：将 `/simplify` 命令更名为 `/code-review`，并支持可选的 `effort level` 参数（例如 `/code-review high`）

### 🐛 问题修复

#### 交互与界面

- **自动模式**：当用户或技能明确依赖 `AskUserQuestion` 时，自动模式不再抑制该功能的执行
- **对话框**：修复了 `/theme` 颜色编辑器与“新建自定义主题”对话框无法响应 `Esc` 键关闭的问题
- **终端兼容**：
  - 修复了 GNOME 终端中右键粘贴与中键粘贴无法插入文本的问题
  - 修复了 Windows Terminal 中后台附加会话在 Claude 流式输出时出现的全屏频闪问题

#### 系统与工具

- **Windows PowerShell**：修复了通过 `winget` 或 Microsoft Store 安装 `pwsh` 后，执行工具时提示“命令行无效”的错误（此为 v2.1.124 引入的回归问题）
- **后台任务**：
  - 修复了 `/background` 拒绝那些仅包含技能或自定义斜杠命令输入（无普通文本）的会话问题
  - 修复了后台会话会再次提示用户已选择“不再询问”的工具权限问题
- **Windows 工作树**：修复了删除后台任务工作树时，错误地跟随 NTFS 结点进入主仓库的问题

#### 网络与集成

- **MCP 协议**：修复了使用分页服务器时，`resources/list`、`resources/templates/list` 及 `prompts/list` 接口会丢失第1页之后项目的问题
- **Agent SDK**：修复了流式会话结束时抛出未捕获异常的问题

#### 策略与安全

- **托管策略**：修复了 `forceLoginOrgUUID` 和 `forceLoginMethod` 策略未能对第三方提供商及 API-Key 会话强制执行的问题

### 🔧 其他改进

- **自动更新器**：
  - 修复了更新失败时状态栏不显示当前版本的问题
  - 改进了网络容错性：原生版本检查和下载现在会在遇到临时网络故障时自动重试，而非立即失败
- **子代理模型配置**：修复了 `CLAUDE_CODE_SUBAGENT_MODEL` 环境变量未传递给多代理会话中的子进程的问题
- **性能优化**：改进了大文件编辑场景下的差异（diff）渲染性能

## 2.1.145

**2.1.145 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **`claude agents --json` 命令**  
   新增 JSON 输出模式，方便脚本化处理（如 tmux-resurrect、状态栏、自定义会话选择器等）。

2. **OpenTelemetry 追踪增强**  
   在 `claude_code.tool` OTEL spans 中新增 `agent_id` 和 `parent_agent_id` 属性，并优化了后台子 Agent 的追踪嵌套关系（现在正确嵌套在父 Agent 下）。

3. **状态栏信息丰富**  
   Status line 的 JSON 输入现在会包含检测到的 GitHub 仓库和 PR 信息。

4. **插件市场详情大幅增强**  
   `/plugin` 的 Discover（发现）和 Browse（浏览）界面在安装前即可显示插件包含的：
   - Commands（命令）
   - Agents（智能体）
   - Skills（技能）
   - Hooks（钩子）
   - MCP / LSP Servers

5. **Agent 标签页标题优化**  
   `claude agents` 的终端标签页现在会显示“等待输入”的数量，方便 Alt+Tab 切换窗口时快速知道哪些 Agent 需要关注。

6. **交互体验改进**  
   Slash 命令和 @-mention 建议列表在全屏模式下支持**鼠标悬停和点击**。

7. **Hook 输入字段扩展**  
   Stop 和 SubagentStop Hook 现在会收到 `background_tasks` 和 `session_crons` 字段。

### 二、改进与优化（Improvements）

- Read 工具优化：当读取整个文件超出 Token 限制时，不再报错，而是返回**前一部分内容**并标注 “PARTIAL view” 提示。

### 三、Bug 修复（Bug Fixes）

本次版本共修复 **15+** 个问题，主要涉及权限、插件、UI 稳定性等方面：

**权限与安全**

- 修复 Bash 命令中通过变量赋值绕过环境变量白名单的权限漏洞。

**MCP 与插件**

- 修复 MCP 提示命令缺失参数时显示原始错误的问题，现在会清晰提示缺失参数和正确用法。
- 修复 `claude plugin validate` 对 Skill 配置校验不严格的问题。
- 修复 Skill 使用 `context: fork` 时可能导致的无限循环。

**界面与交互**

- 修复终端 resize 或重新聚焦后 Spinner 和耗时显示冻结的问题。
- 修复任务列表同时创建时顺序混乱的问题。
- 修复 Voice Push-to-Talk 在 Agent View 中无效的问题。
- 修复 PR 状态徽章更新不及时的问题。

**其他修复**

- 修复 Windows PowerShell 5.1 下跨项目恢复提示失败的问题。
- 修复 Agent Teams 中非 ASCII 名称导致 API 调用失败的问题。
- 修复 `/review` 命令在 Classic Projects 仓库中报错的问题。
- 修复部分无用或错误的提示横幅。
- 修复 Anthropic 市场安装状态错误显示的问题。

---

### **总结评价**

**2.1.145 是一个中小型功能增强 + 稳定性修复版本**。

- **亮点**：
  - `claude agents --json` 为脚本化和自动化提供了强力支持。
  - `/plugin` 市场信息大幅丰富，安装前即可全面预览。
  - Agent 标签页等待计数和鼠标支持，提升了多 Agent 场景下的使用体验。
  - OTEL 追踪进一步完善，适合需要监控和调试复杂 Agent 系统的用户。

- **重点方向**：提升脚本化能力、插件市场透明度和多 Agent 管理体验，同时修复了若干实用性 Bug。

**推荐升级**：正在使用 `claude agents`、插件开发或需要脚本自动化管理的用户，建议尽快更新。

---

需要我帮您对比 **2.1.144** 与 **2.1.145** 的差异总结吗？

## 2.1.244

**2.1.144 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **后台会话恢复功能**  
   新增 `/resume` 对后台会话的支持。通过 `claude --bg` 或 Agent View 启动的后台会话现在会出现在会话列表中，并标记为 `bg`。

2. **后台子 Agent 完成通知增强**  
   后台子 Agent 完成时会显示已用时长，例如：“Agent completed · 3h 2m 5s”。

3. **插件市场信息完善**  
   `/plugin` 浏览和发现面板现在会显示插件的**最后更新时间**。

4. **模型选择行为变更**  
   `/model` 命令现在**仅修改当前会话**的模型。  
   在模型选择器中按 `d` 可设置为新会话的默认模型。

5. **用语规范化**  
   “extra usage” 统一更名为 “usage credits”，对应命令 `/extra-usage` 改为 `/usage-credits`（旧命令仍可使用）。

### 二、改进与优化（Improvements）

- 后台会话相关操作体验显著提升（`/bg`、detach、resume 等）。
- `/plugin` 在启用/禁用/卸载后自动返回已安装列表。
- 插件市场新增对 `CLAUDE_CODE_PLUGIN_PREFER_HTTPS` 的支持。
- `/doctor` 命令在 Hook 配置缺失时提供可执行的示例。
- 流式请求恢复机制改进（遇到卡住时会重试一次）。
- SDK / Headless 模式下 MCP 服务器启动速度优化（最快可提升 2 秒）。
- 调查问卷后的跟进提示更智能且上下文相关。

### 三、Bug 修复（Bug Fixes）

本次版本**重点修复了后台会话稳定性**，共修复 **35+** 项问题，主要包括：

**后台会话与 Agent 核心修复**

- 修复 macOS 下 Full Disk Access 保护文件夹导致后台会话崩溃的问题。
- 修复 `/resume`、会话唤醒、标题更新、目录保留等多项后台会话问题。
- 修复 Windows 下 Agent View 键盘响应、滚动、鬼影字符等问题。
- 修复后台会话 Worktree 隔离、Edit/Write 拒绝等逻辑问题。

**终端与显示**

- 修复窗口 resize 后输出乱码和长时间会话显示渐进损坏的问题。
- 优化 VS Code 中的 Spinner 渲染，减少闪烁。
- 修复关闭终端时附加后台会话导致的崩溃。

**模型与会话管理**

- 修复 `/model` 更改不生效、恢复会话模型丢失等问题。
- 修复 Bedrock / Vertex 用户无法选择 “Opus (1M context)” 的问题。

**插件与 MCP**

- 修复 MCP 分页工具列表只返回第一页的问题。
- 修复插件缓存、Skill 加载、配置解析等错误。
- 修复 Skill 在 Headless 模式下的权限问题。

**其他重要修复**

- 修复 API 不可达时启动挂起长达 75 秒的问题（现缩短至 15 秒超时）。
- 修复读取内容与扩展名不匹配的文件导致会话不可恢复的问题。
- 修复搜索工具误报错误、分支命令失败等多个边缘问题。

---

### **总结评价**

**2.1.144 是一个以后台会话体验为核心的大型稳定性优化版本**。

- **亮点**：`/resume` 对后台会话的支持 + 耗时显示，让长期运行的 Agent 管理更加完善；模型选择逻辑更合理。
- **重点方向**：大幅提升后台会话（`--bg` / Agent View）的稳定性和可用性，同时修复了大量终端渲染、插件、MCP 等老问题。
- **用户受益**：重度使用后台 Agent、长期运行任务、插件用户将获得最显著的体验提升。

**推荐程度**：**强烈建议升级**。该版本对后台会话的修复质量很高，能有效减少崩溃、卡死和状态错误。

---

需要我帮您对比 **2.1.143** 与 **2.1.144** 的主要差异吗？

## 2.1.243

> **2.1.143 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **插件依赖管理增强**
   - `claude plugin disable` 现在会拒绝禁用被其他插件依赖的插件，并给出可复制的依赖链禁用提示。
   - `claude plugin enable` 会自动强制启用所有传递依赖。

2. **插件市场 Token 预估**
   - `/plugin` 市场浏览面板新增**每轮上下文成本**和**每次调用 Token 预估**显示。

3. **工作树（Worktree）新配置**
   - 新增 `worktree.bgIsolation: "none"` 设置，允许后台会话直接编辑工作副本，而不进入独立 Worktree（适用于不适合使用工作树的项目）。

4. **PowerShell 工具优化**
   - PowerShell Tool 默认传递 `-ExecutionPolicy Bypass` 参数。
   - 可通过 `CLAUDE_CODE_POWERSHELL_RESPECT_EXECUTION_POLICY=1` 关闭此行为。

### 二、改进与优化（Improvements）

- 后台会话从空闲唤醒后，**自动保留之前设置的模型和 Effort 等级**。
- 在 Agent 会话中，`Shift+Tab` 现在会循环包含 Auto 权限模式。
- PowerShell Tool 在 Bedrock、Vertex、Foundry 等第三方平台上**默认启用**（可手动关闭）。
- `claude agents` 命令新增多个参数支持（`--add-dir`、`--settings`、`--mcp-config`、`--permission-mode`、`--model` 等），可统一设置仪表盘和后台会话默认值。
- `/bg` 和 `←` detach 操作大幅增强，现在能更好地保留权限模式、MCP 配置、Fallback 模型、危险跳过权限等设置。

### 三、Bug 修复（Bug Fixes）

本次版本共修复 **25+** 个问题，主要集中在以下方面：

**插件与依赖**

- 修复插件依赖处理相关问题。

**后台会话与 Agent**

- 修复 `/goal` 在后台 Shell 或子 Agent 仍在运行时错误触发的问题。
- 修复后台会话模型、权限、MCP 配置丢失的问题。
- 修复 `claude agents` 在 Windows 下的粘贴、响应中输入卡死等问题。
- 修复后台会话休眠唤醒后的假阳性卡死检测（尤其是 macOS App Nap）。
- 修复后台会话文件引用、Worktree 清理、权限模式继承等多个问题。

**核心稳定性**

- 修复损坏的 `.credentials.json` 导致 CLI 启动卡死或 OAuth 刷新失败的问题。
- 修复 Stop Hook 重复阻塞导致死循环的问题（新增 8 次上限，可配置）。
- 修复 `/loop`、Esc/Ctrl+C 中断相关问题。
- 修复 Windows 和 macOS 平台特定问题（PowerShell 进程、文件权限、粘贴等）。

**其他修复**

- 修复颜色环境变量（NO_COLOR）影响主界面颜色的问题。
- 修复会话删除后 Transcript 文件未清理的问题。
- 修复 5xx 错误提示指向错误地址的问题。
- 修复后台 daemon 启动时 launcher 缺失的回退问题。

---

### **总结评价**

**2.1.143 是一个以插件生态、后台会话稳定性和易用性为主的优化版本**。

- **亮点**：插件依赖管理更加智能和安全；后台会话（尤其是通过 `claude agents` 管理的）体验大幅提升，配置保留更完善；PowerShell 在 Windows 环境的支持更友好。
- **重点方向**：解决后台 Agent / 长期运行会话的各类顽固问题，提升企业/多插件用户的使用稳定性。
- **用户受益**：重度使用插件、后台 Agent、Worktree 和 Windows 用户将获得最明显改善。

**推荐升级**：建议所有活跃用户更新，特别是经常使用 `claude agents` 和后台会话的用户。

---

需要我帮您对比 **2.1.141** 与 **2.1.143** 的差异，或者针对某个新功能做详细使用说明吗？

## 2.1.142

> **2.1.142 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **`claude agents` 命令新增多项配置参数**  
   新增以下标志，可用于配置派发的后台会话：
   - `--add-dir`、`--settings`、`--mcp-config`、`--plugin-dir`
   - `--permission-mode`、`--model`、`--effort`、`--dangerously-skip-permissions`

2. **Fast Mode 模型升级**  
   Fast 模式默认切换至 **Opus 4.7**（之前为 Opus 4.6）。  
   如需固定使用旧版本，可设置环境变量：`CLAUDE_CODE_OPUS_4_6_FAST_MODE_OVERRIDE=1`

3. **插件 Skill 识别增强**  
   如果插件在根目录提供 `SKILL.md` 文件且没有 `skills/` 子目录，现在会自动作为 Skill 对外提供。

4. **插件详情显示优化**
   - `/plugin` 详情面板和 `claude plugin details` 命令现在会显示插件提供的 **LSP 服务器** 信息。

5. **GitHub App 连接保护**  
   `/web-setup` 在替换已存在的 GitHub App 连接前会给出明确警告。

### 二、改进与优化（Improvements）

- **响应式压缩（Compaction）优化**：首次压缩尝试现在会根据原始请求的溢出大小进行种子选择，避免浪费一次接近满上下文的重试。
- **Hook 配置错误提示更清晰**：当尝试为 `SessionStart`、`Setup`、`SubagentStart` 等事件配置 prompt/agent-type hook 时，会明确提示“应使用 command-type hook”。

### 三、Bug 修复（Bug Fixes）

本次版本共修复 **18 项** 问题，主要集中在后台会话稳定性、插件系统和跨平台兼容性上：

**后台会话与 Agent 相关修复**

- 修复后台会话无法识别已存在的 Git Worktree，导致 Edit 操作被阻塞的问题。
- 修复 macOS 睡眠/唤醒后后台会话消失和 daemon 重连失败的问题（现在正确检测时钟跳变）。
- 修复 daemon 在二进制升级（如 `brew upgrade`）后未干净退出，导致 Agent 崩溃循环的问题。
- 修复 Claude-in-Chrome 扩展连接时后台 Agent 崩溃循环的问题。
- 修复 `claude agents` 中点击链接、编辑器打开、颜色渲染等问题。
- 修复 `--dangerously-skip-permissions` 在休眠唤醒后不持久的问题。

**插件与 MCP**

- 修复 MCP_TOOL_TIMEOUT 对远程 HTTP/SSE MCP 服务器无效的问题（之前始终限制为 60 秒）。
- 修复插件缓存清理误删正在使用的插件目录的问题。
- 修复新发布插件显示“0 installs”、Skill 路径误报等问题。

**其他修复**

- 修复会话标题从链接中错误提取的问题。
- 修复远程客户端重复发送 `set_model` 请求导致 Transcript 出现重复记录的问题。
- 修复 Windows 下 `claude agents` 死锁、网络驱动器兼容性等问题。
- 清理了 Usage Policy 拒绝消息中过期的旧模型建议（`claude-sonnet-4-20250514`）。

---

### **总结评价**

**2.1.142 是一个中小型优化与修复版本**，重点提升了 `claude agents` 的可配置性和后台会话的稳定性。

- **亮点**：`claude agents` 可配置能力大幅增强；Fast Mode 升级到 Opus 4.7（性能/质量更好）；插件 Skill 和 LSP 支持更完善。
- **主要改进方向**：后台会话（尤其是跨睡眠、升级场景）的健壮性，以及插件生态的细节打磨。
- **用户受益**：经常使用 `claude agents`、后台 Agent、插件开发和 macOS/Windows 用户将获得明显改善。

**推荐升级**：建议正在使用 Agent 功能或插件的用户尽快更新，稳定性有一定提升。

---

需要我帮您对比 **2.1.141 ~ 2.1.143** 的版本差异总结吗？

## 2.1.141

> **2.1.141 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **Hook 机制增强**
   - Hook JSON 输出新增 `terminalSequence` 字段。  
     允许 Hook 在没有控制终端的情况下发送桌面通知、修改窗口标题、响铃等操作。

2. **插件安装方式优化**
   - 新增环境变量 `CLAUDE_CODE_PLUGIN_PREFER_HTTPS`。  
     在没有配置 GitHub SSH Key 的环境下，强制使用 HTTPS 克隆插件源。

3. **工作区身份联邦支持**
   - 新增 `ANTHROPIC_WORKSPACE_ID` 环境变量，用于 Workload Identity Federation，可将令牌限定到特定工作区。

4. **Agent 视图增强**
   - `claude agents --cwd <path>`：支持指定目录范围，仅显示该目录下的 Agent 会话。

5. **反馈功能升级**
   - `/feedback` 现在可以包含最近会话（最近24小时或7天），便于反馈跨会话的问题。

6. **Rewind（回退）菜单新增功能**
   - 新增 “Summarize up to here”（总结到此处），可在保留最近对话的同时压缩早期上下文。

7. **权限提示改进**
   - Auto 模式权限对话框现在会说明是由 `permissions.ask` 规则触发的。

8. **IDE 集成恢复**
   - 文件编辑权限提示中恢复了“在 IDE 中查看 Diff”选项（当连接 IDE 时）。

### 二、改进与优化（Improvements）

- 后台 Agent（通过 `/bg` 或 `←←` 启动）现在会**保留当前权限模式**，不再回退到默认模式。
- 已完成工作的 Agent，若后台 Shell 仍在运行，现在会正确移至 “Completed” 状态。
- 长思考期间的 Spinner 动画优化：10秒后变为琥珀色，提示 Claude 仍在工作。
- 插件菜单导航体验大幅提升（支持方向键、Tab 切换、点击等）。
- 后台侧查询在 Bedrock/Vertex 等平台无小模型配置时，改为回退使用主模型。

### 三、Bug 修复（Bug Fixes）

本次版本共修复 **40+** 个问题，覆盖面非常广：

**Agent 与后台任务**

- 修复 `claude agents` 在某些启动方式下显示错误页面的问题。
- 修复后台任务命名、状态显示、崩溃会话处理等问题。
- 空闲后台会话 5 分钟后自动清理。

**权限与会话管理**

- 修复权限模式切换时对话框不自动关闭的问题。
- 修复 Enter 键在权限提示打开时误提交输入框内容的问题。
- 修复 Hook 收到错误 `transcript_path` 的问题。

**界面与交互**

- 修复 Markdown 表格渲染回归问题。
- 修复历史记录（Up-arrow）、取消提示、快捷键冲突等问题。
- 修复语音、输入框、状态栏、主题颜色等多处显示问题。
- 修复插件菜单在短终端下的显示问题。

**插件与 MCP**

- 修复插件安装、详情显示、MCP 配置解析、连接状态显示等多个问题。
- 修复 `.mcp.json` 配置中使用 Shell 参数展开时被误判的问题。
- 修复远程 MCP 服务器不必要的断开和 401 认证问题。

**其他修复**

- Windows 平台 daemon 状态、管道文件锁定等问题。
- 第三方提供商（Bedrock 等）的认证、显示、模型 ID 问题。
- SDK、VS Code 语音模式、Windows 图片粘贴等平台特定修复。
- 分析事件、日志、OTel 等底层稳定性修复。

---

### **总结评价**

**2.1.141 是一个以稳定性、Agent 体验和开发者友好度为主的中大型更新版本。**

- **亮点**：Hook 能力进一步增强（桌面通知等）、Agent 管理更完善、Rewind 功能实用性提升。
- **重点方向**：大幅修复 Agent、插件、MCP、权限系统和跨平台稳定性问题，同时解决了很多长期存在的细节体验 Bug。
- **用户受益群体**：
  - 重度 Agent 用户
  - 使用 Hook 和 MCP 的开发者
  - 多设备 / 企业环境用户（HTTPS 克隆、工作区 ID）
  - VS Code + Windows 用户

**总体推荐**：强烈建议升级。该版本修复了大量可能导致卡顿、状态错误、功能失效的 Bug，稳定性显著提升。

---

需要我帮您对比 **2.1.140** 与 **2.1.141** 的差异，或针对特定功能做详细说明吗？

## 2.1.140

> **2.1.140 版本更新记录（简体中文整理与分析）**

### 一、主要改进（Improvements）

- **Agent 工具优化**：  
  `subagent_type` 参数匹配规则改进，现在支持**大小写不敏感**和**分隔符不敏感**（例如输入 `"Code Reviewer"` 可自动解析为 `code-reviewer`）。这大大提升了使用友好度，减少了参数输入错误。

- **视觉体验升级**：  
  更新了 Agent 的颜色配色方案，提升界面美观性和辨识度。

### 二、Bug 修复（Bug Fixes）

本次版本重点修复了大量稳定性、兼容性和使用体验问题，共计 **11 项** 修复：

1. **命令交互修复**
   - 修复了在 `disableAllHooks` 或 `allowManagedHooksOnly` 模式下，`/goal` 命令会静默卡住的问题。现在会显示明确的提示信息，而非永远不结束的加载指示器。

2. **设置系统优化**
   - 修复设置热重载（hot-reload）的一个回归问题：符号链接（symlink）的设置文件之前会导致错误的事件归属和多余的 `ConfigChange` 钩子触发。

3. **后台服务稳定性**
   - 修复 `claude --bg` 在后台服务即将空闲退出时出现 “connection dropped mid-request” 错误。
   - 修复企业级终端安全软件环境下后台服务启动失败的问题（增加启动等待时间）。
   - 修复远程托管设置在遇到 401 错误时不重试的问题，现在会强制刷新 token 并重试一次。

4. **配置持久化修复**
   - 修复托管模式的 `extraKnownMarketplaces` 自动更新策略未正确保存到 `known_marketplaces.json` 的问题。

5. **任务调度优化**
   - 修复 `/loop` 命令会调度多余唤醒来轮询已完成后台任务的问题（任务已通过完成通知机制）。

6. **Windows 平台专属修复**
   - 修复 Windows 下因缺失可执行文件（如 `gh`）导致的循环事件阻塞问题（之前会反复同步调用 `where.exe`）。

7. **工具调用验证**
   - 修复 `Read` 工具在 `offset` 参数传入带空格或 `+` 前缀的字符串时验证失败的问题。

8. **终端体验修复**
   - 修复原生终端在失去焦点时，光标无法保持在输入位置的问题。

9. **插件系统改进**
   - 当 `plugin.json` 中已设置对应键值时，若默认组件文件夹（如 `commands/`）被静默忽略，插件现在会**主动发出警告**。
   - 警告位置：`/doctor`、 `claude plugin list` 和 `/plugin` 命令中均可查看。

---

### **总结评价**

此版本属于**稳定性与体验优化型更新**：

- **重点方向**：提升后台服务可靠性、Windows 平台兼容性、配置系统健壮性和 Agent 使用便利性。
- **用户受益**：日常使用更流畅，尤其是使用 Agent、插件、后台模式（--bg）和远程托管设置的用户将获得显著改善。
- **推荐升级**：强烈建议所有用户更新，修复了多个可能导致卡死、启动失败、配置丢失的潜在问题。

整体质量较高，修复项多且覆盖面广，体现了团队对用户反馈和边缘场景的重视。

## 2.1.139

> **2.1.139 版本更新记录（简体中文整理与分析）**

### 一、新功能（New Features）

1. **Agent 视图（研究预览）**  
   新增统一的 Agent 视图，可在一个列表中查看所有 Claude Code 会话状态（运行中、等待用户输入、已完成）。  
   命令：`claude agents`  
   详细文档：<https://code.claude.com/docs/en/agent-view>

2. **/goal 命令**  
   重磅新功能！设置完成目标后，Claude 会跨多轮持续工作直到达成目标。  
   支持交互模式、`-p` 模式和 Remote Control。  
   界面上会实时显示已用时间、轮次、Token 数的悬浮面板。

3. **/scroll-speed 命令**  
   新增鼠标滚轮滚动速度调节命令，并提供实时预览。

4. **插件详情命令**  
   `claude plugin details <name>`：显示插件的组件清单及每个会话预估 Token 消耗。

5. **对话记录（Transcript）视图增强**
   - `?` 显示键盘快捷键
   - `{` / `}` 在用户提示之间跳转
   - `v` 切换快捷键面板

6. **Hook 机制重大改进**
   - 新增 `args: string[]` 执行形式（exec form），直接启动命令，无需 Shell，路径占位符不再需要引号。
   - `PostToolUse` Hook 新增 `continueOnBlock` 配置，可将拒绝原因反馈给 Claude 并继续执行。

7. **MCP 增强**
   - stdio MCP 服务现在会收到 `CLAUDE_PROJECT_DIR` 环境变量。
   - 插件配置中可使用 `${CLAUDE_PROJECT_DIR}` 占位符。
   - `/mcp` Reconnect 支持不重启即可加载 `.mcp.json` 修改，失败时显示 HTTP 状态和 URL。

### 二、改进与优化（Improvements）

- Compaction 提示词优化：要求模型更好地保留敏感用户指令。
- `/context all` 的 Token 估算现在使用实际模型分词器，显示四舍五入后的数值。
- `claude plugin install <name>@<marketplace>` 安装时会自动刷新市场并重试。
- `/plugin` 和 `/context` 显示更清晰（显示插件名称、Hook 事件名、MCP 服务名）。
- Remote MCP 服务器在瞬时失败时自动重试（已对所有用户启用）。
- Subagent 的 API 请求新增 `x-claude-code-agent-id` 等头部，OTEL 追踪包含 agent_id。
- 当设置 `ANTHROPIC_API_KEY` 等密钥时，自动禁用 Remote Control、/schedule、claude.ai MCP 等功能（更清晰的安全策略）。

### 三、Bug 修复（Bug Fixes）

本次版本修复了**大量**问题，共计 **30+** 项，主要集中在以下方面：

**核心稳定性与权限：**

- 修复凭证过期时导致 `claude auth` 命令死锁的问题。
- 修复 `autoAllowBashIfSandboxed` 不支持 `$VAR` 和 `$(cmd)` 扩展的问题。
- 修复 Hook 写入终端导致交互提示被破坏的问题。
- 修复 MCP 服务器流式非协议数据导致内存无限增长的问题（现限制 16MB）。
- 修复 `Skill(name *)` 通配符权限规则失效的问题。

**设置与插件系统：**

- 修复符号链接的 `settings.json` 热重载无法检测的问题。
- 修复插件详情在 marketplace key 与 manifest name 不一致时加载失败的问题。
- 修复 `claude plugin update` 不保留跨插件符号链接的问题。

**界面与交互：**

- 修复光标在 Tab 名、列表、对话框中闪烁的问题。
- 修复鼠标点击后快捷键失效的问题。
- 修复 Bash 模式向上键历史记录错误的问题。
- 修复粘贴/拖拽多张图片只插入最后一张的问题。
- 修复深色主题下超链接颜色不可读的问题。
- 修复模型选择器显示冗余行和别名解析错误的问题。

**其他重要修复：**

- 修复 Windows Terminal 和 VS Code 背景会话滚动问题。
- 修复鼠标滚轮在 Cursor 和 VS Code 中的滚动速度问题。
- 修复 Grep 结果路径、Diff 行数、Emoji 显示、模糊匹配等多个细节问题。
- 修复 MCP 资源残留、插件依赖计数、Insights 图表等边缘问题。

**VS Code 专属：**

- 新增 Cmd/Ctrl + Shift + T 快捷键重新打开最近关闭的会话标签（可配置）。

---

### **总结评价**

**2.1.139 是一个大型功能与稳定性更新版本**。

- **亮点**：引入了 **Agent 视图** 和 **/goal** 持久目标功能，大幅提升了 Claude Code 的自动化和多轮工作能力。
- **重点优化方向**：Hook/MCP 机制、插件系统、界面交互细节和跨平台稳定性。
- **用户影响**：重度用户（尤其是使用 Agent、插件、MCP、Remote Control 的用户）体验将显著提升，同时修复了大量可能导致崩溃、卡死或配置失效的顽固问题。

**推荐所有用户升级**，特别是正在使用 Agent 或复杂插件工作流的用户。

需要我帮您对比 **2.1.139** 与 **2.1.140** 的差异吗？
