ifeq ($(BUILD_OS),Windows_NT)
  TI_SW_ROOT      := $(abspath ../..)/ti_components
endif

ifeq ($(BUILD_OS),Linux)
  TI_SW_ROOT      := $(abspath ../..)/ti_components
  # or /opt/ti if you follow the package installers
endif

export SDK_INSTALL_PATH ?= $(TI_SW_ROOT)/../
infoadas_PATH  ?=

#
# Code gen and config tools
#

ifeq ($(BUILD_OS),Windows_NT)
CODEGEN_PATH_DSP ?= $(TI_SW_ROOT)/cg_tools/windows/ti-cgt-c6000_8.2.4
CODEGEN_PATH_EVE ?= $(TI_SW_ROOT)/cg_tools/windows/arp32_1.0.7
CODEGEN_PATH_A15 ?= $(TI_SW_ROOT)/cg_tools/windows/gcc-arm-none-eabi-4_9-2015q3
CODEGEN_PATH_M4  ?= $(TI_SW_ROOT)/cg_tools/windows/ti-cgt-arm_16.9.2.LTS
TI_OCL_CGT_INSTALL ?= $(CODEGEN_PATH_DSP)
endif

ifeq ($(BUILD_OS),Linux)
CODEGEN_PATH_DSP ?= $(TI_SW_ROOT)/cg_tools/linux/ti-cgt-c6000_8.2.4
CODEGEN_PATH_EVE ?= $(TI_SW_ROOT)/cg_tools/linux/arp32_1.0.7
CODEGEN_PATH_M4  ?= $(TI_SW_ROOT)/cg_tools/linux/ti-cgt-arm_16.9.2.LTS
TI_OCL_CGT_INSTALL ?= $(CODEGEN_PATH_DSP)

ifeq ($(A15_TARGET_OS),Bios)
CODEGEN_PATH_A15 ?=$(TI_SW_ROOT)/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3
endif

ifeq ($(A15_TARGET_OS),Linux)
CODEGEN_PATH_A15     ?= $(TI_SW_ROOT)/os_tools/linux/linaro/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf
A15_TOOLCHAIN_PREFIX ?= $(CODEGEN_PATH_A15)/bin/arm-linux-gnueabihf-
endif

ifeq ($(A15_TARGET_OS),Qnx)
ifeq ($(QNX_HOST), )
  $(error QNX_HOST does not exist or not set! )
endif
CODEGEN_PATH_A15 ?= $(QNX_HOST)
ifeq ($(QCONF_OVERRIDE), )
  $(error QCONF_OVERRIDE does not exist or not set! )
endif
ifeq ($(QNX_TARGETFS), )
  $(error QNX_TARGETFS does not exist or not set! )
endif
ifeq ($(infoadas_PATH), )
  $(error infoadas_PATH does not exist or not set! )
endif
endif
endif

#
# BIOS, IPC and XDC, M4 Codegen
#

ifeq ($(PLATFORM),$(filter $(PLATFORM), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-mc tda2xx-rvp tda3xx-evm tda3xx-rvp))
    bios_PATH ?= $(TI_SW_ROOT)/os_tools/bios_6_46_06_00
    ifeq ($(RADAR_ONLY),no)
        ipc_PATH  ?= $(TI_SW_ROOT)/os_tools/ipc_3_45_00_00
    endif
    ifeq ($(BUILD_OS),Windows_NT)
        xdc_PATH  ?= $(TI_SW_ROOT)/os_tools/windows/xdctools_3_32_01_22_core
    endif
    ifeq ($(BUILD_OS),Linux)
        xdc_PATH  ?= $(TI_SW_ROOT)/os_tools/linux/xdctools_3_32_01_22_core
    endif
endif


ifeq ($(A15_TARGET_OS),Linux)
#
# Path where linux uImage, uboot etc will be copied to after build
#
LINUX_BOOT_OUT_FILES =$(DEST_ROOT)/hlos/linux/boot
LINUX_TARGETFS ?=$(vision_sdk_PATH)/../ti_components/os_tools/linux/targetfs

kernel_PATH ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/kernel/omap
cmem_PATH ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/kernel/cmem/ludev
debugss_PATH ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/kernel/dsptop/debugss_module/debugss-mod
gdbc6x_PATH ?=  $(vision_sdk_PATH)/../ti_components/os_tools/linux/kernel/gdbc6x/kernel_module/gdbproxy-mod
kernel_addon_PATH ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/kernel/linux-kernel-addon
memcache_PATH ?= $(kernel_addon_PATH)/memcache
shm_PATH := $(infoadas_PATH)/../plat/linux/lib/shmem/inc
uboot_PATH  ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/u-boot/u-boot
sgx_PATH ?= $(vision_sdk_PATH)/../ti_components/os_tools/linux/sgx/omap5-sgx-ddk-linux
pvr_PATH ?= $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils
mm_PATH ?= $(vision_sdk_PATH)/../ti_components/codecs/ipumm
ce_PATH ?= $(TI_SW_ROOT)/codecs/codec_engine_3_24_00_08
endif

ifeq ($(A15_TARGET_OS),Qnx)
pvr_PATH ?= $($(MAKEAPPNAME)_PATH)/src/hlos/modules/sgxRenderUtils
endif

#
# Low-level drivers
#
pdk_PATH         ?= $(TI_SW_ROOT)/drivers/pdk_01_10_02_07
edma_PATH        ?= $(TI_SW_ROOT)/drivers/edma3_lld_02_12_00_21

#
# Networking related packages
#
ndk_PATH   ?= $(TI_SW_ROOT)/networking/ndk_2_24_02_31
nsp_PATH   ?= $(TI_SW_ROOT)/networking/nsp_gmacsw_4_16_00_00
avbtp_PATH ?= $(TI_SW_ROOT)/networking/avbtp_0_10_00_00

#
# Algorithm related packages
#
fc_PATH                       ?= $(TI_SW_ROOT)/codecs/framework_components_3_40_02_07
xdais_PATH                    ?= $(TI_SW_ROOT)/codecs/xdais_7_24_00_04
hdvicplib_PATH                ?= $(TI_SW_ROOT)/codecs/ivahd_hdvicp20api_01_00_00_23_production
jpegvenc_PATH                 ?= $(TI_SW_ROOT)/codecs/ivahd_jpegvenc_01_00_16_01_production
jpegvdec_PATH                 ?= $(TI_SW_ROOT)/codecs/ivahd_jpegvdec_01_00_13_01_production
h264venc_PATH                 ?= $(TI_SW_ROOT)/codecs/ivahd_h264enc_02_00_09_01_production
h264vdec_PATH                 ?= $(TI_SW_ROOT)/codecs/ivahd_h264vdec_02_00_17_01_production
evealg_PATH                   ?= $(TI_SW_ROOT)/algorithms/eve_sw_01_19_00_00
vlib_PATH                     ?= $(TI_SW_ROOT)/algorithms/vlib_c66x_3_3_2_0
lane_detect_PATH              ?= $(TI_SW_ROOT)/algorithms/REL.200.V.LD.C66X.00.03.00.00/200.V.LD.C66X.00.03
object_detect_PATH            ?= $(TI_SW_ROOT)/algorithms/REL.200.V.OD.C66X.00.06.02.00/200.V.OD.C66X.00.06
object_classification_PATH    ?= $(TI_SW_ROOT)/algorithms/REL.200.V.OC.C66X.00.02.00.00/200.V.OC.C66X.00.02
stereo_postprocess_PATH       ?= $(TI_SW_ROOT)/algorithms/REL.200.V.ST.C66X.00.03.00.00/200.V.ST.C66X.00.03.00.00
clr_PATH                      ?= $(TI_SW_ROOT)/algorithms/REL.200.V.CLR.C66X.00.02.00.00/200.V.CLR.C66X.00.02
mathlib_PATH                  ?= $(TI_SW_ROOT)/algorithms/mathlib_c66x_3_1_0_0
scene_obstruction_detect_PATH ?= $(TI_SW_ROOT)/algorithms/REL.200.V.SOD.C66X.00.02.00.00/200.V.SOD.C66X.02.00
sfm_PATH                      ?= $(TI_SW_ROOT)/algorithms/REL.200.V.SFM.C66X.00.02.00.00/200.V.SFM.C66X.00.02
gpe_PATH                      ?= $(sfm_PATH)
fcw_PATH                      ?= $(sfm_PATH)
tidl_PATH                     ?= $(TI_SW_ROOT)/algorithms/REL.TIDL.01.01.03.00
tiop_PATH                     ?= $(TI_SW_ROOT)/algorithms/REL.TIOP.00.01.00.00
dmautils_PATH                 ?= $(TI_SW_ROOT)/algorithms/REL.DMAUTILS.00.08.00.02/dmautils
algframework_PATH             ?= $(TI_SW_ROOT)/algorithms/REL.ALGFRAMEWORK.02.08.00.00/algframework
VXLIB_PATH                    ?= $(TI_SW_ROOT)/algorithms/vxlib_c66x_1_1_3_0
dsplib_PATH                   ?= $(TI_SW_ROOT)/algorithms/dsplib_c66x_3_4_0_0
mmwavelib_PATH                ?= $(TI_SW_ROOT)/algorithms/mmwave_sdk_01_02_00_05
ifeq ($(AUTOSAR_APP), yes)
mcal_PATH                     ?= $(vision_sdk_PATH)/apps/src/rtos/modules/mcal
endif

OpenCL_PATH ?= $(TI_SW_ROOT)/open_compute/opencl_rtos_am57xx_01_01_10_00
OpenCV_SRC_PATH ?= $(TI_SW_ROOT)/open_compute/opencv_src/tiopencv
OpenCV_PREBUILD_PATH ?= $(TI_SW_ROOT)/open_compute/opencv/opencv-3.1.0
OpenCV_BUILD_PATH ?= build_dummy
OpenVX_PATH ?= $(TI_SW_ROOT)/open_compute/tiovx_01_03_01_00
ifeq ($(A15_TARGET_OS), Linux)
	CLOCL = $(LINUX_TARGETFS)/usr/share/ti/opencl/bin/x86/clocl
else
	CLOCL = $(TI_SW_ROOT)/open_compute/opencl_rtos_am57xx_01_01_10_00/packages/ti/clocl/linux/clocl
endif

ifeq ($(A15_TARGET_OS), Linux)
	TARGET_ROOTDIR=$(LINUX_TARGETFS)
else
ifeq ($(A15_TARGET_OS), Bios)
	TARGET_ROOTDIR=$(vision_sdk_PATH)/apps/src/rtos/opencl
endif
endif

#
# Radar related paths
#
mmwavelink_version=mmwave_dfp_01_02_00_00
radarLink_PATH=$(TI_SW_ROOT)/radar/$(mmwavelink_version)
radarMssFirmware_PATH=$(radarLink_PATH)/firmware/masterss
radarBssFirmware_PATH=$(radarLink_PATH)/firmware/radarss

#
# MSHIELD related paths
#
MSHIELD_DK_DIR       ?= $(TI_SW_ROOT)/mshield-dk_std_4_5_3
# MSHIELD 4.5.3 needs gcc-linaro-arm-linux-gnueabihf. Will remove this in later releases.
CODEGEN_PATH_MSHIELD ?= $(TI_SW_ROOT)/os_tools/linux/linaro/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf
TDA3X_SIGNING_TOOL_DIR ?= $(pdk_PATH)/packages/ti/boot/sbl_auto/security/tools/tda3xx

ifeq ($(ENABLE_UIA_PROFILING),yes)
uia_PATH=$(TI_SW_ROOT)/os_tools/uia_2_00_05_50
endif
