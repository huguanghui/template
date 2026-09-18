# markserv 安装与使用

markserv 是一个基于 Node.js 的轻量 Markdown HTTP 服务器。它把 `.md` 文件实时渲染成 GitHub 风格的 HTML，在浏览器中查看；文件保存后页面会自动刷新，适合替代编辑器内置预览，尤其适合在远程服务器上通过 SSH 端口转发预览模型生成的 Markdown。

- 项目地址：https://github.com/markserv/markserv
- 依赖：Node.js 和浏览器
- 推荐场景：远程开发时在 tmux 中常驻运行，本地浏览器通过 SSH 转发查看

## 安装

### 全局安装

```bash
npm install -g markserv
```

### 免安装使用

不想全局安装时，可以用 `npx` 直接运行：

```bash
npx markserv --help
```

### 验证安装

```bash
markserv --help
```

如果输出版本和参数说明，说明安装成功。

## 基本使用

### 预览单个文件

```bash
markserv README.md
```

命令输出会显示服务地址，默认通常是：

```text
http://localhost:8642/README.md
```

### 预览整个目录

```bash
markserv /path/to/markdown
```

浏览器访问目录地址后，markserv 会提供目录索引；点击其中的 `.md` 文件即可预览。

### 常用参数

```bash
# 指定端口
markserv -p 8642

# 只监听本机回环地址
markserv -a 127.0.0.1

# 使用浅色主题
markserv --light

# 指定主题，可选 dark / light / synthwave / solarized
markserv --theme solarized

# 查看帮助
markserv --help
```

## 在 tmux 中常驻运行

推荐把 markserv 放到一个独立的 tmux window 中，避免它占用当前工作窗口：

```bash
tmux new-window -n preview 'markserv -p 8642 -a 127.0.0.1 /path/to/output'
```

如果服务已经在 tmux 里运行，需要重新加载文件或重启服务时：

```bash
tmux send-keys -t preview C-c
tmux send-keys -t preview 'markserv -p 8642 -a 127.0.0.1 /path/to/output' Enter
```

也可以直接查看运行日志：

```bash
tmux select-window -t preview
```

## 配合远程 SSH 使用

假设 markserv 运行在远程服务器的 `127.0.0.1:8642`。

### 临时端口转发

在 Windows 本地 pwsh 中连接远程主机：

```powershell
ssh -L 8642:127.0.0.1:8642 user@remote
```

连接成功后，Windows 浏览器打开：

```text
http://localhost:8642/your-file.md
```

### 永久写入 SSH 配置

编辑本地的 `~/.ssh/config`，例如 Windows 下通常是：

```text
C:\Users\<你的用户名>\.ssh\config
```

添加：

```sshconfig
Host remote
  HostName remote.example.com
  User your-user
  LocalForward 8642 127.0.0.1:8642
```

之后只需正常执行：

```bash
ssh remote
```

端口转发会自动建立。

## 工作流示例

以 `windows → pwsh → ssh → tmux → claude/opencode/lazyvim` 的开发方式为例：

1. 远程项目目录中启动 markserv：

   ```bash
   tmux new-window -n preview 'markserv -p 8642 -a 127.0.0.1 ~/work/output'
   ```

2. Windows 本地 SSH 连接时转发端口：

   ```powershell
   ssh -L 8642:127.0.0.1:8642 user@remote
   ```

3. 浏览器打开：

   ```text
   http://localhost:8642/summary.md
   ```

4. claude/opencode 生成或更新 Markdown 后，浏览器页面自动刷新。

## 渲染 SVG

markserv 会把 Markdown 中的原始 HTML 块按 HTML 输出，因此内嵌 `<svg>` 块通常可以直接渲染。

如果使用的 markserv 版本对 HTML 有过滤，导致内嵌 SVG 不显示，可以让模型把 SVG 保存为独立文件，然后在 Markdown 中引用：

```markdown
![](diagram.svg)
```

浏览器会按普通 SVG 图片渲染该文件。

## 常见问题

### 端口被占用

换个端口启动：

```bash
markserv -p 8643
```

同时把 SSH 转发命令中的端口也改成相同值。

### 浏览器无法访问

检查三处配置是否一致：

1. markserv 是否绑定在 `127.0.0.1`；
2. markserv 实际监听端口是否是 `8642`；
3. SSH `LocalForward` 的远端地址和端口是否正确。

如果远程服务必须监听 `0.0.0.0`，请确保服务器防火墙和云安全组没有把该端口暴露到公网；更推荐继续使用 `127.0.0.1` 加 SSH 隧道。

### 页面没有自动刷新

确认：

- 保存的是 markserv 正在预览的 `.md` 文件；
- 页面没有禁用 JavaScript；
- tmux 中 markserv 进程没有退出。

必要时重新启动 markserv。

### Node.js 版本过旧

markserv 依赖较新的 Node.js 运行时。如果 `npm install` 或运行时报语法错误，先升级 Node.js，例如使用 `nvm`：

```bash
nvm install --lts
nvm use --lts
npm install -g markserv
```
