#
# This file is the makefile for building TDA2xx SBL.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

ifeq ($(SBL_TEST_AUTO), yes)
  APP_NAME_TMP = sbl_test_auto
  APP_PATH_TMP = sbl/test_auto
else ifeq ($(SBL_TYPE), mflash)
  APP_NAME_TMP = sbl_mflash_$(BOOTMODE)
  APP_PATH_TMP = sbl/mflash_$(BOOTMODE)
else
  APP_PATH_TMP = sbl/$(BOOTMODE)/$(OPPMODE)
  APP_NAME_TMP = sbl_$(BOOTMODE)_$(OPPMODE)
endif
ifeq ($(BUILD_HS),yes)
  APP_PATH = $(APP_PATH_TMP)_hs
  APP_NAME = $(APP_NAME_TMP)_hs
else
  APP_PATH = $(APP_PATH_TMP)
  APP_NAME = $(APP_NAME_TMP)
endif

#Export APP_NAME dependent make variables as we have changed the app name
$(APP_NAME)_RELPATH = ti/boot/sbl_auto/sbl_app/src/$(SOC_SRC)
$(APP_NAME)_BOARD_DEPENDENCY = yes
$(APP_NAME)_BINPATH = $(DEST_ROOT)/$(APP_PATH)
$(APP_NAME)_OBJPATH = $(DEST_ROOT)/$(APP_PATH)/obj
export $(APP_NAME)_RELPATH
export $(APP_NAME)_BOARD_DEPENDENCY
export $(APP_NAME)_BINPATH
export $(APP_NAME)_OBJPATH

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON = csl_init csl stw_uartconsole stw_platform pm_hal_optimized pm_lib_optimized sbl_lib sbl_utils
ifeq ($(BOOTMODE),qspi)
    COMP_LIST_COMMON += qspiflash_lib
endif
ifeq ($(BOOTMODE),sd)
    COMP_LIST_COMMON += stw_fatlib stw_fatlib_edma vps_osal_baremetal
endif
ifeq ($(BOOTMODE),uart)
    ifeq ($(SBL_TYPE), mflash)
        COMP_LIST_COMMON += qspiflash_lib
    endif
endif
ifeq ($(SBL_TEST_AUTO), yes)
    COMP_LIST_COMMON += stw_boards stw_devices i2c_lld stw_examples_utility
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_a15_0 = sbl_tda2xx_main.c sbl_tda2xx_priv.c
ifeq ($(BOOTMODE),nor)
    SRCS_ASM_a15_0 += sbl_tda2xx_nor_init.asm
endif
SRCS_ASM_a15_0 += sbl_tda2xx_init.asm

ifeq ($(SBL_TEST_AUTO),yes)
    SRCDIR += ../test_auto
    SRCS_a15_0 += sbl_test_auto.c
endif

ifeq ($(SBL_TYPE), mflash)
    SRCDIR += ../mflash
    INCDIR += ../mflash
    SRCS_a15_0 = sbl_mflash_utils.c sbl_tda2xx_priv.c sbl_tda2xx_mflash_main.c sbl_mflash_uart_console.c
endif

PACKAGE_SRCS_COMMON = . ../mflash ../test_auto
PACKAGE_SRCS_COMMON += ../../makefile_all.mk ../../makefile_opps.mk ../../makefile_mshield.mk
PACKAGE_SRCS_COMMON += ../../../prebuilt_binaries

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)

#Flags for SBL opp_nom, opp_od, opp_high and opp_plus
ifeq ($(OPPMODE),)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_low)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=0
else ifeq ($(OPPMODE),opp_nom)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_od)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=2
else ifeq ($(OPPMODE),opp_high)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=3
else ifeq ($(OPPMODE),opp_plus)
    CFLAGS_LOCAL_COMMON += -DOPP_MODE=4
endif
#Flags for forcing opp mode irrespective of fd/sample revision
ifeq ($(FORCE_OPPMODE),TRUE)
    CFLAGS_LOCAL_COMMON += -DFORCE_OPP_MODE=1
else
    CFLAGS_LOCAL_COMMON += -DFORCE_OPP_MODE=0
endif
#TODO for MC build
ifeq ($(BOARD),tda2xx-mc)
    CFLAGS_LOCAL_COMMON += -DTDA2XX_MC_BUILD
endif

# SD/QSPI boot
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), sd qspi uart))
    ifeq ($(BUILD_HS),yes)
        LNKCMD_FILE = lnk_tda2xx_a15_hs.cmd
    else
        LNKCMD_FILE = lnk_tda2xx_a15.cmd
    endif
    LNKFLAGS_LOCAL_a15_0 += --entry SBL_Start
    ifeq ($(SBL_TEST_AUTO), yes)
        ifeq ($(BUILD_HS),yes)
            LNKCMD_FILE = lnk_tda2xx_a15_test_auto_hs.cmd
        else
            LNKCMD_FILE = lnk_tda2xx_a15_test_auto.cmd
        endif
    endif
endif
# NOR boot
ifeq ($(BOOTMODE),nor)
    ifeq ($(BUILD_HS),yes)
        LNKCMD_FILE = lnk_tda2xx_a15_nor_hs.cmd
    else
        LNKCMD_FILE = lnk_tda2xx_a15_nor.cmd
    endif
    LNKFLAGS_LOCAL_a15_0 += --entry nor_lowlevel_init
endif

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
