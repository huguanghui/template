在 LazyVim 中搭建 Golang 环境非常简单，因为 LazyVim 官方已经提供了高度集成的 **Extra** 模块。

以下是完整步骤，分为 **基础开启**、**工具安装**、**进阶配置** 三部分。

---

### 第一步：开启 LazyVim 的 Go 模块

LazyVim 内置了 Go 语言支持，你只需要在配置文件中启用它。

1. 打开 Neovim。
2. 输入 `:LazyExtras` 并回车。
3. 找到 **`lang.go`** 选项，按 `x` 键选中（它会自动修改你的配置文件）。
    - _(可选)_ 建议同时开启 **`dap.core`** (调试) 和 **`test.core`** (测试)。
4. 重启 Neovim。

或者，你也可以手动修改 `~/.config/nvim/lua/config/lazy.lua`，在 `spec` 部分添加：

```lua
{ import = "lazyvim.plugins.extras.lang.go" },
```

---

### 第二步：安装必要二进制工具

LazyVim 会通过 **Mason** 自动提示安装工具，但为了确保稳定，建议手动运行 Mason 安装以下核心包：

1. 在 Neovim 中输入 `:Mason`。
2. 手动查找并按 `i` 安装：
    - **`gopls`**: 官方语言服务器 (LSP)。
    - **`goimports`** 或 **`goimports-reviser`**: 自动整理 import。
    - **`golangci-lint`**: 代码静态检查（Linter）。
    - **`delve`**: 调试器 (DAP)。
    - **`gotests`**: 自动生成测试用例。
    - **`golines`**: 自动拆分长行（如果你有行宽限制需求）。

---

### 第三步：进阶配置 (LSP 与 格式化)

为了让环境更好用，我们通常会微调 `gopls` 的设置（例如开启代码镜头、语义高亮等）。

创建或编辑 `~/.config/nvim/lua/plugins/go.lua`:

```lua
return {
  -- 1. 配置 LSP (gopls)
  {
    "neovim/nvim-lspconfig",
    opts = {
      servers = {
        gopls = {
          settings = {
            gopls = {
              gofumpt = true, -- 使用更严格的格式化
              codelenses = {
                gc_details = false,
                generate = true,
                regenerate_cgo = true,
                run_govulncheck = true,
                test = true,
                tidy = true,
                upgrade_dependency = true,
                vendor = true,
              },
              hints = {
                assignVariableTypes = true,
                compositeLiteralFields = true,
                compositeLiteralTypes = true,
                constantValues = true,
                functionTypeParameters = true,
                parameterNames = true,
                rangeVariableTypes = true,
              },
              analyses = {
                unusedparams = true,
              },
              staticcheck = true,
              directoryFilters = { "-.git", "-.vscode", "-.idea", "-.vscode-test", "-vendor" },
            },
          },
        },
      },
      setup = {
        -- 绑定快捷键用于显示代码高度 (Code Lens)
        gopls = function(_, opts)
          require("lazyvim.util").lsp.on_attach(function(client, bufnr)
            if client.name == "gopls" then
              vim.api.nvim_create_autocmd({ "BufEnter", "CursorHold", "InsertLeave" }, {
                buffer = bufnr,
                callback = vim.lsp.codelens.refresh,
              })
            end
          end)
        end,
      },
    },
  },

  -- 2. 配置格式化 (集成 golines)
  {
    "stevearc/conform.nvim",
    opts = {
      formatters_by_ft = {
        go = { "golines", "goimports-reviser", "gofumpt" },
      },
      formatters = {
        golines = {
          args = { "--max-len=100", "--base-formatter=gofumpt" },
        },
      },
    },
  },
}
```

---

### 第四步：常用快捷键 (Workflow)

开启了 `lang.go` 模块后，你可以使用以下快捷键（默认为 LazyVim 风格）：

- **LSP 相关**:
  - `gd`: 跳转到定义。
  - `gr`: 查看引用。
  - `K`: 查看文档/悬浮提示。
  - `<leader>cr`: 变量重命名 (Rename)。
  - `<leader>ca`: 代码操作 (Code Action，如快速修复、填充 struct 字段)。

- **测试相关**:
  - `<leader>tt`: 运行当前测试。
  - `<leader>tT`: 运行整个文件的测试。
  - `<leader>ts`: 查看测试输出。

- **调试相关 (`nvim-dap-go`)**:
  - `<leader>db`: 打断点。
  - `<leader>dt`: 调试当前测试用例。
  - `<leader>dc`: 继续运行 (Continue)。

- **工具辅助**:
  - `<leader>cy`: 运行 `go mod tidy`。
  - `<leader>cg`: 生成测试用例。

---

### 第五步：验证环境

1. 新建一个 `main.go`。
2. 输入代码，观察 **Inlay Hints**（行内提示变量类型）是否出现。
3. 故意写一个未使用的变量，看 `golangci-lint` 是否报错。
4. 输入一个长行，保存文件，看 `golines` 是否自动换行。
5. 按 `<leader>dt` 启动调试，确认 `dlv` (Delve) 正常工作。

这样你就拥有了一个不输于 GoLand 的轻量化开发环境！
