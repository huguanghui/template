# 开发环境搭建

> 这份文档旨在为你构建一套**全平台一致、CLI 优先、高效且现代化**的开发环境。

---

## 一、 Windows 开发环境搭建 (Local)

Windows 端定位为：**交互入口 + 串口调试 + 高级排版 + AI 辅助**。

#### 1. 基础包管理

- **Winget**: 系统自带，用于安装大型软件。

  ```powershell
  winget install wezterm winmerge espanso.espanso
  ```

- **Scoop (推荐补充)**: 相比 winget，更适合管理开发工具（不污染环境变量）。

  ```powershell
  # 安装 scoop
  Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
  Invoke-RestMethod -Uri https://get.scoop.sh | Microsoft.PowerShell.Commands.InvokeExpression
  # 安装开发工具
  scoop install pwsh neovim lazygit ripgrep yazi fzf zoxide miniconda claudecode
  ```

#### 2. 终端与 Shell (WezTerm + Pwsh)

- **WezTerm**: 配置文件使用 Lua（与 Neovim 一致），支持内置 Multiplexer。
- **Oh My Posh**:

  ```powershell
  oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\jandedobbeleer.omp.json" | Invoke-Expression
  ```

- **字体**: 必须安装 **Nerd Fonts** (如 `JetBrainsMono NF`)，否则 Yazi 和 OhMyPosh 会乱码。

#### 3. 核心工具配置

- **Espanso**: 文本替换（如输入 `:date` 自动补全日期），适合快速输入常用代码片段。
- **SecureCRT**: 保持用于稳定串口通信。
- **WinMerge**: 处理复杂的二进制或目录差异对比。

---

## 二、 Linux 服务器环境搭建 (Remote)

Linux 端定位为：**高性能编译 + 会话持久化 + 自动化部署**。

#### 1. 基础环境

- **包管理**: 使用 `apt/dnf` 配合 `nvm` 和 `miniconda`。
- **交叉编译**: 安装 `build-essential`, `gcc-arm-linux-gnueabihf` (根据芯片型号)。

#### 2. Shell 与会话 (Zsh + Tmux)

- **Zsh**: 配合插件 `zsh-autosuggestions`, `zsh-syntax-highlighting`。
- **Tmux**: 核心工具，建议使用 `Oh My Tmux!` 配置。
- **Zoxide & Atuin**:
  - `z`: 极速路径跳转（zoxide）。
  - `atuin`: 带数据库的命令历史搜索。

#### 3. 开发工具链

- **Neovim + LazyVim**: 远程 SSH 连上去直接 `nvim .`。
- **Yazi**: 代替 Ranger（Yazi 是 Rust 写的，预览大文件和图片更快）。
- **NCDU**: 磁盘清理利器。

---

## 三、 统一的 Neovim & AI 工作流

无论在 Windows 还是 Linux，保持 `~/.config/nvim` 同步（建议使用 Git 管理）。

- **LazyVim**: 开启 `lang.python`, `lang.rust`, `lang.cmake`, `lang.typescript` 插件。
- **ClaudeCode**: 作为独立 CLI 工具，在终端内执行 `claude` 进行代码审计和自动重构。
- **Lazygit**: 在 Neovim 内通过快捷键（通常是 `<leader>gg`）唤起。

---

## 四、 优化建议与更实用的工具推荐

基于你现有的工具链，我推荐以下几个能显著提升“丝滑感”的优化点：

#### 1. 跨平台增强 (推荐)

- **fzf (Fuzzy Finder)**: **必装**。它是 `rg`, `fd`, `zoxide` 的粘合剂。配合 `CTRL-R` 搜历史，`CTRL-T` 搜文件。
- **bat**: 替代 `cat`。带语法高亮和 Git 状态显示。
- **eza**: 替代 `ls`。它是 `ls` 的现代化版，支持图标和 Git 状态展示。
- **delta**: **强烈推荐**。用于 `git diff` 的分页器，让终端里的代码对比比 WinMerge 还直观。

##### delta 安装和配置

```bash
# windows
scoop install git-delta
# linux
cargo install git-delta
```

- gitconfig配置

> 编辑你的 ~/.gitconfig (Linux) 或 C:\Users\用户名\.gitconfig (Win

```
[core]
    pager = delta

[interactive]
    diffFilter = delta --color-only

[delta]
    side-by-side = true    # 开启侧边对比 (如果你屏幕够宽)
    line-numbers = true    # 显示行号
    navigate = true        # 开启 n/N 跳转
    syntax-theme = Monokai Extended # 高亮主题

[merge]
    conflictstyle = zdiff3 # 增强冲突显示
```

#### 2. Windows 特有优化

- **Gsudo**: Windows 端的 `sudo`。不用切换管理员窗口，直接 `gsudo nvim`。
- **Keypirinha / PowerToys Run**: 快速启动器，比系统自带搜索快得多。

#### 3. 工具替换与精简

- **Yazi vs Ranger**: 既然你两个都列了，**建议统一使用 Yazi**。Yazi 是基于异步事件的（Rust），在预览大文件夹时不会像 Ranger 那样卡顿。
- **fd vs ag**: `fd` (Rust) 通常比 `ag` 快且语法更人性化。建议 Linux 端也统一使用 `fd` + `rg`。
- **SSH 增强**: 推荐使用 **`ssh-config`** 管理服务器别名，并配合 **`Tailscale`** 或 **`ZeroTier`** 组网，省去记 IP 的麻烦。

#### 4. 配置同步方案

- **Chezmoi**: 专门管理 Dotfiles 的工具。可以一键将你的 `nvim`, `tmux`, `wezterm`, `zsh` 配置同步到新服务器。

---

## 总结：你的终极工具栈清单

| 分类           | 推荐工具                                              |
| :------------- | :---------------------------------------------------- |
| **Shell/终端** | WezTerm + Pwsh(Win) / Zsh(Lin) + **zoxide** + **fzf** |
| **编辑器**     | Neovim (LazyVim) + **ClaudeCode**                     |
| **文件管理**   | **Yazi** (统一取代 Ranger)                            |
| **Git 增强**   | Lazygit + **delta**                                   |
| **搜索/查看**  | **rg** + **fd** + **bat**                             |
| **包管理**     | **Scoop**(Win) + **Mamba**(替代 Conda，更快)          |
| **系统监控**   | **btop** (比 htop 更强更帅)                           |

**建议操作步骤：**

1. 在 Windows 安装 **Scoop**。
2. 配置 **WezTerm**，使用 Lua 统一管理。
3. 学习 **fzf** 的基本快捷键（这是效率质变的关键）。
4. 将所有配置文件（Dotfiles）放入 Git 仓库，实现两端同步。
