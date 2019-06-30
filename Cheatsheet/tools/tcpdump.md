[TOC]

tcpdump
===

## 命令

```shell
# 指定网络接口
$ tcpdump -i eth1
# 指定主机和端口
$ tcpdump tcp port 8000 host 192.168.3.125
# 指定端口和保存文件
$ tcpdump -i wlp3s0 "port 8000" -w tmp.pcap
```

