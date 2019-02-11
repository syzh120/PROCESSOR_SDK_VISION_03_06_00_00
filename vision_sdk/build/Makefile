# (c) Texas Instruments

include Rules.make

##########################################
#                                        #
# Vision-SDK Top Level Build Targets     #
#                                        #
##########################################

vision_sdk:
	$(MAKE) $(MAKEAPPNAME)

##########################################
#                                        #
#	Sample Application Build             #
#                                        #
##########################################
sample_app:
ifeq ($(BUILD_DEPENDENCY_ALWAYS),yes)
	$(MAKE) depend
endif
	$(MAKE) links_fw_libs
	$(MAKE) app_alg_plugins
	$(MAKE) apps_libs
	$(MAKE) sample_apps_exe APP_PATH=$($(MAKEAPPNAME)_PATH)
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(A15_TARGET_OS), Linux)
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk header_install
	$(MAKE) sample_app_hlos
endif
endif

apps:
ifeq ($(BUILD_DEPENDENCY_ALWAYS),yes)
	$(MAKE) depend
endif
	$(MAKE) links_fw_libs
	$(MAKE) app_alg_plugins
	$(MAKE) apps_libs
ifneq ($(RADAR_ONLY),yes)
ifeq ($(ISS_INCLUDE), yes)
	$(MAKE) iss_libs
endif
	$(MAKE) video_sensor_libs
endif
	$(MAKE) apps_exe APP_PATH=$($(MAKEAPPNAME)_PATH)
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(A15_TARGET_OS), Linux)
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk header_install
	$(MAKE) apps_hlos
endif
endif
ifeq ($(A15_TARGET_OS), Qnx)
	$(MAKE) apps_hlos
endif

sample_app_hlos:
ifeq ($(A15_TARGET_OS), Linux)
	$(MAKE) links_fw_libs_hlos
	$(MAKE) sample_apps_exe_hlos APP_PATH=$($(MAKEAPPNAME)_PATH)
	$(MAKE) app_linux_install
endif

apps_hlos:
ifeq ($(A15_TARGET_OS), Linux)
ifneq ($(ROBUST_RVC_INCLUDE), yes)
	$(MAKE) links_fw_libs_hlos
	$(MAKE) apps_exe_hlos APP_PATH=$($(MAKEAPPNAME)_PATH)
ifneq ($(BUILD_INFOADAS),yes)
	$(MAKE) app_linux_install
endif
endif
endif
ifeq ($(A15_TARGET_OS), Qnx)
	$(MAKE) qnx
endif

opencx:
ifeq ($(A15_TARGET_OS), Bios)
	$(eval CACHE_BUILD_OPENCV_SRC := $(BUILD_OPENCV_SRC))
	$(eval BUILD_OPENCV_SRC := no)
	$(MAKE) vision_sdk
	$(MAKE) -C $(vision_sdk_PATH)/build/rtos/makerules -fbuild_opencv.mk _vision_sdk_opencx PROFILE=$(PROFILE) BUILD_OS=$(BUILD_OS) BUILD_OPENCV_SRC=$(CACHE_BUILD_OPENCV_SRC)
	$(MAKE) vision_sdk
else
	echo $(BUILD_OPENCV_SRC)
	$(MAKE) -C $(vision_sdk_PATH)/build/hlos/makerules/linux -fbuild_opencv.mk _vision_sdk_opencx PROFILE=$(PROFILE) BUILD_OS=$(BUILD_OS) BUILD_OPENCV_SRC=$(BUILD_OPENCV_SRC)
endif

opencx_clean:
ifeq ($(A15_TARGET_OS), Bios)
	$(MAKE) -C $(vision_sdk_PATH)/build/rtos/makerules -fbuild_opencv.mk _vision_sdk_opencx_clean PROFILE=$(PROFILE)
else
	$(MAKE) -C $(vision_sdk_PATH)/build/hlos/makerules/linux -fbuild_opencv.mk _vision_sdk_opencx_clean PROFILE=$(PROFILE)
endif

opencl:
ifeq ($(A15_TARGET_OS), Linux)
	$(MAKE) -C $(vision_sdk_PATH)/build/hlos/makerules/linux -fbuild_opencl.mk _vision_sdk_opencl BUILD_LLVM=$(BUILD_LLVM)
endif

opencl_clean:
ifeq ($(A15_TARGET_OS), Linux)
	$(MAKE) -C $(vision_sdk_PATH)/build/hlos/makerules/linux -fbuild_opencl.mk _vision_sdk_opencl_clean BUILD_LLVM=$(BUILD_LLVM)
endif

clean: pdk_clean edma3lld_clean app_alg_plugins_clean links_fw_libs_clean apps_libs_clean
ifeq ($(A15_TARGET_OS),Linux)
# Bydefault IPUMM build is not enabled from VSDK.
# Assume IPUMM libs are present in mm_PATH for the IPUMM_INCLUDE to work.
ifeq ($(IPUMM_INCLUDE),yes)
	$(MAKE) ipumm_clean
endif
endif
ifeq ($(A15_TARGET_OS), Qnx)
	$(MAKE) qnx_clean
endif

all: clean
	$(MAKE) vision_sdk

##########################################
#                                        #
# WARNING: This deletes complete         #
# directory $(DEST_ROOT)                 #
#                                        #
##########################################

allclean:
	$(RM) -rf $(DEST_ROOT)

##########################################
#                                        #
# Vision-SDK Apps Build Targets          #
#                                        #
##########################################

apps_libs:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) $(TARGET)

apps_libs_clean:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) clean

apps_libs_all: apps_libs_clean
	$(MAKE) apps_libs

iss_libs:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) iss_libs

iss_libs_clean:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) iss_libs_clean

iss_libs_all: iss_libs_clean
	$(MAKE) iss_libs

video_sensor_libs:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) video_sensor_libs

video_sensor_libs_clean:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH) video_sensor_libs_clean

video_sensor_libs_all: video_sensor_libs_clean
	$(MAKE) video_sensor_libs

##########################################
#                                        #
# Vision-SDK Application Build Targets   #
#                                        #
##########################################
sample_apps_exe:
	$(MAKE) -fMAKEFILE.MK -C $($(MAKEAPPNAME)_PATH) apps

apps_exe:
	$(MAKE) -fMAKEFILE.MK -C $($(MAKEAPPNAME)_PATH) apps

sample_apps_exe_hlos:
ifeq ($(A15_TARGET_OS),Linux)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos apps
endif

apps_exe_hlos:
ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
ifeq ($(BUILD_INFOADAS),yes)
	$(MAKE) -fMAKEFILE_infoadas.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos
else
	$(MAKE) -fMAKEFILE_adas.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos
endif
ifeq ($(BUILD_ADAM_CAR),yes)
	$(MAKE) -fMAKEFILE_adam_car.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos
endif
endif

#####################################################
#                                                   #
# Vision-SDK Alg-plugin apps Build Targets          #
#                                                   #
#####################################################

app_alg_plugins:
ifeq ($(BUILD_ALGORITHMS),yes)
	$(MAKE) algorithmslib
endif
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins $(TARGET)

app_alg_plugins_clean:
	-s $(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/rtos/alg_plugins clean

app_alg_plugins_all: app_alg_plugins_clean
	$(MAKE) app_alg_plugins

######################################
#                                    #
# Vision-SDK Library Build Targets   #
#                                    #
######################################

links_fw_libs:
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/rtos libs

links_fw_libs_clean:
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/rtos clean

links_fw_libs_all: links_fw_libs_clean
	$(MAKE) links_fw_libs

links_fw_depend:
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/rtos depend

links_fw_libs_hlos:
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Linux)
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/hlos libs
endif
endif

links_fw_libs_hlos_clean:
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Linux)
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/hlos clean
endif
endif

links_fw_libs_hlos_all: links_fw_libs_hlos_clean
	$(MAKE) links_fw_libs_hlos

##################################################
#                                                #
# Vision-SDK Multi-core Image Gen Targets        #
#                                                #
##################################################
appimage:
	$(MAKE) -fbuild_multi_core_image_gen.mk -C$(vision_sdk_PATH)/build/rtos/makerules

#################################
#                               #
# Config targets            #
#                               #
#################################
makeconfig:
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/configs -f build_makeconfig.mk all

showconfig:
	$(MAKE) -C $($(MAKEAPPNAME)_PATH)/configs -f build_makeconfig.mk showconfig

#######################################
#                                     #
# Target to touch files required to   #
# recompile to change the number of   #
# proccesor's to build                #
#                                     #
#######################################
depend:
	$(MAKE) -s makeconfig
	$(MAKE) edma3lld
	$(MAKE) pdk
	$(MAKE) links_fw_depend
ifeq ($(IPUMM_INCLUDE), yes)
	$(MAKE) ipumm
endif
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_common/system/system_common.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_common/system/system_ipc_bios_ipc.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_common/algorithm/algorithmLink_cfg.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/system/system_ipu1_1.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/system/system_ipu1_0.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_ipu/system/system_ipu2.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/links_a15/system/system_a15.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/ndk/ndk_nsp_hooks.c
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2xx-rvp))
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/cfg/IPC_common.cfg
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/eve1/src/tlb_config_eve1.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/eve2/src/tlb_config_eve2.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/eve3/src/tlb_config_eve3.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/eve4/src/tlb_config_eve4.c
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2px-evm))
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2px/cfg/IPC_common.cfg
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2px/eve1/src/tlb_config_eve1.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2px/eve2/src/tlb_config_eve2.c
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda3xx-evm tda3xx-rvp))
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda3xx/cfg/IPC_common.cfg
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda3xx/eve1/src/tlb_config_eve1.c
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2ex-evm))
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2ex/cfg/IPC_common.cfg
endif
ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
ifeq ($(BUILD_ADAM_CAR),yes)
	$(TOUCH) $(vision_sdk_PATH)/apps/src/rtos/adam_car/src/system/system_adam_car_common.c
endif
#	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/ipu1_0/src/main_ipu1_0.c
#	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2ex/ipu1_0/src/main_ipu1_0.c
#	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2xx/ipu2/src/main_ipu2.c
#	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/bios_app_common/tda2ex/ipu2/src/main_ipu2.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_eveloader.c
endif

depend_ndk_fatfs: depend
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/network_api.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/network_tfdtp_api.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/file_api.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/file_api_dma.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/dma_cfg/utils_dma_cfg_sys_edma.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/tda2xx/utils_prcm.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/tda2px/utils_prcm.c
	$(TOUCH) $(vision_sdk_PATH)/apps/src/rtos/usecases/common/chains_common.c

depend_pm:
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_prf.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_idle_m4.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_idle_arp32.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_idle_a15.c
	$(TOUCH) $(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/utils_idle_c66x.c

#########################
#                       #
# PDK Build Targets     #
#                       #
#########################
pdk:
	$(MAKE) -C $(vision_sdk_PATH)/build/rtos/makerules -fbuild_pdk.mk pdk

pdk_clean:
	$(MAKE) -C $(vision_sdk_PATH)/build/rtos/makerules -fbuild_pdk.mk pdk_clean

pdk_all: pdk_clean
	$(MAKE) pdk

#################################
#                               #
# EDMA3LLD Build Targets        #
#                               #
#################################

edma3lld:
	$(MAKE) -C ./rtos/makerules -fbuild_edma3lld.mk edma3lld

edma3lld_clean:
	$(MAKE) -C ./rtos/makerules -fbuild_edma3lld.mk edma3lld_clean

edma3lld_all: edma3lld_clean
	$(MAKE) edma3lld

#########################
#                       #
# IPC Build Targets     #
#                       #
#########################

ipc:
	$(MAKE) -C ./rtos/makerules -fbuild_ipc.mk ipc

ipc_clean:
	$(MAKE) -C ./rtos/makerules -fbuild_ipc.mk ipc_clean

ipc_all: ipc_clean
	$(MAKE) ipc

#########################
#                       #
# IPUMM Build Targets   #
#                       #
#########################

ipumm:
	$(MAKE) -C ./rtos/makerules -fbuild_ipumm.mk ipumm

ipumm_clean:
	$(MAKE) -C ./rtos/makerules -fbuild_ipumm.mk ipumm_clean

ipumm_all: ipumm_clean
	$(MAKE) ipumm

#################################
#                               #
# SBL  build Targets            #
#                               #
#################################

sbl:
	$(MAKE) -C ./rtos/makerules -fbuild_pdk.mk sbl

sbl_clean:
	$(MAKE) -C ./rtos/makerules -fbuild_pdk.mk sbl_clean

sbl_all: sbl_clean
	$(MAKE) sbl

#################################
#                               #
# Usecase auto-generate targets #
#                               #
#################################
use_case_gen:
	$(MAKE) -C ./build/rtos/scripts -f use_case_gen.mk


#######################################
#                                     #
# Linux Kernel and U-boot build       #
# Vision SDK linux side app build     #
#                                     #
# NOTE: Should be used only when      #
#       A15_TARGET_OS is Linux        #
#                                     #
#######################################

uboot:
	$(MAKE) -C ./hlos/makerules/linux -f build_uboot.mk uboot

uboot_all:
	$(MAKE) -C ./hlos/makerules/linux -f build_uboot.mk uboot_all

uboot_clean:
	$(MAKE) -C ./hlos/makerules/linux -f build_uboot.mk uboot_clean

kernel:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk kernel

dtb:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk dtb

kernel_all:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk kernel_all

kernel_menuconfig:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk kernel_menuconfig

kernel_clean:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk kernel_clean

sgx:
	$(MAKE) -C ./hlos/makerules/linux -f build_sgx.mk sgx

sgx_all:
	$(MAKE) -C ./hlos/makerules/linux -f build_sgx.mk sgx_all

sgx_clean:
	$(MAKE) -C ./hlos/makerules/linux -f build_sgx.mk sgx_clean

linux: uboot kernel sgx

linux_clean: uboot_clean sgx_clean kernel_clean

linux_all: kernel_all uboot_all sgx_all

linux_install:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk kernel_install
	$(MAKE) -C ./hlos/makerules/linux -f build_sgx.mk sgx_install
	$(MAKE) -C ./hlos/makerules/linux -f build_uboot.mk uboot_install

app_linux_install:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk linux_app_install

autosar_install:
	$(MAKE) -C ./hlos/makerules/linux -f build_kernel.mk autosar_app_install

#######################################
#                                     #
# Vision SDK firmware QNX install     #
#                                     #
# NOTE: Should be used only when      #
#       A15_TARGET_OS is Qnx          #
#                                     #
#######################################

qnx_install:
	$(MAKE) -f install_qnx.mk -C$(vision_sdk_PATH)/build/hlos/makerules/qnx firmware_install

qnx_install_clean:
	$(MAKE) -f install_qnx.mk -C$(vision_sdk_PATH)/build/hlos/makerules/qnx firmware_clean

#######################################
#                                     #
# QNX build                           #
# Vision SDK Qnx side app build       #
#                                     #
# NOTE: Should be used only when      #
#       A15_TARGET_OS is Qnx          #
#                                     #
#######################################

qnx:
	-rm -rf ${QCONF_OVERRIDE}
	echo "INSTALL_ROOT_nto := ${QNX_TARGETFS}" >> ${QCONF_OVERRIDE}
	echo "USE_INSTALL_ROOT = 1" >> ${QCONF_OVERRIDE}
	$(MAKE) qnx_install
	$(MAKE) -f install_qnx.mk -C$(vision_sdk_PATH)/build/hlos/makerules/qnx header_install
	$(MAKE) -f build_qnx.mk -C$(vision_sdk_PATH)/build/hlos/makerules/qnx/vision_sdk CPULIST=arm VARIANTLIST=v7 install

qnx_clean:
	$(MAKE) qnx_install_clean
	$(MAKE) -f build_qnx.mk -C$(vision_sdk_PATH)/build/hlos/makerules/qnx/vision_sdk CPULIST=arm VARIANTLIST=v7 clean

qnx_all: qnx_clean
	$(MAKE) qnx

#######################################
#                                     #
# ADAM_CAR_LINUX  					  #
# adam_car development build          #
#                                     #
#######################################

adam_car_linux:
	$(MAKE) -fMAKEFILE_adam_car.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos
	$(MAKE) app_linux_install

adam_car_linux_clean:
	$(MAKE) -fMAKEFILE_adam_car.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos clean

adam_car_linux_all: adam_car_linux_clean adam_car_linux

## TI internal make targets. NOT to be used by customers ##

#######################################
#                                     #
# Algorithms                          #
#                                     #
#######################################

algorithmslib:
	$(MAKE) -C$(vision_sdk_PATH)/algorithms -fMAKEFILE.MK algorithmslib

algorithmslib_clean:
	$(MAKE) -C$(vision_sdk_PATH)/algorithms -fMAKEFILE.MK algorithmslib_clean

algorithmslib_all: algorithmslib_clean
	$(MAKE) algorithmslib

##########################################
#                                        #
# Vision-SDK test suite Build Targets    #
#                                        #
# NOTE: Testsuite software NOT included  #
#       in release package		 #
##########################################

testsuite_app:
ifeq ($(BUILD_DEPENDENCY_ALWAYS),yes)
	$(MAKE) depend
endif
	$(MAKE) app_alg_plugins
	$(MAKE) links_fw_libs
	$(MAKE) testsuite_app_libs
ifneq ($(RADAR_ONLY),yes)
ifeq ($(ISS_INCLUDE), yes)
	$(MAKE) iss_libs
endif
	$(MAKE) video_sensor_libs
endif
	$(MAKE) testsuite_app_exe APP_PATH=$($(MAKEAPPNAME)_PATH)

testsuite_app_clean: pdk_clean edma3lld_clean app_alg_plugins_clean links_fw_libs_clean testsuite_app_libs_clean

testsuite_app_all: testsuite_app_clean
	$(MAKE) testsuite_app

testsuite_app_libs:
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/testsuite $(TARGET)

testsuite_app_libs_clean:
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/testsuite clean

testsuite_app_exe:
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/testsuite apps

##############################################
#                                            #
# Vision-SDK Ethernet Based Flashing         #
#                                            #
##############################################
eth_flash_appimage:
	$(MAKE) -fbuild_ethflash.mk -C$(vision_sdk_PATH)/build/rtos/makerules eth_flash_appimage

eth_flash_sbl:
	$(MAKE) -fbuild_ethflash.mk -C$(vision_sdk_PATH)/build/rtos/makerules eth_flash_sbl

eth_reset:
	$(MAKE) -fbuild_ethflash.mk -C$(vision_sdk_PATH)/build/rtos/makerules eth_reset

eth_writesd_sbl:
	$(MAKE) -fbuild_ethflash.mk -C$(vision_sdk_PATH)/build/rtos/makerules eth_writesd_sbl

eth_writesd_appimage:
	$(MAKE) -fbuild_ethflash.mk -C$(vision_sdk_PATH)/build/rtos/makerules eth_writesd_appimage

##############################################
#                                            #
# Vision-SDK Build All Configs               #
#                                            #
##############################################
build_config:
	$(MAKE) -s -j showconfig
	$(MAKE) -s -j depend
	$(MAKE) -s -j
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) -s -j appimage
endif

##############################################
#                                            #
# Help Target                                #
##############################################

help:
	$(ECHO) \#
	$(ECHO) \# Vision SDK Build System
	$(ECHO) \#
	$(ECHO) \# Basic targets,
	$(ECHO) '# gmake -s -j showconfig  // Show current build config'
	$(ECHO) '# gmake -s -j depend      // Generate config, Build PDK, EDMA3LLD, touch dependant files'
	$(ECHO) '# gmake -s -j             // Incremental build, build vision sdk lib, alg_plugins, apps, binaries'
	$(ECHO) '# gmake -s -j appimage    // Generate bootable application image'
	$(ECHO) '# gmake -s -j sbl         // Generate SBL including SBL firmware for all boot modes'
	$(ECHO) \#
	$(ECHO) \# Advanced targets,
	$(ECHO) '# gmake -s -j makeconfig             // Generate config related files'
	$(ECHO) '# gmake -s -j pdk                    // Build PDK'
	$(ECHO) '# gmake -s -j edma3lld               // Build EDMA3LLD'
	$(ECHO) '# gmake -s -j algorithmslib          // Build Algorithm libraries'
	$(ECHO) '# gmake -s -j links_fw_libs          // Build Vision SDK framework library'
	$(ECHO) '# gmake -s -j vision_sdk_alg_plugins // Build Vision SDK algo plugins'
	$(ECHO) '# gmake -s -j apps                   // Build Vision SDK BIOS applications binaries'
	$(ECHO) \#
	$(ECHO) \# Linux related targets,
	$(ECHO) '# gmake -s -j linux             // Build linux kernel, uboot, sgx drivers'
	$(ECHO) '# gmake -s -j linux_install     // Install kernel, uboot, sgx files into filesystem'
	$(ECHO) '# gmake -s -j vision_sdk_linux  // Build Vision SDK linux side library and binaries'
	$(ECHO) '# gmake -s -j uboot             // Build uboot'
	$(ECHO) '# gmake -s -j kernel            // Build kernel'
	$(ECHO) '# gmake -s -j sgx               // Build sgx drivers'
	$(ECHO) \#
	$(ECHO) \# Qnx related targets,
	$(ECHO) '# gmake -s -j vision_sdk_qnx  // Build Vision SDK qnx side library and binaries'
	$(ECHO) \#

.PHONY : allclean vision_sdk clean all apps vision_sdk_alg_plugins links_fw_libs depend pdk edma3lld sbl_sd sbl_nor sbl_qspi testsuite_app algorithmslib uboot uboot_all uboot_clean kernel kernel_all kernel_menuconfig kernel_clean sgx sgx_clean sgx_all sample_app

