LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  sample.cpp 

LOCAL_C_INCLUDES := \
  $(LOCAL_PATH)/../../include \
  $(LOCAL_PATH)/../../include/VX_EXT \
  $(LOCAL_PATH)/../../include/libnn

LOCAL_CPP_EXTENSION := .cpp
LOCAL_SHARED_LIBRARIES := \
  libopenvx \
  libopenvx-nn \
  libnn \
  libmbase \
  liblog 

#LOCAL_MODULE_TAGS := optional
# 注释此行如果你希望保留符合和调试信息
LOCAL_STRIP_MODULE := false

LOCAL_MODULE:= inference

include $(BUILD_EXECUTABLE)
