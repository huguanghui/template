**问题诊断**：

你手动运行命令时出现的错误：

```
FATA[0000] Parse config error: proxy 2: unsupport proxy type: vless
```

**核心原因**：  
你当前使用的 **Clash** 是**原始官方内核**（Dreamacro/clash），它**不支持 `vless` 协议**。  
你的配置文件 `/etc/clash/config.yaml` 中第 2 个代理节点（proxy 2）使用了 `type: vless`，这是现代机场/订阅常见的协议，而旧版 Clash 只支持 vmess、ss、trojan 等，**不支持 vless、hysteria2、tuic 等新协议**。

这是 Linux 上 Clash 服务最常见的报错之一，尤其当你从机场订阅导入配置时。

### 推荐解决方案（强烈建议换成 Meta 内核）

**Clash Meta**（也叫 **Mihomo**）是目前社区维护的主流版本，它完全支持 `vless`（包括 vless+reality、vless+ws+tls 等），性能更好，功能更全。

#### 步骤 1：下载并替换 Clash 二进制为 Meta 版本

在你的服务器（hgh-NUC12DCMi9，应该是 amd64 架构）执行以下命令：

```bash
# 1. 停止当前服务
sudo systemctl stop clash.service

# 2. 下载最新 Clash Meta（mihomo）Linux amd64 版本
cd /tmp
wget https://github.com/MetaCubeX/mihomo/releases/latest/download/mihomo-linux-amd64-compatible.tar.gz

# 3. 解压并替换
tar -xzf mihomo-linux-amd64-compatible.tar.gz
sudo mv /usr/local/bin/clash /usr/local/bin/clash.bak          # 备份旧版
sudo mv mihomo /usr/local/bin/clash
sudo chmod +x /usr/local/bin/clash

# 4. 验证版本（应该显示 mihomo 或 Meta 相关信息）
clash --version
```

#### 步骤 2：重新启动服务并验证

```bash
# 重置失败计数
sudo systemctl reset-failed clash.service

# 启动服务
sudo systemctl start clash.service

# 查看状态和日志
sudo systemctl status clash.service
sudo journalctl -u clash.service -e
```

如果启动成功，你应该看到类似 “Clash Meta” 或 “mihomo” 的启动信息，且不再报 `unsupport proxy type: vless`。

#### 步骤 3：（可选）更新 systemd 服务文件（推荐）

检查你的服务文件，确保 ExecStart 正确指向新二进制：

```bash
sudo systemctl cat clash.service
```

如果需要修改，通常是这样的（常见配置）：

```ini
[Unit]
Description=Clash Daemon
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/clash -d /etc/clash
Restart=always
RestartSec=3
LimitNOFILE=65535

[Install]
WantedBy=multi-user.target
```

修改后执行：
```bash
sudo systemctl daemon-reload
sudo systemctl restart clash.service
```

### 其他注意事项

- **配置文件不需要改**：你的 `/etc/clash/config.yaml` 可以继续使用，Meta 内核能完美兼容旧配置 + vless 节点。
- **端口 7890**：启动成功后，Go 的代理问题应该也能解决（记得把 GOPROXY 设为 `https://goproxy.cn,direct`）。
- **更新订阅**：以后订阅链接建议使用支持 Meta 的转换器，或直接用支持 vless 的订阅。
- 如果你想用图形界面管理，推荐在本地电脑用 **Clash Verge Rev**（它默认使用 Meta 内核）。

**快速测试**（不通过 systemd）：
```bash
sudo /usr/local/bin/clash -d /etc/clash
```

执行完上面替换步骤后，把 `clash --version` 和 `sudo systemctl status clash.service` 的输出贴给我，我帮你确认是否成功。

需要我给你完整的下载最新版本的命令（带版本号防失效），或者帮你调整服务文件吗？直接说。
