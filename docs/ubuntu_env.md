**是的，强烈建议将「代码盘」和「软件工具盘」分开！**

这是 Docker / 开发环境的最佳实践之一。

### 为什么推荐分开？

| 项目         | 推荐做法               | 原因 |
|--------------|------------------------|------|
| **代码盘**   | 挂载到 `/workspace` 或 `/project` | 代码需要频繁修改、Git 操作、IDE 访问 |
| **工具盘**   | 挂载到 `/tools` 或 `/opt/tools` | 工具链、SDK、缓存等，不希望被代码污染 |
| **数据盘**   | 可选挂载 `/data`       | 数据库、数据集、大文件 |

---

### 推荐的最终切换脚本（已分离）

```bash
cat > ~/dev-switch.sh << 'EOF'
#!/bin/bash

case "$1" in
  20.04|20) TAG="20.04" ;;
  22.04|22) TAG="22.04" ;;
  24.04|24) TAG="24.04" ;;
  *) 
    echo "用法: $0 <版本>"
    echo "支持版本: 20.04  22.04  24.04"
    exit 1 ;;
esac

CONTAINER_NAME="dev-${TAG}"

echo "🚀 启动 Ubuntu ${TAG} 开发环境..."

docker run -it --rm \
    --name $CONTAINER_NAME \
    -v ~/Projects:/workspace \           # ← 代码盘（你的项目代码）
    -v ~/Tools:/tools \                  # ← 软件工具盘（SDK、工具链、缓存）
    -v ~/Data:/data \                    # ← 数据盘（可选）
    -v ~/.ssh:/root/.ssh:ro \            # SSH 密钥（只读）
    -w /workspace \
    ubuntu:${TAG} /bin/bash -c '
        apt update && apt install -y sudo curl wget git vim build-essential gcc g++ cmake python3 python3-pip gdb
        echo "======================================"
        echo "✅ 环境已就绪！"
        echo "代码目录  → /workspace"
        echo "工具目录  → /tools"
        echo "数据目录  → /data"
        echo "======================================"
        bash'
EOF

chmod +x ~/dev-switch.sh
```

---

### 主机目录建议结构

```bash
~/Projects/          # 所有代码项目（推荐）
~/Tools/             # 各种工具、SDK、编译缓存
~/Data/              # 大数据、数据库、测试文件
```

---

### 优点总结

- **代码干净**：只放源码，方便备份、Git 管理
- **工具复用**：不同版本容器可以共享 `/tools` 目录下的工具
- **数据隔离**：避免代码目录被缓存文件、下载文件污染
- **迁移方便**：换电脑时只需要复制这三个目录

---

**下一步建议**：

你主要开发什么语言？  
我可以帮你进一步优化：
- C/C++ 开发环境（GCC 多版本 + CMake + Conan/vcpkg）
- Python 开发（uv + venv 统一管理）
- Go / Rust / Node.js 等

告诉我你的技术栈，我给你最终完善版脚本。
