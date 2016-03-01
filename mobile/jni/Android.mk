LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= libmg
ifeq ($(ANDROID_DEBUG), on)
ifeq ($(USE_AES_ECB), on)
LOCAL_SRC_FILES:= \
	../../src/aes.c \
	../../src/adapter.c
endif
ifeq ($(USE_AES_CBC), on)
LOCAL_SRC_FILES:= \
	../../src/aes.c \
	../../src/adapter.c
endif
ifeq ($(USE_DES), on)
LOCAL_SRC_FILES:= \
	../../src/des.c \
	../../src/adapter.c
endif
ifeq ($(USE_3DES), on)
LOCAL_SRC_FILES:= \
	../../src/des.c \
	../../src/adapter.c
endif
ifeq ($(USE_RC4), on)
LOCAL_SRC_FILES:= \
	../../src/rc4.c \
	../../src/adapter.c
endif
else
ifeq ($(USE_AES_ECB), on)
LOCAL_SRC_FILES:= \
	xcode/aes.cloak.c \
	xcode/adapter.cloak.c
endif
ifeq ($(USE_AES_CBC), on)
LOCAL_SRC_FILES:= \
	xcode/aes.cloak.c \
	xcode/adapter.cloak.c
endif
ifeq ($(USE_DES), on)
LOCAL_SRC_FILES:= \
	xcode/des.cloak.c \
	xcode/adapter.cloak.c
endif
ifeq ($(USE_3DES), on)
LOCAL_SRC_FILES:= \
	xcode/des.cloak.c \
	xcode/adapter.cloak.c
endif
ifeq ($(USE_RC4), on)
LOCAL_SRC_FILES:= \
	xcode/rc4.cloak.c \
	xcode/adapter.cloak.c
endif
endif
LOCAL_C_INCLUDES+= \

LOCAL_CFLAGS := -fdata-sections -ffunction-sections -DANDROID
ifeq ($(ANDROID_DEBUG), on)
	LOCAL_CFLAGS += -DLOG_OUT
endif
ifeq ($(USE_AES_CBC), on)
	LOCAL_CFLAGS += -DUSE_AES_CBC
endif
ifeq ($(USE_AES_ECB), on)
	LOCAL_CFLAGS += -DUSE_AES_ECB
endif
ifeq ($(USE_DES), on)
	LOCAL_CFLAGS += -DUSE_DES
endif
ifeq ($(USE_3DES), on)
	LOCAL_CFLAGS += -DUSE_3DES
endif
ifeq ($(USE_RC4), on)
	LOCAL_CFLAGS += -DUSE_RC4
endif
LOCAL_CXXFLAGS:=$(LOCAL_CFLAGS)
LOCAL_PRELINK_MODULE:=false
include $(BUILD_STATIC_LIBRARY)
