## 获取视频编码

**接口描述**

> 获取设备的视频编码配置

**请求**

```json
{
  "cmd":"CODEC_VENC",
  "args": "G0C0S0",
  /*req, string, [G0#获取]*/
  "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
}
```

**响应**

```json
{
  "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
  "code": 0,
  "data": {
    "en":   1,
    /*req,int, 0 disable,1 enable*/
    "type": 1,
    /*req,int, 0 h265,1 h264,2 MJPEG,3 JPEG,4 MPEG4*/
    "width":        1920,
    /*req,int, Number of the columns of the Video image. 1920,1280,640*/
    "height":       1080,
    /*req, int, Number of the lines of the Video image.1080,720,360*/
    "fps":  25,
    /*req, int,range:[1,30]*/
    "gop":  50,
    /*req,int*/
    "bitrate":      8000,
    /*req,int*/
    "profile":      0,
    /*req,int ,The encoder profile,0 AVC_VASELINE, 1 AVC_MAIN, 2 AVC_HIGH, 3 HEVC_MAIN, 4 JPEG*/
    "qp":   0,
    /*req,int,Relative value for the video quantizers and the quality of the video,0 normal,1 high, 2 higher*/
    "lowdelay":     0
    /*0 disbale, 1 enable*/
  }
}
```
------

## 设置视频编码

**接口描述**

> 设置视频编码配置

**请求**

```json
{
  "cmd":"CODEC_VENC",
  "args": "G1C0S0",
  /*req, string, [G1#设置*/
  "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
  "data":{
  	"en":   1,
     /*req,int, 0 disable,1 enable*/
     "type": 1,
     /*req,int, 0 h265,1 h264,2 MJPEG,3 JPEG,4 MPEG4*/
     "width":        1920,
     /*req,int, Number of the columns of the Video image. 1920,1280,640*/
     "height":       1080,
     /*req, int, Number of the lines of the Video image.1080,720,360*/
     "fps":  25,
      /*req, int,range:[1,30]*/
     "gop":  50,
      /*req,int*/
     "bitrate":      8000,
      /*req,int*/
     "profile":      0,
     /*req,int ,The encoder profile,0 AVC_VASELINE, 1 AVC_MAIN, 2 AVC_HIGH, 3 HEVC_MAIN, 4 JPEG*/
     "qp":   0,
      /*req,int,Relative value for the video quantizers and the quality of the video,0 normal,1 high, 2 higher*/
     "lowdelay":     0
     /*0 disbale, 1 enable*/
  }
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
}
```
------

## 获取音频编码

**接口描述**

> 获取音频编码配置

**请求**

```json
{
  "cmd":"CODEC_AENC",
  "args": "G0C0S0",
  /*req, string, [G0#获取]*/
  "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
  "data": {
    {
      "en":   1,
      /*req,int, 0 disable,1 enable*/
      "type": 7,
      /*req,int ,5 ADPCM, 6 G711A, 7 G711U, 8 G726, 9 AAC*/
      "stereo":       0,
      /*req,int, 0 mono, 1 stereo*/
      "sprate":       16,
      /*req,int ,sample rate,16 16K,48 48K,...*/
      "vol":  100
      /*req,int ,audio in volume*/
    }
  }
}
```
------

## 设置音频编码

**接口描述**

> 配置设备音频编码通道

**请求**

```json
{
     "cmd":"CODEC_AENC",
     "args": "G1C0S0",
     /*req, string, [G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data":{
         "en":   1,
        /*req,int, 0 disable,1 enable*/
        "type": 7,
        /*req,int ,5 ADPCM, 6 G711A, 7 G711U, 8 G726, 9 AAC*/
        "stereo":       0,
        /*req,int, 0 mono, 1 stereo*/
        "sprate":       16,
        /*req,int ,sample rate,16 16K,48 48K,...*/
        "vol":  100
        /*req,int ,audio in volume*/
    }
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
}
```
------

## 获取音频输出

**接口描述**

> 获取设备音频输出配置

**请求**

```json
{
     "cmd":"CODEC_ADEC",
     "args": "G0C0S0",
     /*req, string, [G0#获取]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
  "data": {
  	"talk_en":      0,
  	/*req,int, 0 talkback disable, 1 talkback enable*/
  	"speech_en":    0,
  	/*req,int, 0 speech disable, 1 speech enable*/
  	"type": 7,
  	/*req,int,5 ADPCM, 6 G711A, 7 G711U, 8 G726, 9 AAC*/
  	"stereo":       0,
  	/*req,int ,0 mono, 1 stereo*/
  	"sprate":       16,
  	/*req,int, decode audio sample rate*/
  	"vol":  100
  	/*req,int ,mic volume*/
  }
}
```
------

## 设置音频输出

**接口描述**

> 设置设备音频输出配置

**请求**

```json
{
     "cmd":"CODEC_ADEC",
     "args": "G1C0S0",
     /*req, string, [G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data":{
        "talk_en":      0,
        /*req,int, 0 talkback disable, 1 talkback enable*/
        "speech_en":    0,
        /*req,int, 0 speech disable, 1 speech enable*/
        "type": 7,
        /*req,int,5 ADPCM, 6 G711A, 7 G711U, 8 G726, 9 AAC*/
        "stereo":       0,
        /*req,int ,0 mono, 1 stereo*/
        "sprate":       16,
        /*req,int, decode audio sample rate*/
        "vol":  100
        /*req,int ,mic volume*/
    }
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
}
```
------

## 语音播报

**接口描述**

> 设备语音播报

> 字段描述

> - type: 播报声音类型

```C
enum {
    GSF_SPEECH_FACTORY_TEST = 0,
    GSF_SPEECH_SYS_START = 1000,
    GSF_SPEECH_SYS_POWER_OFF = 1001,
    GSF_SPEECH_SYS_LOW_BATTERY = 1002,
    GSF_SPEECH_SYS_UP = 1003,
    GSF_SPEECH_SYS_SD_NO_EXIST = 1004,
    GSF_SPEECH_SYS_SD_ERR = 1005,
    GSF_SPEECH_SYS_RECORD_MANUAL_START = 1006,
    GSF_SPEECH_SYS_RECORD_MANUAL_STOP = 1007,
    GSF_SPEECH_SYS_RECORD_SMART_START = 1008,
    GSF_SPEECH_SYS_RECORD_SMART_STOP = 1009,
    GSF_SPEECH_SYS_TIMELOG_START = 1010,
    GSF_SPEECH_SYS_TIMELOG_STOP = 1011,
    GSF_SPEECH_NET_CONNECTING = 1100,
    GSF_SPEECH_NET_CONNECT_FAILED = 1101,
    GSF_SPEECH_NET_CONNECT_SUCCESS = 1102,
    GSF_SPEECH_NET_QR_SCAN_START = 1103,
    GSF_SPEECH_NET_QR_SCAN_ERR = 1104,
    GSF_SPEECH_NET_QR_SCAN_TIMEOUT = 1105,
    GSF_SPEECH_NET_BIND_SUCCESS = 1106,
    GSF_SPEECH_NET_BIND_FAILED = 1107,
    GSF_SPEECH_NET_APP_LINK = 1108,
    GSF_SPEECH_NET_LINK_ERR = 1109,
    GSF_SPEECH_NET_MODE_SWITCHING = 1110,
    GSF_SPEECH_NET_SWITCH_AP = 1111,
    GSF_SPEECH_NET_SWITCH_STA = 1112,
    GSF_SPEECH_ALARM = 2000,
    GSF_SPEECH_END,
};
```

**请求**

```json
{
     "cmd":"CODEC_SPEECH",
     "args": "G1C0S0",
     /*req, string, [G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data":{
        "type":  0
        /*req,int, sound type */
    }
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
}
```
------

## 设置指示灯模式

**接口描述**

>


```C
enum {
    GSF_LED_POWER_ON = 0,
    GSF_LED_WIFI_QR_SCAN,
    GSF_LED_WIFI_CONNECTING,
    GSF_LED_WIFI_CONNECTED,
    GSF_LED_WIFI_SLEEP_MODE,
};
```

**请求**

```json
{
     "cmd":"CODEC_GUIDE_LED",
     "args": "G1C0S0",
     /*req, string, [G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data":{
        "status":  0
        /*req,int, led mode */
    }
}
```

**响应**

```json
{
	"msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
	"code": 0,
}
```
------

## 获取指示灯模式

**接口描述**

>

```C
enum {
    GSF_LED_POWER_ON = 0,
    GSF_LED_WIFI_QR_SCAN,
    GSF_LED_WIFI_CONNECTING,
    GSF_LED_WIFI_CONNECTED,
    GSF_LED_WIFI_SLEEP_MODE,
};
```

**请求**

```json
{
     "cmd":"CODEC_GUIDE_LED",
     "args": "G0C0S0",
     /*req, string, [G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781"
}
```

**响应**

```json
{
    "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
    "code": 0,
    "data":{
        "status":  0
        /*req,int, led mode */
    }
}
```
------

## 获取图像镜像和翻转

**接口描述**

>

**请求**

```json
{
     "cmd":"CODEC_IMG_MIRROR_FLIP",
     "args": "G0C0S0",
     /*req, string, [G0#获取 G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781"
}
```

**响应**

```json
{
    "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
    "code": 0,
    "data": {
        "mirror_flip": 0
        /*req,int, 0 - nornmal 1 - mirror 2 - flip 3 - mirror and flip */
    }
}
```
------

## 设置图像镜像和翻转

**接口描述**

>

**请求**

```json
{
     "cmd":"CODEC_IMG_MIRROR_FLIP",
     "args": "G1C0S0",
     /*req, string, [G0#获取 G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data": {
        "mirror_flip": 0
        /*req,int, 0 - nornmal 1 - mirror 2 - flip 3 - mirror and flip */
    }
}
```

**响应**

```json
{
    "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
    "code": 0
}
```
------

## 电动镜头控制

**接口描述**

>

**请求**

```json
{
     "cmd":"CODEC_IMG_MIRROR_FLIP",
     "args": "G1C0S0",
     /*req, string, [G0#获取 G1#设置]*/
     "message_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
     "data": {
        "mirror_flip": 0
        /*req,int, 0 - nornmal 1 - mirror 2 - flip 3 - mirror and flip */
    }
}
```

**响应**

```json
{
    "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
    "code": 0
}
```
------


## 调试接口

**接口描述**

> 设置调试信息(日志等级)

**请求**

```json
{
  "cmd": "CODEC_DEBUG",
  "args": "G1C0S0",
  "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
  "data": {
    "log_level": 4,
    /*req, string, log level. 3 - error, 4 - warning, 5 - notice, 6 - info, 7 - debug*/
    "log_color": 0,
    /*req, string, log color valid. 0 - off, 1 - on*/
    "dbg_ai": 0
    /*req, string, debug audio input function. 0 - off, 1 - on 需要创建/tmp/mnt/sdcard/ai_dbg文件夹保存音频帧*/
  }
}
```

**响应**

```json
{
  "msg_id": "83151E9F-3947-41A9-76D1-D96AC9147781",
  "code": 0,
}
```
------

