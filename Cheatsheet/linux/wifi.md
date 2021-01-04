[TOC]

## Wifi 操作速查表

### 切换到 AP 模式

关闭STA相关程序

```
killall wpa_supplicant
killall udhcpc
```

重新配置wifi网卡网络信息

```
$ ifconfig wlan0 223.223.100.1 netmask 255.255.255.0
$ route add default gw 223.223.100.1
```

AP信息配置

```
// hostapd.conf
interface=wlan0
driver=nl80211
ctrl_interface=/var/hostapd
ssid=ZWAP_IOTBAA-247266-TEST2
channel=6
hw_mode=g
ieee80211n=1
ht_capab=[SHORT-GI-20][SHORT-GI-40][HT40-]
wpa=3
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP CCMP
wpa_passphrase=01234567
```

AP程序启动

```
// 启动AP功能
hostapd -e /tmp/entropy.bin /tmp/hostapd.conf -B
// DHCP分配
udhcpd &
```

### 切换到 STA 模式

关闭AP相关程序

```
killall hostapd
killall udhcpd
```

STA 程序启动

```
wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B
udhcpc -i wlan0 -q &
```
