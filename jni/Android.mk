LOCAL_PATH := $(call my-dir)
SRC_DIR := ../src

VULKAN_INCLUDE := $(VULKAN_SDK)/include
LAYER_INCLUDE := ../layer

include $(CLEAR_VARS)
LOCAL_MODULE := VkLayer_object_tracker
LOCAL_SRC_FILES +=  $(SRC_DIR)/layer_factory.cpp \
                    $(LAYER_INCLUDE)/vk_format_utils.cpp \
                    $(LAYER_INCLUDE)/vk_layer_config.cpp \
                    $(LAYER_INCLUDE)/vk_layer_extension_utils.cpp \
                    $(LAYER_INCLUDE)/vk_layer_utils.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SRC_DIR) \
                    $(LOCAL_PATH)/$(LAYER_INCLUDE) \
                    $(VULKAN_INCLUDE)
                   
LOCAL_CPPFLAGS += -std=c++11 -Wall -Werror -Wno-unused-function -Wno-unused-const-variable
# LOCAL_CPPFLAGS += -DVK_ENABLE_BETA_EXTENSIONS -DVK_USE_PLATFORM_ANDROID_KHR -DVK_PROTOTYPES -fvisibility=hidden

# include android logging and others
LOCAL_LDLIBS    := -llog -landroid

#LOCAL_LDFLAGS   += -Wl,-Bsymbolic
#LOCAL_LDFLAGS   += -Wl,--exclude-libs,ALL
include $(BUILD_SHARED_LIBRARY)
