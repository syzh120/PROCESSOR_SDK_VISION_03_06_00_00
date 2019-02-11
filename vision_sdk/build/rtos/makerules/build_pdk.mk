# File name: build_pdk.mk
#            This file builds the PDK libs.

PDK_BUILD_OPTIONS = MAKERULEDIR=$(pdk_PATH)/packages/ti/build/makerules PDK_INSTALL_PATH=$(pdk_PATH)/packages
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_GCC=$(CODEGEN_PATH_A15) TOOLCHAIN_PATH_A15=$(CODEGEN_PATH_A15)
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_M4=$(CODEGEN_PATH_M4)
PDK_BUILD_OPTIONS += C6X_GEN_INSTALL_PATH=$(CODEGEN_PATH_DSP)
PDK_BUILD_OPTIONS += TOOLCHAIN_PATH_EVE=$(CODEGEN_PATH_EVE)
PDK_BUILD_OPTIONS += BIOS_INSTALL_PATH=$(bios_PATH) XDC_INSTALL_PATH=$(xdc_PATH)
PDK_BUILD_OPTIONS += EDMA3LLD_BIOS6_INSTALLDIR=$(edma_PATH)
PDK_BUILD_OPTIONS += RADARLINK_INSTALL_PATH=$(radarLink_PATH)
PDK_BUILD_OPTIONS += MSHIELD_DK_DIR=$(MSHIELD_DK_DIR)
PDK_BUILD_OPTIONS += utils_PATH=$(UTILSPATH)
PDK_BUILD_OPTIONS += INCLUDE_DUMMY_OSAL=no
PDK_BUILD_OPTIONS += PACKAGE_VIP=yes
PDK_BUILD_OPTIONS += INCLUDE_SYSBIOS=yes
PDK_BUILD_OPTIONS += VPS_RADAR_INCLUDE=yes

ifeq ($(VPE_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_VPE=yes
else
PDK_BUILD_OPTIONS += PACKAGE_VPE=no
endif

ifeq ($(CAL_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_CAL=yes
else
PDK_BUILD_OPTIONS += PACKAGE_CAL=no
endif

ifeq ($(ISS_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_ISS=yes
else
PDK_BUILD_OPTIONS += PACKAGE_ISS=no
endif

ifeq ($(DSS_INCLUDE),yes)
PDK_BUILD_OPTIONS += PACKAGE_DSS=yes
else
PDK_BUILD_OPTIONS += PACKAGE_DSS=no
endif

ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
ifeq ($(ROBUST_RVC_INCLUDE),yes)
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C2=yes
else
ifeq ($(PLATFORM), tda2xx-evm)
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C0=yes VPS_DISABLE_I2C2=yes VPS_DISABLE_I2C3=yes VPS_DISABLE_I2C4=yes
else 
ifeq ($(PLATFORM), tda2xx-rvp)
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C0=yes VPS_DISABLE_I2C2=yes VPS_USE_LINUX_INTC_NUMBERS=yes
else
PDK_BUILD_OPTIONS += VPS_DISABLE_I2C0=yes VPS_DISABLE_I2C2=yes VPS_DISABLE_I2C3=yes VPS_DISABLE_I2C1=yes
endif
endif
endif
endif

pdk:
ifeq ($(PROC_IPU_BUILD_INCLUDE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0 BUILD_PROFILE=$(PROFILE_ipu1_0)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_1 BUILD_PROFILE=$(PROFILE_ipu1_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu2_0 BUILD_PROFILE=$(PROFILE_ipu2)
endif
ifeq ($(PROC_DSP_BUILD_INCLUDE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66x BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_1 BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_2 BUILD_PROFILE=$(PROFILE_c66xdsp_2)
endif
ifeq ($(PROC_EVE_BUILD_INCLUDE),yes)
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda2xx-rvp tda3xx-evm tda3xx-rvp))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_1 BUILD_PROFILE=$(PROFILE_arp32_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_2 BUILD_PROFILE=$(PROFILE_arp32_2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_3 BUILD_PROFILE=$(PROFILE_arp32_3)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_4 BUILD_PROFILE=$(PROFILE_arp32_4)
endif
endif
ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(PROC_A15_0_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=a15_0 BUILD_PROFILE=$(PROFILE_a15_0)
endif
endif
endif

pdk_clean:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0 BUILD_PROFILE=$(PROFILE_$(IPU_PRIMARY_CORE))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_1 BUILD_PROFILE=$(PROFILE_ipu1_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu2_0 BUILD_PROFILE=$(PROFILE_ipu2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66x BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_1 BUILD_PROFILE=$(PROFILE_c66xdsp_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=c66xdsp_2 BUILD_PROFILE=$(PROFILE_c66xdsp_2)
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda2xx-rvp tda3xx-evm tda3xx-rvp))
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_1 BUILD_PROFILE=$(PROFILE_arp32_1)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_2 BUILD_PROFILE=$(PROFILE_arp32_2)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_3 BUILD_PROFILE=$(PROFILE_arp32_3)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=arp32_4 BUILD_PROFILE=$(PROFILE_arp32_4)
endif
ifeq ($(PROC_A15_0_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ pdk_libs_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=a15_0 BUILD_PROFILE=$(PROFILE_a15_0)
endif
endif

# SBL options,
# -------------------
# EMIFMODE         = SINGLE_EMIF_512MB (default) or
#                    DUAL_EMIF_1GB_512MB or
#                    DUAL_EMIF_2X512MB or
#                    SINGLE_EMIF_256MB
# NOTE:
# DUAL_EMIF_1GB_512MB : uses EMIF2 - 1GB and EMIF1 512MB, BUT in non-interleaved mode
#                       Vision SDK uses only 1GB hence effectivly this is single EMIF
#                       non-interleaved mode for Vision SDK
#                       0x8000_0000 - 0xBFFF_FFFF is mapped to EMIF2
#                       0xC000_0000 - 0xDFFF_FFFF is mapped to EMIF1
# DUAL_EMIF_2X512MB   : uses EMIF1 and EMIF 512MB each in interleaved mode
#                       0x8000_0000 - 0x9FFF_FFFF is interleaved between EMIF1 and EMIF2
# SINGLE_EMIF_256MB   : uses EMIF1 with 256MB
#                       0x8000_0000 - 0x8FFF_FFFF is mapped to EMIF1
# SINGLE_EMIF_512MB   : uses EMIF1 with 512MB
#                       0x8000_0000 - 0x9FFF_FFFF is mapped to EMIF1
#
# SINGLE_EMIF_1GB     : uses with 1GB
#                       0x8000_0000 - 0xBFFF_FFFF is mapped

#

PDK_SBL_BUILD_OPTIONS = $(PDK_BUILD_OPTIONS)
ifneq ($(ECC_FFI_INCLUDE),yes)
PDK_SBL_BUILD_OPTIONS+= SBL_CONFIG=disable_safety
endif

ifeq ($(FAST_BOOT_INCLUDE), yes)
PDK_SBL_BUILD_OPTIONS+= SBL_CONFIG=disable_safety SBL_BUILD_MODE=prod SBL_OPT_MODE=high
endif

ifeq ($(HS_DEVICE),yes)
PDK_SBL_BUILD_OPTIONS += BUILD_HS=yes
PDK_SBL_BUILD_OPTIONS += MSHIELD_DK_DIR=$(MSHIELD_DK_DIR)
endif

sbl:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE) BUILD_PROFILE=$(PROFILE_$(PDK_SBL_CORE))
ifeq ($(HS_DEVICE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/boot/sbl_auto/sbl_app -fmakefile_mshield.mk $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE) 2>/dev/null >/dev/null
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
endif
#Build the tools required for flashing as well - only IPU build supported
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ qspi_flash_writer $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ nor_flash_writer  $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0

sbl_clean:
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps_clean $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
ifeq ($(HS_DEVICE),yes)
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ sbl_all_opps_clean $(PDK_SBL_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=$(PDK_SBL_CORE)
endif
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ qspi_flash_writer_clean $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
	$(MAKE) -C $(pdk_PATH)/packages/ti/build/ nor_flash_writer_clean  $(PDK_BUILD_OPTIONS) BOARD=$(PDK_BOARD) CORE=ipu1_0
