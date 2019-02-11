# (c) Texas Instruments

ifndef $(INCLUDES_MK)
INCLUDES_MK = 1


OSA_KERMOD_INC=-I$(memcache_PATH)/include -I$(memcache_PATH)/include/osa

LINUX_COMMON_INC = -I$(vision_sdk_PATH)/hlos/include -I$(LINUX_TARGETFS)/usr/include

LINK_API_INC = -I$(vision_sdk_PATH)/links_fw/include/link_api

COMMON_INC= -I. -I$(vision_sdk_PATH)/ -I$(vision_sdk_PATH)/links_fw -I$(vision_sdk_PATH)/links_fw/include/config/$(MAKEAPPNAME)/$(MAKECONFIG)

OSA_INC = -I$(vision_sdk_PATH)/links_fw/src/hlos/osa/include

SGX_DRM_INC = -I$(LINUX_TARGETFS)/usr/include/libdrm -I$(LINUX_TARGETFS)/usr/include -I$(LINUX_TARGETFS)/usr/include/EGL

ADAM_CAR_INC = -I$(vision_sdk_PATH)/apps/src/hlos/adam_car -I$(vision_sdk_PATH)/apps/src/rtos/adam_car

COMMON_LFLAGS = -L$(LINUX_TARGETFS)/usr/lib -Wl,--rpath-link,$(LINUX_TARGETFS)/usr/lib -L$(LINUX_TARGETFS)/lib -Wl,--rpath-link,$(LINUX_TARGETFS)/lib -lrt

#PLAT_LINK =  $(COMMON_LFLAGS) -lEGL -lGLESv2 -lgbm -ldrm -ldrm_omap -Wl,-Bstatic -logles2tools, -Wl,-Bdynamic
PLAT_LINK =  $(COMMON_LFLAGS) -lEGL -lGLESv2 -lgbm -ldrm -ldrm_omap
ifeq ($(OPENCL_INCLUDE),yes)
PLAT_LINK += -locl_util -lOpenCL
endif

DEFINE += -DA15_TARGET_OS_LINUX -DLINUX_BUILD -DDYNAMIC_LUT -DPLATFORM_EGL

ifeq ($(BUILD_FOR_ANDROID), yes)
  ANDROID_COMMON_INC += \
                     -I$(LINUX_TARGETFS)/bionic/libc/arch-arm/include \
                     -I$(LINUX_TARGETFS)/bionic/libc/include \
                     -I$(LINUX_TARGETFS)/bionic/libc/kernel/uapi \
                     -I$(LINUX_TARGETFS)/bionic/libc/kernel/uapi/asm-arm \
                     -I$(LINUX_TARGETFS)/bionic/libm/include \
                     -I$(LINUX_TARGETFS)/bionic/libm/include/arm \
                     -I$(LINUX_TARGETFS)/external/libcxx/include \
                     -I$(LINUX_TARGETFS)/bionic/libstdc++/include \
                     -I$(LINUX_TARGETFS)/system/core/include \
                     -I$(LINUX_TARGETFS)/frameworks/native/opengl/include
  DEFINE += -DANDROID
  LINUX_COMMON_INC += $(ANDROID_COMMON_INC)
  SGX_DRM_INC += $(ANDROID_COMMON_INC)
endif

ifeq ($(PROC_IPU1_0_INCLUDE),yes)
  DEFINE += -DPROC_IPU1_0_INCLUDE
endif

ifeq ($(PROC_IPU1_1_INCLUDE),yes)
  DEFINE += -DPROC_IPU1_1_INCLUDE
endif

ifeq ($(PROC_IPU2_INCLUDE),yes)
  DEFINE += -DPROC_IPU2_INCLUDE
endif

ifeq ($(PROC_DSP1_INCLUDE),yes)
  DEFINE += -DPROC_DSP1_INCLUDE
endif

ifeq ($(PROC_DSP2_INCLUDE),yes)
  DEFINE += -DPROC_DSP2_INCLUDE
endif

ifeq ($(PROC_EVE1_INCLUDE),yes)
  DEFINE += -DPROC_EVE1_INCLUDE
endif

ifeq ($(PROC_EVE2_INCLUDE),yes)
  DEFINE += -DPROC_EVE2_INCLUDE
endif

ifeq ($(PROC_EVE3_INCLUDE),yes)
  DEFINE += -DPROC_EVE3_INCLUDE
endif

ifeq ($(PROC_EVE4_INCLUDE),yes)
  DEFINE += -DPROC_EVE4_INCLUDE
endif

ifeq ($(PROC_A15_0_INCLUDE),yes)
  DEFINE += -DPROC_A15_0_INCLUDE
endif

ifeq ($(IPU_PRIMARY_CORE),ipu1_0)
  DEFINE += -DIPU_PRIMARY_CORE_IPU1
endif

ifeq ($(IPU_PRIMARY_CORE),ipu2)
  DEFINE += -DIPU_PRIMARY_CORE_IPU2
endif

ifeq ($(IPUMM_INCLUDE), yes)
  DEFINE += -DIPUMM_INCLUDE
endif

ifeq ($(BUILD_INFOADAS), yes)
  DEFINE += -DBUILD_INFOADAS
endif

ifeq ($(ENABLE_OPENCV),yes)
  DEFINE += -DENABLE_OPENCV
endif

ifeq ($(EARLY_USECASE_ENABLE),yes)
		DEFINE += -DEARLY_USECASE_ENABLE
endif

endif # ifndef $(INCLUDES_MK)

