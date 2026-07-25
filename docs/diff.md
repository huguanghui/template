# diff使用

> 使用tudiff来进行目录差异对比

## 安装

```
cargo install tudiff
mkdir -p ~/.local/bin
cat > ~/.local/bin/vimdiff << 'EOF'
#!/bin/bash
exec nvim -d "$@"
EOF
chmod +x ~/.local/bin/vimdiff
```
