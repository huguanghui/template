# CC-Swtich源码编译

Tauri 2 + React + Rust

## 环境核对

```
node --version
npm --version

npm install -g pnpm
pnpm --version

rustc --version
cargo --version


visualstudio c++生成工具
下载：
https://visualstudio.microsoft.com/visual-cpp-build-tools/
运行安装程序，勾选：
使用 C++ 的桌面开发

安装完成后重启电脑（建议）

安装 WebView2（Windows 10 通常已自带）

Windows 11：一般已预装
Windows 10：如果缺失，下载 Evergreen Bootstrapper：
https://developer.microsoft.com/en-us/microsoft-edge/webview2/
```

## 编译

```
# 1. 克隆源码
git clone https://github.com/farion1231/cc-switch.git
cd cc-switch

# 2. 安装依赖
pnpm install

# 3. 开发模式运行
pnpm dev

# 4. 正式打包
pnpm build
```
