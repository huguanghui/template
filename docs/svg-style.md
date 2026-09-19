# svg-style.md — 内联 SVG 技术图风格规范

> 可直接粘贴给任意 AI 工具/对话框的紧凑提示词。两档：一段话版（最精简）、紧凑清单版（带配色表与图型速查）。

---

## 一、一段话版（最精简，适合随手贴）

```text
画技术图时，请在 Markdown 里直接内联 <svg>（不要包在 ``` 代码块里，否则不渲染）。根标签：<svg viewBox="0 0 W H" xmlns="http://www.w3.org/2000/svg" font-family="system-ui,'Noto Sans SC',sans-serif" font-size="15">，W 取 1000~1200、H 给足且无文字溢出。字号拉开层级：分组标题 17-18/700，节点标题 15-16/600，正文 14-15，次级 13，注释 12-13 灰 #6b7280。配色按语义、填充/描边/文字三件套：蓝 #dbeafe/#2563eb/#1e3a8a=进程数据，绿 #dcfce7/#16a34a/#14532d=开始成功，琥珀 #fef3c7/#d97706/#78350f=判断分支，红 #fee2e2/#dc2626/#7f1d1d=错误关键，紫 #ede9fe/#7c3aed/#4c1d95=存储索引，青 #ccfbf1/#0d9488/#115e59=缓冲，灰 #f3f4f6/#4b5563/#1f2937=中性；分组大框底色 #eff6ff/#f0fdfa/#fff7ed、rx=12、stroke-width=2。节点 rx=8、描边 1.5-2；箭头 #374151 宽 2 配 <defs> 里的 marker（同页多图 marker id 加前缀如 s1ar），弱关系用 #9ca3af + stroke-dasharray="6 4"。中文用无衬线字体栈、标签尽量短、长标签拆成多个 <text>；符号直接用 → ≥ ≤ · × ①②③，& 写成 &amp;。按层级分区、等宽对齐、留足间距。输出前自检 XML 合法、无文字溢出、无 id 重复。只输出 SVG，不要解释。
```

---

## 二、紧凑清单版（带配色表与图型速查）

```text
请用内联 SVG 在 Markdown 中绘制技术图（直接输出 <svg>，不要包代码块）。

【根标签】<svg viewBox="0 0 W H" xmlns="http://www.w3.org/2000/svg" font-family="system-ui,'Noto Sans SC',sans-serif" font-size="15">
W=1000~1200，H 给足，禁止文字/元素越界。
【字号】分组标题 17-18/700；节点标题 15-16/600；正文 14-15；次级 13；注释 12-13（#6b7280）。居中用 text-anchor="middle"，基线 y≈框中心+5。
【配色·填充/描边/主文字】蓝 #dbeafe/#2563eb/#1e3a8a=进程数据；绿 #dcfce7/#16a34a/#14532d=开始成功；琥珀 #fef3c7/#d97706/#78350f=判断分支；红 #fee2e2/#dc2626/#7f1d1d=错误关键；紫 #ede9fe/#7c3aed/#4c1d95=存储索引；青 #ccfbf1/#0d9488/#115e59=缓冲；灰 #f3f4f6/#4b5563/#1f2937=中性。分组大框底色 #eff6ff/#f0fdfa/#fff7ed，rx=12，stroke-width=2。
【形状】节点 rx=8、描边 1.5-2；嵌套 rx=6 + 更浅底；起止可用胶囊（rx=高/2）。
【箭头】主流程 #374151 宽 2 + <marker>（markerWidth/Height=11，refX=8）；异步/回环 #9ca3af 宽 1.8-2 + stroke-dasharray="6 4"；分支标注「是/否」13/600。同页多图 marker id 必须前缀唯一（s1ar、s2a…）。
【文本】中文用无衬线字体栈；标签简短，长标签拆多行 <text>；用 → ≥ ≤ · × ①②③；& 写 &amp;，不出现裸 < >。
【布局】按层级/泳道用 rx=12 分组框分区，层内节点等宽、中心对齐，留足间距；宁可加高 H 不挤压。
【图型套路】架构/数据流=分层大框+等宽节点+汇聚箭头；流程图=中轴竖排+琥珀判断+左右分支+下合流；字节布局=横排等宽区段+大字段名+小偏移注+…；树形=父上子下+缩进浅底；管道回环=横排节点+底部虚线回环+条件标注。
【自检】XML 合法、标签闭合、文字不溢出、无 id 重复。只输出 SVG。
```

---

## 三、配色表

| 语义 | 填充 | 描边 | 主文字 | 次文字 |
| --- | --- | --- | --- | --- |
| 蓝 · 进程/数据/处理 | `#dbeafe` | `#2563eb` | `#1e3a8a` | `#1e40af` |
| 绿 · 开始/成功/输入 | `#dcfce7` | `#16a34a` | `#14532d` | `#166534` |
| 琥珀 · 判断/分支 | `#fef3c7` | `#d97706` | `#78350f` | `#92400e` |
| 红 · 错误/终止/关键数据 | `#fee2e2` | `#dc2626` | `#7f1d1d` | `#991b1b` |
| 紫 · 存储/索引 | `#ede9fe` | `#7c3aed` | `#4c1d95` | `#5b21b6` |
| 青 · 缓冲/共享内存 | `#ccfbf1` | `#0d9488` | `#115e59` | `#0f766e` |
| 灰 · 中性/注释/外部 | `#f3f4f6` | `#4b5563` | `#1f2937` | `#374151` |
| 分组框（蓝底） | `#eff6ff` | `#2563eb` | — | — |
| 分组框（青底） | `#f0fdfa` | `#0d9488` | — | — |
| 分组框（橙底） | `#fff7ed` | `#ea580c` | `#9a3412` | — |

---

## 四、图型速查

| 图型 | 关键手法 |
| --- | --- |
| 整体架构 / 数据流 | 分层分组框 + 层内等宽节点 + 汇聚箭头 |
| 业务流程 / 流程图 | 中轴竖排 + 琥珀判断 + 左右分支 + 下合流 |
| 文件 / 内存字节布局 | 横排等宽区段框 + 大字段名 + 小偏移注 + `…` |
| Box / 目录 / 调用树 | 父上子下 + 缩进浅底框 + 左对齐 |
| 结构体 / 索引表 | 头部框 + 记录框分块 + 右侧要点列表 |
| 管道 + 回环 | 横排节点 + 底部虚线回环 + 条件标注 |

---

## 五、最小骨架

```html
<svg viewBox="0 0 1000 260" xmlns="http://www.w3.org/2000/svg"
     font-family="system-ui, 'Noto Sans SC', sans-serif" font-size="15">
  <defs>
    <marker id="s0ar" markerWidth="11" markerHeight="11" refX="8" refY="3.5" orient="auto">
      <path d="M0,0 L8,3.5 L0,7 Z" fill="#374151"/>
    </marker>
  </defs>

  <rect x="30" y="40" width="940" height="90" rx="12" fill="#eff6ff" stroke="#2563eb" stroke-width="2"/>
  <text x="55" y="72" font-size="18" font-weight="700" fill="#1e3a8a">分组标题</text>

  <rect x="60" y="88" width="260" height="60" rx="8" fill="#dbeafe" stroke="#2563eb" stroke-width="1.6"/>
  <text x="190" y="124" text-anchor="middle" font-size="16" font-weight="600" fill="#1e3a8a">节点 A</text>

  <line x1="320" y1="118" x2="396" y2="118" stroke="#374151" stroke-width="2" marker-end="url(#s0ar)"/>

  <rect x="400" y="88" width="260" height="60" rx="8" fill="#fef3c7" stroke="#d97706" stroke-width="1.6"/>
  <text x="530" y="124" text-anchor="middle" font-size="16" font-weight="600" fill="#78350f">判断节点</text>
</svg>
```

---

## 六、校验

```bash
python3 - <<'EOF'
import re, xml.etree.ElementTree as ET
s = open("doc.md", encoding="utf-8").read()
for i, sv in enumerate(re.findall(r'<svg\b.*?</svg>', s, re.S)):
    ET.fromstring(sv)   # 不抛异常即合法
    print(i, "OK")
EOF
```

---

## 七、注意事项

- SVG 不要包进代码块，否则页面只显示源码。
- 不要用 <12px 或未加粗的浅色文字，缩放后会糊。
- 同页多图必须规避 marker / id 冲突（id 加前缀）。
- 有中文时优先无衬线字体栈，避免 monospace 造成中文发虚。
- 颜色只承载语义，不堆砌；一张图建议 ≤5 种色系。
