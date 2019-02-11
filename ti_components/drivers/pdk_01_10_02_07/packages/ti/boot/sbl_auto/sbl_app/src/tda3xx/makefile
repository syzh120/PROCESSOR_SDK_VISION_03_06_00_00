#
# This file is the makefile for building TDA3xx SBL.
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
COMP_LIST_COMMON = csl stw_uartconsole stw_platform pm_hal_optimized sbl_lib sbl_utils i2c_lld
ifeq ($(BOOTMODE),qspi)
    COMP_LIST_COMMON += qspiflash_lib
endif
ifeq ($(BOOTMODE),qspi_sd)
    COMP_LIST_COMMON += qspiflash_lib stw_fatlib stw_fatlib_edma vps_osal_baremetal
endif
ifeq ($(BUILD_HS),yes)
    COMP_LIST_COMMON += security
endif
ifeq ($(BOOTMODE),uart)
    ifeq ($(SBL_TYPE), mflash)
        COMP_LIST_COMMON += qspiflash_lib
    endif
endif
ifeq ($(SBL_TEST_AUTO), yes)
    COMP_LIST_COMMON += stw_boards stw_devices stw_examples_utility
endif

# Common source files and CFLAGS across all platforms and cores
SRCS_ipu1_0 = sbl_tda3xx_priv.c sbl_tda3xx_main.c
SRCS_ASM_ipu1_0 = sbl_m4_init.asm
ifeq ($(BOOTMODE),nor)
    SRCS_ASM_ipu1_0 += sbl_m4_init_nor.asm
endif
ifeq ($(SBL_TEST_AUTO),yes)
    SRCDIR += ../test_auto
    SRCS_ipu1_0 += sbl_test_auto.c
endif
ifeq ($(SBL_TYPE), mflash)
    SRCDIR += ../mflash
    INCDIR += ../mflash
    SRCS_ipu1_0 = sbl_mflash_utils.c sbl_tda3xx_priv.c sbl_tda3xx_mflash_main.c sbl_mflash_uart_console.c
endif

PACKAGE_SRCS_COMMON = . ../mflash ../test_auto
PACKAGE_SRCS_COMMON += ../../makefile_all.mk ../../makefile_opps.mk
PACKAGE_SRCS_COMMON += ../../../prebuilt_binaries

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)

#Flags for SBL opp_nom, opp_od and opp_high
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
endif

# QSPI_SD/QSPI/UART boot
ifeq ($(BOOTMODE),$(filter $(BOOTMODE), qspi_sd qspi uart))
    ifeq ($(SBL_TEST_AUTO), yes)
        LNKCMD_FILE = lnk_tda3xx_m4_test_auto.cmd
    else
        LNKCMD_FILE = lnk_tda3xx_m4.cmd
    endif
    LNKFLAGS_LOCAL_ipu1_0 += -e sbl_start
endif
# NOR boot
ifeq ($(BOOTMODE),nor)
    LNKCMD_FILE = lnk_tda3xx_m4_nor.cmd
    LNKFLAGS_LOCAL_ipu1_0 += -e sbl_nor_start
endif
LNKFLAGS_LOCAL_ipu1_0 += --diag_suppress=10063 --retain SblIPU1Core1Init --dynamic

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
