## TypeScript 开发环境 + LazyVim 配合使用

LazyVim 本身已经把 TypeScript 支持做得非常好，通过 **Extras**（扩展）可以一键启用几乎所有需要的功能。

### 1. 先确保 LazyVim 已经安装（如果你还没装）

```bash
# 备份旧配置（重要！）
mv ~/.config/nvim ~/.config/nvim.bak

# 安装 LazyVim starter
git clone https://github.com/LazyVim/starter ~/.config/nvim

# 删除 .git 文件夹（方便你以后自己管理配置）
rm -rf ~/.config/nvim/.git
```

然后打开 Neovim，等待所有插件自动安装完成。

### 2. 启用 TypeScript 相关 Extras（最核心步骤）

LazyVim 使用 `:LazyExtras` 命令来启用官方扩展。

在 Neovim 中输入以下命令并启用（按空格确认）：

```vim
:LazyExtras
```

推荐至少启用以下几个（用空格选中后回车）：

- **lang.typescript** → 核心：提供 vtsls（推荐）或 tsgo LSP、智能补全、inlay hints、组织导入等
- **linting.eslint** → ESLint  linting 支持（自动修复）
- **formatting.prettier** → Prettier 格式化（保存时自动格式化）
- **lang.json** → package.json、tsconfig.json 等 JSON 文件支持
- **lang.tailwind** （如果你用 Tailwind CSS）→ Tailwind 类名补全、hover 提示

**推荐完整组合**（Web/TS 项目常用）：
- lang.typescript
- linting.eslint
- formatting.prettier
- lang.json
- lang.tailwind （可选）

启用后，重启 Neovim（`:qa` 退出再打开），LazyVim 会通过 **Mason** 自动安装：
- vtsls（默认 LSP，性能比旧 tsserver 更好）
- eslint / prettier 等工具

### 3. 常用配置调整（推荐放在这些文件中）

#### A. `lua/config/options.lua`（全局选项）
```lua
-- TypeScript LSP 选择（默认 vtsls，推荐；想用更快的新版可改 tsgo）
vim.g.lazyvim_ts_lsp = "vtsls"   -- 或 "tsgo"

-- Prettier 配置（如果项目没有 .prettierrc 也强制格式化）
vim.g.lazyvim_prettier_needs_config = false

-- ESLint 自动格式化（推荐开启）
vim.g.lazyvim_eslint_auto_format = true
```

#### B. 自定义 LSP 设置（如果需要微调）
新建文件 `lua/plugins/lsp.lua`（或 `typescript.lua`）：

```lua
return {
  -- 禁用 LSP 自带格式化，让 Prettier/ESLint 接管（避免冲突）
  {
    "neovim/nvim-lspconfig",
    opts = {
      servers = {
        vtsls = {
          settings = {
            typescript = {
              format = { enable = false },
            },
            javascript = {
              format = { enable = false },
            },
          },
        },
      },
      -- 全局 inlay hints（类型提示）开关
      inlay_hints = { enabled = true },
    },
  },

  -- 额外确保安装的工具
  {
    "williamboman/mason.nvim",
    opts = function(_, opts)
      vim.list_extend(opts.ensure_installed, {
        "vtsls",           -- 或 typescript-language-server
        "eslint-lsp",
        "prettier",
      })
    end,
  },
}
```

### 4. 常用快捷键（LazyVim 默认）

- **格式化**：`<leader>cf` （或保存时自动格式化）
- **代码操作**：`<leader>ca` （Code Action，例如 Organize Imports、Fix all）
- **跳转定义**：`gd`、`gD`
- **悬浮提示**：`K` 或 `<leader>ck`
- **重命名**：`<leader>cr`
- **诊断**：`<leader>cd`、`<leader>xl`
- **组织导入**：`<leader>co`（TypeScript 特有）

### 5. 项目级推荐配置

在你的 TS 项目根目录建议有以下文件：
- `tsconfig.json`（严格模式推荐）
- `.eslintrc.js` 或 `.eslintrc.json`
- `.prettierrc` 或 `prettier.config.js`
- `.editorconfig`

这样 ESLint + Prettier 才能正确读取项目配置。

### 6. 进阶建议（可选）

- 如果你觉得 vtsls 还不够强，可以尝试 **typescript-tools.nvim**（功能更丰富，但配置稍复杂）。
- 配合 **nvim-cmp**（LazyVim 已内置）补全非常丝滑。
- 大型 monorepo 项目：可能需要额外配置 `root_dir` 或 ESLint workingDirectories。

### 测试是否成功

1. 打开一个 `.ts` 或 `.tsx` 文件
2. 输入代码，看是否有智能补全、类型提示（inlay hints）
3. 保存文件，看是否自动用 Prettier 格式化 + ESLint 修复
4. 输入 `:Mason` 查看是否安装了 vtsls / prettier 等

大多数情况下，**只启用 lang.typescript + linting.eslint + formatting.prettier** 这三个 extras 就能得到一个非常好用的 TypeScript 开发环境。

---

**遇到问题请告诉我**：
- 你是用 React / Next.js / Vue / Node.js 项目？
- 具体卡在哪一步（LSP 不启动？格式化无效？补全慢？）
- 贴出错误信息或 `:LspInfo` 的输出，我可以帮你精准排查。

这样配置后，LazyVim + TypeScript 的体验通常比 VS Code 还流畅轻量很多。加油！
