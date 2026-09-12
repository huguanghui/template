# tio

> https://github.com/tio/tio

## 安装

```bash
sudo apt-get install tio -y
```

## 使用技巧

tio 的实用技巧可以围绕它的核心优势展开：**自动重连、日志管理和配置复用**。以下是整理后的使用要点。

### 🔌 连接与自动重连（核心卖点）

tio 默认会自动连接设备，并且**设备断开后会等待其重新出现并自动恢复连接**。这对于调试过程中设备意外掉线的情况非常省心。

**关键技巧：用设备 ID 代替设备名**
不要用 `/dev/ttyUSB0` 这种会变的路径，而是用 `/dev/serial/by-id/...`。这样即使 USB 重新枚举导致设备号变化，tio 也能自动重连到**正确的设备**。

```bash
tio /dev/serial/by-id/usb-FTDI_TTL232R-3V3_XXXX-if00-port0
```

如果你**不希望**自动重连（比如只想临时看一眼，断开就退出），加上 `-n` 或 `--no-autoconnect` 即可。

### 📝 日志记录

tio 的日志功能比较顺手，支持自动生成文件名。

**自动命名**（格式通常为 `tio_设备名_时间戳.log`）：

```bash
tio --log /dev/ttyUSB0
```

**指定文件名**：

```bash
tio --log --log-file my-log.txt /dev/ttyUSB0
```

**带时间戳**（每行前加时间）：

```bash
tio --timestamp --log /dev/ttyUSB0
```

**日志过滤控制字符**（让日志更干净，去掉转义序列）：

```bash
tio --log --log-strip /dev/ttyUSB0
```

连接后也可以用快捷键 `Ctrl+t f` 临时开关日志记录。

### ⌨️ 常用快捷键（前缀 `Ctrl+t`）

连接后按 `Ctrl+t ?` 可查看完整列表，常用的有：

- `Ctrl+t t`：发送 `Ctrl+t` 字符本身
- `Ctrl+t f`：切换日志记录开关
- `Ctrl+t c`：查看当前配置（波特率、数据位等）
- `Ctrl+t h`：切换十六进制显示模式
- `Ctrl+t e`：切换本地回显
- `Ctrl+t s`：显示 TX/RX 统计
- `Ctrl+t q`：退出

> 退出操作是**先按 `Ctrl+t`，松手后再按 `q`**，不是同时按。

### ⚙️ 配置文件：一次设置，反复使用

tio 支持配置文件，可以把常用参数固化下来，避免每次敲一长串命令。配置文件放在 `~/.config/tio/config` 或 `~/.tioconfig`。

**示例配置**（可以定义多个 profile）：

```ini
[default]
baudrate = 115200
databits = 8
flow = none
stopbits = 1
parity = none
auto-connect = direct
no-reconnect = false

[s0]
device = /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0
baudrate = 115200
timestamp = true
log = enable
log-strip = true

[usb-devices]
pattern = ^usb([1-9]*)
device = /dev/ttyUSB%m1
```

配置好之后，直接用 profile 名启动：

```bash
tio rpi3
```

甚至可以**在 profile 名两侧临时追加参数**，比如用 9600 波特率临时连 rpi3：

```bash
tio -b 9600 rpi3
```

### 🧰 其他实用选项

**本地回显**（确认你输入的字符是否被正确发送）：

```bash
tio -e /dev/ttyUSB0
```

**串口线路控制**（比如不触发 Arduino 复位）：可以配置 DTR/RTS 的脉冲时序，这在调试 ESP32 等板子时有用。

**网络套接字重定向**（把串口数据转发到 TCP 端口，供其他程序连接）：

```bash
tio /dev/ttyUSB0 --socket inet:4444
# 另一个终端连接
nc 127.0.0.1 4444
```
