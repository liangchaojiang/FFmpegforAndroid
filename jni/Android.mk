LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libavcodec
LOCAL_SRC_FILES:= libavcodec-53.so
include $(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libavformat
LOCAL_SRC_FILES:= libavformat-53.so
include $(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libswscale
LOCAL_SRC_FILES:= libswscale-2.so
include $(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libavutil
LOCAL_SRC_FILES:= libavutil-51.so
include $(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libavfilter
LOCAL_SRC_FILES:= libavfilter-2.so
include $(PREBUILT_SHARED_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= libswresample
LOCAL_SRC_FILES:= libswresample-0.so
include $(PREBUILT_SHARED_LIBRARY)



include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg_codec
LOCAL_SRC_FILES := com_example_moscal_FFmpegNative.c ParsePcap.c ParseTs.c
LOCAL_LDLIBS := -llog -ljnigraphics -lz -landroid
LOCAL_SHARED_LIBRARIES := libavcodec libavformat libswscale libavutil libavfilter libswresample 
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_LDLIBS    := -lm -llog 
LOCAL_MODULE    := Parse
LOCAL_SRC_FILES := ParsePcap.c ParseTs.c  Parse.c

include $(BUILD_EXECUTABLE)


