# 测试

## 最推荐：xfrpc（最成熟、兼容性最好）

项目地址 [https://github.com/liudf0716/xfrpc]
特点:
纯 C 语言实现，完美兼容官方 frps 服务端。
支持常见的代理类型（TCP、UDP、HTTP、HTTPS 等）。
体积极小，非常适合 OpenWrt、嵌入式 Linux 等环境。
很多人在路由器上用它替代官方 frpc。

## tiny-frpc（极简 C 实现）

项目地址 [https://github.com/jifanchn/tiny-frpc]
特点:
轻量级、可移植的纯 C 实现。
重点支持 STCP（Secret TCP）。
依赖极少，适合嵌入式和资源受限场景。
可编译成静态库（libfrpc.a 等）。
