**2.1.140 版本更新记录（简体中文整理与分析）**

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

**2.1.139 版本更新记录（简体中文整理与分析）**

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
