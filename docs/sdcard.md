### 工具对比

| 对比项             | H2testw                                    | CrystalDiskMark                             |
| ------------------ | ------------------------------------------ | ------------------------------------------- |
| **主要用途**       | 检测存储设备**容量造假**（扩容盘）         | 测试存储设备**读写性能**                    |
| **测试原理**       | 写入测试文件直到填满，再读回校验数据完整性 | 用不同块大小/队列深度测试顺序和随机读写速度 |
| **测试时间**       | 长（取决于容量，32GB需数小时）             | 短（几分钟）                                |
| **结果输出**       | 通过/失败 + 实际可用容量                   | MB/s 读写速度图表                           |
| **能发现的问题**   | 容量虚标、坏块、数据损坏                   | 读写速度瓶颈                                |
| **发现不了的问题** | 速度问题                                   | 容量造假、数据完整性                        |
| **适用设备**       | U盘、SD卡、TF卡                            | SSD、HDD、U盘、SD卡                         |
| **平台**           | Windows                                    | Windows（Linux 有 fio 替代）                |

---

### 使用场景推荐

**用 H2testw 的情况：**

- 购买了廉价 U盘/SD卡，怀疑容量造假
- 设备写入一定量后数据丢失或损坏
- 验证存储介质数据完整性

**用 CrystalDiskMark 的情况：**

- 评估 SSD 性能是否达标
- 对比不同存储设备速度
- 排查系统慢是否是存储瓶颈

---

### 嵌入式/Linux 场景的替代工具

```bash
# 替代 H2testw：f3（完全等价）
apt install f3
f3write /mnt/card    # 写入
f3read  /mnt/card    # 校验

# 替代 CrystalDiskMark：fio（更专业）
apt install fio

# 顺序读
fio --name=seq_read --rw=read --bs=1M --size=1G \
    --filename=/dev/mmcblk0 --direct=1

# 随机4K读写
fio --name=rand_rw --rw=randrw --bs=4k --size=512M \
    --filename=/dev/mmcblk0 --direct=1 --iodepth=32

# 简单速度测试（dd）
dd if=/dev/zero of=/mnt/card/test bs=1M count=512 conv=fdatasync
dd if=/mnt/card/test of=/dev/null bs=1M
```

---

### 总结

两个工具解决的是**完全不同的问题**，不存在替代关系，针对 SD 卡/U 盘建议两个都跑：先用 **H2testw 验证真实容量和完整性**，再用 **CrystalDiskMark 评估速度**。

### H2testw

**安装：**
直接下载绿色版，无需安装

官网：`https://www.heise.de/download/product/h2testw-50539`

**使用：**

```
1. 插入 U盘/SD卡
2. 打开 H2testw
3. Select Target → 选择目标盘符
4. 勾选 "only 1 GByte"（快速测试）或不勾（完整测试）
5. 点击 Write + Verify
6. 等待结果
```

结果判断：

```
Test finished without errors   → 容量真实，数据完整 ✅
The media is likely to be defective  → 存在坏块或容量造假 ❌
X.X GB OK / X.X GB DATA LOST  → 实际可用容量比标称小 ❌
```

---

### CrystalDiskMark

**安装：**

官网：`https://crystalmark.info/en/software/crystaldiskmark/`

下载 `CrystalDiskMark_x.x.x.exe` 安装版 或 `Portable` 免安装版

**使用：**

```
1. 打开 CrystalDiskMark
2. 左上角选择测试次数（默认 5 次）
3. 选择测试大小（默认 1GiB）
4. 右上角下拉选择目标盘符
5. 点击 All 开始全部测试
```

结果说明：

| 指标        | 含义                 | SD卡参考值           |
| ----------- | -------------------- | -------------------- |
| SEQ1M Q8T1  | 顺序读写（大文件）   | 读>80MB/s 为良好     |
| SEQ1M Q1T1  | 单队列顺序读写       | 接近标称速度         |
| RND4K Q32T1 | 随机小文件（多队列） | 关键性能指标         |
| RND4K Q1T1  | 随机小文件（单队列） | 嵌入式场景最接近实际 |

---

### 两个工具配合使用顺序

```
拿到新设备
    ↓
H2testw 完整测试（验证容量和完整性）
    ↓
通过 → CrystalDiskMark 测速（评估性能）
    ↓
对比标称速度，判断是否达标
```
