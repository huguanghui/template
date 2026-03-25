## v4l2-ctl

### --list-devices

> 列出所有v4l2设备

```bash
root@orangepi5plus:~# v4l2-ctl --list-devices
rk_hdmirx (fdee0000.hdmirx-controller):
        /dev/video0
```

### --get-dv-timings

> 查询当前设备（如 HDMI 采集卡或 SDI 输入端）正在使用的详细数字视频计时参数

```bash
root@orangepi5plus:~# v4l2-ctl --get-dv-timings
DV timings:
        Active width: 3840
        Active height: 2160
        Total width: 4400
        Total height: 2250
        Frame format: progressive
        Polarities: -vsync -hsync
        Pixelclock: 296696000 Hz (29.97 frames per second)
        Horizontal frontporch: 176
        Horizontal sync: 88
        Horizontal backporch: 296
        Vertical frontporch: 8
        Vertical sync: 10
        Vertical backporch: 72
        Standards:
        Flags:
```

### dv处理

> 设置的参数必须在它预设的“支持列表”中。即使 query 到了，如果不在列表里，它也会拒绝

```bash
v4l2-ctl -d /dev/video0 --list-dv-timings
v4l2-ctl -d /dev/video0 --set-dv-bt-timings index=14
v4l2-ctl --device /dev/video0 --stream-mmap --stream-to=test.raw --stream-count=100
```

`gst-launch-1.0` 是 **GStreamer** 框架下的一个命令行工具，被誉为多媒体开发的“瑞士军刀”。它主要用于快速构建、测试和运行多媒体流水线（Pipeline），而无需编写 C 或 Python 代码。

既然你正在使用 **Orange Pi 5 Plus (RK3588)** 调试 HDMI-In，掌握 `gst-launch-1.0` 将极大提高你的效率，因为它能利用 RK3588 的 **MPP 硬解码/硬编码加速**。

---

### 1. 基本语法结构

```bash
gst-launch-1.0 [OPTIONS] ELEMENT1 ! ELEMENT2 ! ELEMENT3
```

- **`!` (感叹号)**：连接符，表示将前一个元件的输出传给后一个元件的输入。
- **元件 (Element)**：流水线的最小单元。分为三类：
  - **Source (源)**：产生数据（如 `v4l2src`, `filesrc`）。
  - **Filter/Convert (转换)**：处理数据（如 `videoconvert`, `v4l2h264enc`）。
  - **Sink (接收器)**：输出数据（如 `autovideosink`, `filesink`）。

---

### 2. 核心概念：Caps (能力/格式限制)

在两个元件之间，通常需要指定格式（分辨率、帧率、像素格式），这被称为 **Caps**。
**格式：** `video/x-raw,width=1920,height=1080,format=NV12`

---

### 3. RK3588 常用专用元件

针对 Orange Pi 5 Plus，这些元件调用了瑞芯微的硬件加速：

- **`v4l2src`**：调用摄像头或 HDMI-In。
- **`mpph264enc` / `mpph265enc`**：硬件 H.264/H.265 编码器。
- **`mppvideodec`**：硬件解码器。
- **`rkximagesink`**：高性能视频渲染输出。

---

### 4. 实用命令示例

#### A. 基础测试：显示测试画面

```bash
gst-launch-1.0 videotestsrc ! autovideosink
```

#### B. 重点：从 HDMI-In (/dev/video0) 抓取并预览

针对你之前的 4K 信号，使用 GStreamer 预览（会自动处理 Buffer）：

```bash
gst-launch-1.0 v4l2src device=/dev/video0 ! \
    video/x-raw,format=NV12,width=3840,height=2160,framerate=30/1 ! \
    videoconvert ! \
    autovideosink
```

_注意：如果报错，请确保先运行了 `v4l2-ctl -d /dev/video0 --set-dv-bt-timings query`。_

#### C. HDMI-In 硬件编码存为 H.264 文件

这比 `v4l2-ctl` 抓取 `.raw` 更实用，因为它经过了硬件压缩，节省空间：

```bash
gst-launch-1.0 -e v4l2src device=/dev/video0 ! \
    video/x-raw,format=NV12,width=3840,height=2160 ! \
    mpph264enc ! \
    h264parse ! \
    mp4mux ! \
    filesink location=output.mp4
```

- `-e`：在按 Ctrl+C 停止时发送 EOS 信号，确保 MP4 文件头被正确写入，否则视频无法播放。

#### D. 网络推流 (UDP)

将 HDMI-In 画面推送到另一台电脑：

```bash
# Orange Pi 端 (IP 假设为 192.168.1.10)
gst-launch-1.0 v4l2src device=/dev/video0 ! \
    video/x-raw,format=NV12,width=1920,height=1080 ! \
    mpph264enc ! \
    rtph264pay ! \
    udpsink host=192.168.1.100 port=5000
```

---

### 5. 常用参数说明

- **`-v` (Verbose)**：打印详细状态信息，可以看到两个元件之间最终协商（Negotiate）出的 Caps 是什么。
- **`-e` (EOS)**：关闭流时优雅退出，录制文件时必带。
- **`prop=value`**：给元件设置属性。例如 `v4l2src io-mode=4`（使用 dmabuf 提高性能）。

---

### 6. 调试小技巧

如果你不知道某个元件支持什么格式，可以使用 `gst-inspect-1.0`：

```bash
# 查看 v4l2src 支持的所有参数和格式
gst-inspect-1.0 v4l2src

# 查看 RK3588 的编码器支持什么输入
gst-inspect-1.0 mpph264enc
```

### 针对你目前 HDMI-In 调试的建议

你之前 `v4l2-ctl` 设置 Timing 失败，GStreamer 有时能绕过某些权限限制或自动尝试更多配置。你可以尝试运行：

```bash
# 使用 GStreamer 强制拉流
gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,width=3840,height=2160 ! fakesink dump=true num-buffers=1
```

如果这个命令能跑通（不报错），说明硬件链路是通的，只是 `v4l2-ctl` 的参数校验比较死板。

```
gst-launch-1.0 videotestsrc pattern=18 !     videoconvert !     video/x-raw,format=BGRx,width=2560,height=1440 !     kmssink driver-name=rockchip connector-id=208 plane-id=57
gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=BGRx,width=2560,height=1440 ! kmssink driver-name=rockchip
connector-id=208 plane-id=57
```

操作分析

```
gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=BGRx,width=1920,height=1080 ! kmssink driver-name=rockchip
connector-id=208 plane-id=57 force-aspect-ratio=false sync=false
```

```
gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=BGRx ! kmssink driver-name=rockchip connector-id=208 plane-id=57 force-aspect-ratio=true sync=false
```

```
root@orangepi5plus:~# v4l2-ctl -d /dev/video0 --set-dv-bt-timings index=16
BT timings set
root@orangepi5plus:~# gst-launch-1.0 v4l2src device=/dev/video0 ! kmssink driver-name=rockchip connector-id=208 plane-id=57 force-aspect-ratio=false sync=false
```

```
gst-launch-1.0 v4l2src device=/dev/video0 ! \
    tee name=t \
    t. ! queue ! kmssink driver-name=rockchip connector-id=208 plane-id=57 force-aspect-ratio=true sync=false \
    t. ! queue ! filesink location=alg_input.raw
```
