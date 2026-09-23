---
name: 模块代码文档化（Codebase Doc）
description: 对指定目录/模块的 C/C++ 源码进行文档化梳理，输出带内联 SVG 流程图的中文 Markdown 分析文档，固定包含【目录与架构】【核心数据结构】【主干流程图】【关键函数解析】【可优化建议】。适用于本工程 ax615 的嵌入式模块。
---

# 模块代码文档化

把指定的目录/模块读透，产出一份结构固定、技术专业、带内联 SVG 流程图的 Markdown 文档。
本技能复现并固化了 `src/apps/p2p` 一次完整分析的工作流，可直接套用到本工程任意模块。

## 适用场景

- 用户要求「分析/梳理/文档化 `<目录或模块>` 代码」「输出带流程图的代码分析文档」。
- 新增或重构一个模块后，需要补齐设计文档与调用关系说明。
- 需要评估某模块的可优化点、并发风险、资源生命周期。

## 输入与输出

| 项 | 说明 |
| --- | --- |
| 输入 | 目标目录（如 `src/apps/rtsp`）或模块名；可选：输出文件路径 |
| 输出 | 单个 `.md` 文件；默认写到目标模块同级或仓库根，命名为 `<module>_analysis.md` |
| 约束 | 纯净 Markdown；SVG 必须内联（**不要**放进 ``` 代码块）；中文、去废话、结论可追溯 |

## 工作流

严格按以下步骤执行，不要跳步。

### 1. 确定范围与输出

- 确认目标目录、模块名、输出路径。若用户未指定输出路径，默认 `<repo-root>/<module>_analysis.md`。
- 先读仓库根 `README.md` 与目标模块的 `CMakeLists.txt` / `*.cmake`，确认编译归属与外部依赖。

### 2. 目录扫描（结构 + 规模）

```bash
# 目录树与文件规模
find <target-dir> -type f | sort
wc -l <target-dir>/**/*.c <target-dir>/**/*.h
# 编译单元 / 依赖
grep -rn "<target-dir-name>" --include='CMakeLists.txt' --include='*.cmake' .
```

记录：分层目录、每个文件的职责（读文件头注释与主要导出符号）。

### 3. 定位挂载点与外部契约（关键）

一个模块的价值在它与外部的接口。必须找到：

```bash
# 谁调用本模块的 init/deinit/主入口（排除自身）
grep -rn "<入口符号>" --include='*.c' --include='*.h' --include='*.cpp' src/ | grep -v "<target-dir>/"
# 确认外部依赖的真实定义（不要臆测结构体字段）
grep -rn "typedef struct\|typedef enum\|} <type>;" --include='*.h' <依赖目录>
```

要弄清楚：
- **生命周期挂载点**：谁、在哪个循环/回调里、按什么条件调用 `init`/`deinit`。
- **触发来源**：主线程轮询？SDK/驱动回调线程？信号？定时器？
- **外部契约**：SDK/框架的结构体、枚举、回调签名、错误码。
- **编译产物**：进程名、链接库、条件编译宏。

### 4. 精读全部源码

对每个源文件通读，提取：

- **核心数据结构**：全局单例、会话/上下文结构、句柄、状态枚举、缓冲。
- **初始化/去初始化链路**：调用顺序、失败回滚、幂等保护。
- **主干调用链**：从外部触发到最终落点（硬件/SDK/网络/共享内存）。
- **线程模型**：`pthread_create/detach/join`、锁、条件变量、`_Atomic`、跨线程共享变量。
- **进程间通信**：`GSF_MSG_SENDTO`、`cfifo_shmat`、共享内存、`extern` 全局、文件/Socket。
- **资源生命周期**：`malloc/free`、`create/destroy`、`open/close`、引用计数。
- **状态机与并发**：状态字段读写是否加锁/原子、是否存在死代码、错误是否向上反馈。

> 结论必须能落到「文件:行号」或「函数名/符号名」，不写空泛套话。

### 5. 绘图

阅读**项目根目录的 `svg-style.md`**（权威规范），按其生成内联 SVG；本技能 `references/svg-style.md` 是精简自检版。
选择的图型（至少 3 张，其中 1 张为主干流程图）：

1. **架构/数据流图**：分层分组框 + 层内等宽节点 + 汇聚箭头。
2. **主干逻辑流程图**：中轴竖排 + 琥珀判断 + 左右分支 + 下合流（必选）。
3. **数据面/时序图**：泳道 + 循环与回环箭头。
4. 可选：状态机、共享内存字节布局、线程模型。

### 6. 按模板产出文档

章节固定为 `references/output-template.md` 的顺序：标题元信息 →【目录与架构说明】→【核心数据结构】→【主干逻辑流程图】→【关键函数解析】→【可优化建议】→ 附录调用关系速查。

优化建议按 **P0（正确性/并发安全）→ P1（资源/架构）→ P2（质量/清理）** 分级；每条给出「问题 + 位置 + 建议动作」。

### 7. 自检（必须执行）

```bash
python3 .opencode/skills/codebase-doc/scripts/validate_svgs.py <输出.md>
```

逐项确认：

- [ ] 目录树为 tree 风格，每项带功能简述。
- [ ] 结论均有文件/符号支撑。
- [ ] SVG 内联、XML 合法、`marker` id 唯一且带图前缀（`f1ar`、`f2red`…）。
- [ ] 无文字溢出 `viewBox`；同页无重复 id。
- [ ] 优化建议可执行且已分级。
- [ ] 全文为纯净 Markdown，无半成品/TODO。

## 分析要点备忘（本工程常见）

- 依赖头：`inc/gsf.h`、`inc/frm.h`、`src/apps/cfg.h`、`src/apps/protol_api.h`、`src/util_fw/inc/fw/cfifo/cfifo.h`、`src/mpp/inc/mpp/codec.h`、`src/apps/tencent_rtc_sdk/include/*`。
- 共享内存环形队列：`cfifo_*`（`cfifo_shmat`/`cfifo_ep_wait`/`cfifo_get`），帧头 `gsf_frm_t`。
- 进程间消息：`GSF_MSG_SENDTO(...)` + `GSF_IPC_*`；编码流 `gsf_stream_shmid_t`。
- 全局配置：`g_apps_parm`（`gsf_apps_t`，宏生成于 `src/apps/inc/apps/*.ih`）、`g_apps_info`（`gsf_apps_info_t`）。
- 常见并发缺陷模式：普通 `int` 状态跨线程、大锁内调用 SDK、`pthread_join` 与状态更新非原子、回调未注册、调试 `printf` 残留、不可达死代码。

## 参考

- 权威绘图规范：项目根 `svg-style.md`
- 输出模板：`references/output-template.md`
- SVG 自检脚本：`scripts/validate_svgs.py`
- 完整范例（本技能来源）：`p2p_analysis.md`
