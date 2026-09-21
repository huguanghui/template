# tmux 源码编译完整流程（Ubuntu 24.04）

## 一、安装依赖

### 必需依赖

```bash
sudo apt update
sudo apt install -y build-essential pkg-config \
    libevent-dev libncurses-dev
```

### 可选依赖（按需选择）

```bash
# jemalloc：高性能内存分配器，长时间运行更稳定
sudo apt install -y libjemalloc-dev

# utf8proc：更准确的 Unicode 字符宽度计算，改善 emoji/CJK 显示
sudo apt install -y libutf8proc-dev

# libsixel：终端内直接显示图片
sudo apt install -y libsixel-dev

# systemd 集成（个人使用一般不需要）
sudo apt install -y libsystemd-dev
```

## 二、获取源码

### 方式 A：从 Git 仓库克隆（最新开发版）

```bash
git clone https://github.com/tmux/tmux.git
cd tmux
```

### 方式 B：下载 release 压缩包（稳定版，推荐）

```bash
# 到 https://github.com/tmux/tmux/releases 查看最新版本号
wget https://github.com/tmux/tmux/releases/download/3.5a/tmux-3.5a.tar.gz
tar -zxvf tmux-3.5a.tar.gz
cd tmux-3.5a
```

> **说明**：Git 仓库克隆的源码默认 `debug: on`，release 包默认 `debug: off`。

## 三、配置

```bash
./configure \
    --enable-sixel \
    --enable-jemalloc \
    --enable-utf8proc \
    --disable-debug
```

### 参数说明

| 参数                | 作用                                                          |
| :------------------ | :------------------------------------------------------------ |
| `--enable-sixel`    | 启用 SIXEL 图像协议支持（注意不是 `--enable-sixel-graphics`） |
| `--enable-jemalloc` | 使用 jemalloc 内存分配器                                      |
| `--enable-utf8proc` | 使用 utf8proc 处理 Unicode 宽度                               |
| `--disable-debug`   | 关闭调试模式，提升性能                                        |
| `--enable-systemd`  | 启用 systemd 集成（个人使用无需）                             |
| `--enable-utempter` | 记录登录会话到 utmp（按需）                                   |

### 验证配置结果

配置成功后应看到类似输出：

```
configure: SIXEL: on
configure: debug: off
configure: jemalloc: 5.3.0_0
configure: libevent: 2.1.12-stable
configure: ncurses: 6.4.20240113
configure: utf8proc: 3.0.0
```

如果某项显示 `off`，检查对应依赖是否安装，以及参数名是否正确。

## 四、编译与安装

```bash
# 编译（-j 后接 CPU 核心数，加速编译）
make -j$(nproc)

# 安装到 /usr/local/bin
sudo make install
```

## 五、验证安装

```bash
# 检查版本
tmux -V

# 确认路径（应为 /usr/local/bin/tmux）
which tmux
```

如果 `which tmux` 指向 `/usr/bin/tmux`，说明系统自带的旧版优先被找到。解决方法：

```bash
# 方案一：卸载系统自带版本
sudo apt remove tmux

# 方案二：调整 PATH，确保 /usr/local/bin 在前
export PATH=/usr/local/bin:$PATH
```

## 六、安装后配置

### 1. 启用 SIXEL（如果编译时开启了）

在 `~/.tmux.conf` 中加入：

```tmux
set -g terminal-features "xterm*:sixel"
```

### 2. 验证 SIXEL 是否生效

```bash
tmux display -p '#{sixel_support}'
# 返回 1 表示编译层面已启用
```

### 3. 确认终端模拟器支持 SIXEL

tmux 编译支持只是前提，终端本身也需要支持：

- ✅ **支持**：WezTerm、foot、contour、mlterm、kitty（需配置）
- ❌ **不支持**：GNOME Terminal、Konsole、Alacritty、xterm（默认）

## 七、常见问题

| 问题                 | 原因                 | 解决                                               |
| :------------------- | :------------------- | :------------------------------------------------- |
| `curses not found`   | 缺少 ncurses 开发库  | `sudo apt install libncurses-dev`                  |
| SIXEL 始终 off       | 参数名写错           | 用 `--enable-sixel` 而非 `--enable-sixel-graphics` |
| SIXEL 仍 off         | libsixel-dev 未装    | `sudo apt install libsixel-dev`                    |
| `libevent not found` | 缺少 libevent 开发库 | `sudo apt install libevent-dev`                    |
| 编译后仍是旧版       | 路径优先问题         | 卸载系统 tmux 或调整 PATH                          |
| 重新配置有残留       | 缓存干扰             | 先 `make distclean` 再重新 `./configure`           |

## 八、完整命令速查

```bash
# 1. 依赖
sudo apt install -y build-essential pkg-config libevent-dev libncurses-dev \
    libjemalloc-dev libutf8proc-dev libsixel-dev

# 2. 源码
git clone https://github.com/tmux/tmux.git && cd tmux

# 3. 配置
./configure --enable-sixel --enable-jemalloc --enable-utf8proc --disable-debug

# 4. 编译安装
make -j$(nproc) && sudo make install

# 5. 验证
tmux -V && which tmux
```
