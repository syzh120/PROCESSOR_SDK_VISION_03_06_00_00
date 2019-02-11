# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
DEST_ROOT=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
UTILS_INSTALL_DIR := $(xdc_PATH)

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/bin
  ifeq (cygwin,$(findstring cygwin,$(PATH)))
    COMMAND_SEPERATOR = ;
  else ifeq (mingw,$(findstring mingw,$(PATH)))
    COMMAND_SEPERATOR = ;
  else
    COMMAND_SEPERATOR = &
  endif
else
  # else, assume it is linux
  PATH_SEPARATOR = :
  UTILSPATH = /bin
  COMMAND_SEPERATOR = ;
endif

# BIOS
bios_INCLUDE = $(bios_PATH)/packages
export bios_INCLUDE

# IPC
ipc_INCLUDE = $(ipc_PATH)/packages
export ipc_INCLUDE

# MM
mm_INCLUDE = $(mm_PATH)
export mm_INCLUDE

# CE
ce_INCLUDE = $(ce_PATH)/packages
export ce_INCLUDE

# XDC
xdc_INCLUDE = $(xdc_PATH)/packages
export xdc_INCLUDE

# pdk drivers
pdk_INCLUDE = $(pdk_PATH)/packages
PACKAGE_SELECT=$(BSP_STW_PACKAGE_SELECT)
export PACKAGE_SELECT
export pdk_INCLUDE

include $(vision_sdk_PATH)/build/rtos/makerules/component.mk

vision_sdk_common_INCLUDE = $(vision_sdk_PATH)/common
export vision_sdk_common_INCLUDE

links_fw_INCLUDE = $(vision_sdk_PATH)/links_fw
export links_fw_INCLUDE

links_fw_rtos_INCLUDE = $(vision_sdk_PATH)/links_fw/src
export links_fw_rtos_INCLUDE

apps_src_INCLUDE = $(vision_sdk_PATH)/apps
export apps_src_INCLUDE

#FC include
fc_INCLUDE = $(fc_PATH)/packages
export fc_INCLUDE

#XDAIS include
xdais_INCLUDE = $(xdais_PATH)/packages
export xdais_INCLUDE

#JPEGVDEC include
jpegvdec_INCLUDE = $(jpegvdec_PATH)/packages
export jpegvdec_INCLUDE

#JPEGVENC include
jpegvenc_INCLUDE = $(jpegvenc_PATH)/packages
export jpegvenc_INCLUDE

#H264VENC include
h264venc_INCLUDE = $(h264venc_PATH)/packages
export h264venc_INCLUDE

#H264VDEC include
h264vdec_INCLUDE = $(h264vdec_PATH)/packages $(h264vdec_PATH)/packages/ti/sdo/codecs/h264vdec/
export h264vdec_INCLUDE

#HDVICP API
hdvicpapi_INCLUDE = $(hdvicplib_PATH)/packages
export hdvicpapi_INCLUDE

# DSP Algos
lane_detect_INCLUDE = $(lane_detect_PATH)/modules/ti_lane_detection/inc
export lane_detect_INCLUDE

object_detect_INCLUDE = $(object_detect_PATH)/modules/ti_object_detection/inc \
						$(object_detect_PATH)/modules/common
export object_detect_INCLUDE

object_classification_INCLUDE = $(object_classification_PATH)/modules/ti_object_classification/inc
export object_classification_INCLUDE

gpe_INCLUDE = $(gpe_PATH)/modules/ti_ground_plane_estimation/inc
export gpe_INCLUDE

sfm_INCLUDE = $(sfm_PATH)/modules/ti_sfm/inc
export sfm_INCLUDE

clr_INCLUDE = $(clr_PATH)/modules/ti_circular_light_recognition/inc
export clr_INCLUDE

fcw_INCLUDE = $(fcw_PATH)/modules/ti_forward_collision_warning/inc
export fcw_INCLUDE

stereo_postprocess_INCLUDE = $(stereo_postprocess_PATH)/modules/ti_stereovision/inc
export stereo_postprocess_INCLUDE

scene_obstruction_detect_INCLUDE= $(scene_obstruction_detect_PATH)/modules/ti_scene_obstruction_detect/inc
export scene_obstruction_detect_INCLUDE

tidl_INCLUDE= $(tidl_PATH)/modules/ti_dl/inc
export tidl_INCLUDE

tiop_INCLUDE= $(tiop_PATH)/modules/ti_object_propagation/inc
export tiop_INCLUDE

dmautils_INCLUDE= $(dmautils_PATH)/inc
export dmautils_INCLUDE

# EVE SW
evealg_INCLUDE = $(evealg_PATH)/ $(evealg_PATH)/common \
			$(evealg_PATH)/apps/apps_nonbam/inc \
			$(evealg_PATH)/apps/fast9_best_feature_to_front/algo/inc \
			$(evealg_PATH)/apps/pyramid_lk_tracker/algo/inc \
			$(evealg_PATH)/apps/remap_merge/algo/inc \
			$(evealg_PATH)/kernels/vlib/vcop_remap/inc \
			$(evealg_PATH)/apps/ti_pd_feature_plane_computation/algo/inc \
			$(evealg_PATH)/apps/yuv_scalar/algo/inc \
			$(evealg_PATH)/apps/filter_2d/algo/inc \
			$(evealg_PATH)/apps/yuv_padding/algo/inc \
			$(evealg_PATH)/apps/bin_image_to_list/algo/inc/ \
			$(evealg_PATH)/apps/harrisCornerDetection32/algo/inc/ \
			$(evealg_PATH)/apps/fft/algo/inc/ \
			$(evealg_PATH)/apps/peak_detection/algo/inc/ \
			$(evealg_PATH)/apps/beam_forming/algo/inc/ \
			$(evealg_PATH)/apps/clahe/algo/inc/

export evealg_INCLUDE

# Radar
radar_INCLUDE = $(vision_sdk_PATH)/apps/src/rtos/radar
export radar_INCLUDE

# Radar mmwavelink
radarLink_INCLUDE = $(radarLink_PATH) \
					$(radarLink_PATH)/ti/control/mmwavelink/include \
					$(radarLink_PATH)/ti/control/mmwavelink/source \
					$(radarLink_PATH)/ti/control/mmwavelink
radarFirmware_INCLUDE = $(radarMssFirmware_PATH) $(radarBssFirmware_PATH)   \
                        $(radarLink_PATH)/firmware
export radarLink_INCLUDE
export radarFirmware_INCLUDE

#OpenCV
ifeq ($(BUILD_OPENCV_SRC),yes)
opencv_INCLUDE = $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/include
else
opencv_INCLUDE = $(OpenCV_PREBUILD_PATH)/include
endif
export opencv_INCLUDE

#OpenCL
opencl_INCLUDE = $(OpenCL_PATH)/packages/ti/opencl/usr/include
export opencl_INCLUDE

#OpenVX
openvx_INCLUDE = $(OpenVX_PATH)/include $(OpenVX_PATH)/kernels/include
export openvx_INCLUDE

#VXLIB
vxlib_INCLUDE = $(VXLIB_PATH)/packages
export vxlib_INCLUDE

# ADAM CAR
adam_car_INCLUDE = $(vision_sdk_PATH)/apps/src/rtos/adam_car/
export adam_car_INCLUDE

# EDMA
edma_INCLUDE = $(edma_PATH)/packages
export edma_INCLUDE

vlib_INCLUDE = $(vlib_PATH)/packages
export vlib_INCLUDE

mathlib_INCLUDE = $(mathlib_PATH)/packages
export mathlib_INCLUDE

dsplib_INCLUDE = $(dsplib_PATH)/packages
export dsplib_INCLUDE

mmwavelib_INCLUDE = $(mmwavelib_PATH)/packages
export mmwavelib_INCLUDE

ndk_INCLUDE = $(ndk_PATH)/packages
export ndk_INCLUDE

nsp_INCLUDE = $(nsp_PATH)/packages
export nsp_INCLUDE

# AVBTP drivers
avbtp_INCLUDE = $(avbtp_PATH)/packages
export avbtp_INCLUDE

#UIA
uia_INCLUDE = $(uia_PATH)/packages
export uia_INCLUDE

# Package Name
PACKAGE_NAME = $(vision_sdk_RELPATH)
export PACKAGE_NAME

#
# Tools paths
#

# Cortex-A8
CODEGEN_PATH_A8 =

# DSP
CODEGEN_PATH_C674 = $(CODEGEN_PATH_DSP)


# Commands commonly used within the make files
RM = $(UTILSPATH)/rm
RMDIR = $(UTILSPATH)/rm -rf
MKDIR = $(UTILSPATH)/mkdir
ECHO = @$(UTILSPATH)/echo

#emake provides detailed info for build analysis.
EMAKE = emake --emake-emulation=gmake --emake-gen-subbuild-db=1 --emake-annodetail=waiting

ifeq ($(OS),Windows_NT)
  MAKE = gmake
#  MAKE =  $(EMAKE)
else
  MAKE = make
  CMAKE = cmake
endif
EGREP = $(UTILSPATH)/egrep
CP = $(UTILSPATH)/cp
ifeq ($(OS),Windows_NT)
  CHMOD = $(UTILSPATH)/echo
else
  CHMOD = $(UTILSPATH)/chmod
endif

ifeq ($(OS),Windows_NT)
  TOUCH=$(xdc_PATH)/bin/touch
  MKDIR=$(xdc_PATH)/bin/mkdir
  COPY=$(xdc_PATH)/bin/cp
  RM=$(xdc_PATH)/bin/rm
  MV=$(xdc_PATH)/bin/mv
  CAT=$(xdc_PATH)/bin/cat
else
  TOUCH=touch
  MKDIR=mkdir
  RM=rm
  COPY=cp
  MV=mv
  CAT=cat
  CHDIR_SHELL=$(SHELL)
  define chdir
	$(eval _D=$(firstword $(1) $(@D)))
	echo $_
	$(info $(MAKE): cd $(_D)) $(eval SHELL = cd $(_D); $(CHDIR_SHELL))
  endef
endif

#
# XDC specific ENV variables
#
# XDC Config.bld file (required for configuro); Derives from top-level vision_sdk_PATH
ifeq ($(SOCFAMILY),tda2xx)
 ifeq ($(SOC),tda2xx)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    CONFIG_BLD_XDC_m4     = $(vision_sdk_PATH)/build/rtos/tda2xx/config_m4.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(vision_sdk_PATH)/build/rtos/tda2xx/config_c66.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_arp32),)
    CONFIG_BLD_XDC_arp32 = $(vision_sdk_PATH)/build/rtos/tda2xx/config_arp32.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_a15),)
    CONFIG_BLD_XDC_a15 = $(vision_sdk_PATH)/build/rtos/tda2xx/config_a15.bld
  endif
 endif
 ifeq ($(SOC),tda2px)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    CONFIG_BLD_XDC_m4     = $(vision_sdk_PATH)/build/rtos/tda2px/config_m4.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(vision_sdk_PATH)/build/rtos/tda2px/config_c66.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_arp32),)
    CONFIG_BLD_XDC_arp32 = $(vision_sdk_PATH)/build/rtos/tda2px/config_arp32.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_a15),)
    CONFIG_BLD_XDC_a15 = $(vision_sdk_PATH)/build/rtos/tda2px/config_a15.bld
  endif
 endif
 ifeq ($(SOC),tda2ex)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    CONFIG_BLD_XDC_m4     = $(vision_sdk_PATH)/build/rtos/tda2ex/config_m4.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(vision_sdk_PATH)/build/rtos/tda2ex/config_c66.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_a15),)
    CONFIG_BLD_XDC_a15 = $(vision_sdk_PATH)/build/rtos/tda2ex/config_a15.bld
  endif
 endif
endif

ifeq ($(SOCFAMILY),tda3xx)
  ifeq ($(CONFIG_BLD_XDC_m4),)
    CONFIG_BLD_XDC_m4     = $(vision_sdk_PATH)/build/rtos/tda3xx/config_m4.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_66),)
    CONFIG_BLD_XDC_66     = $(vision_sdk_PATH)/build/rtos/tda3xx/config_c66.bld
  endif
  ifeq ($(CONFIG_BLD_XDC_arp32),)
    CONFIG_BLD_XDC_arp32 = $(vision_sdk_PATH)/build/rtos/tda3xx/config_arp32.bld
  endif
endif

XDCROOT = $(xdc_PATH)
XDCTOOLS = $(xdc_PATH)
BIOSROOT = $(bios_PATH)
export BIOSROOT
export XDCROOT
export XDCTOOLS

CGTOOLS = $(CODEGEN_PATH_M4)
export CGTOOLS

CGTOOLS_DSP = $(CODEGEN_PATH_C674)
export CGTOOLS_DSP

CODESOURCERYCGTOOLS = $(CODEGEN_PATH_A8)
export CODESOURCERYCGTOOLS

CGTOOLS_EVE = $(CODEGEN_PATH_EVE)
export CGTOOLS_EVE

CGTOOLS_A15 = $(CODEGEN_PATH_A15)
export CGTOOLS_A15

STRIP470 = $(CODEGEN_PATH_M4)/bin/strip470 -p
STRIP6x = $(CODEGEN_PATH_C674)/bin/strip6x -p
STRIP_ALL_ARM = $(CODEGEN_PREFIX)strip -s
STRIP_DEBUG_ARM = $(CODEGEN_PREFIX)strip --strip-debug

PATH += $(PATH_SEPARATOR)$(xdc_PATH)$(PATH_SEPARATOR)$(CODEGEN_PATH_M4)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_C674)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_EVE)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_A15)/bin$(PATH_SEPARATOR)$(CODEGEN_PATH_MSHIELD)/bin$(PATH_SEPARATOR)
export PATH

CHECK_YES = $(filter yes, $(subst emptyreplacement, ,$(1)))
export CHECK_YES

export TOUCH
export MKDIR
export COPY
export RM
export MV
export CAT
export COMMAND_SEPERATOR
export UTILSPATH
export CHMOD

# Nothing beyond this point

