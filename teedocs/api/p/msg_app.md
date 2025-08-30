---
title: APP通信协议
keywords: protcol, apps
desc: description for this article
date: 2025-08-06
---

## HTTP 的 URL

> http://ip/api/msg

<!-- ![http_msg](/static/image/http_msg.png) -->
<img src="/static/image/http_msg.png" class="white_border shadow-xl rounded-md">

## 设备信息

**接口描述**

> 获取设备基础信息

**请求**

```json
{
  "cmd": "APPS_DEV_INFO",
  "args": "G0C0S0",
  "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781"
}
```

**响应**

```json
{
  "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
  "code": 0,
  "data": {
    "model": "SC-AI26",
    "ver": "20221230"
    "ssid": "HUAWEI-APP4QY",
    "rssi": 99,
    "ip": "192.168.3.1",
    "mac": "70:3A:2D:16:4E:5B",
    "wifi_ver": "V1.1.23"
  }
}
```

