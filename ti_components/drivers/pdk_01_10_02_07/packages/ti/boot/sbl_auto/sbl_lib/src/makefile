#
# This file is the makefile for building sbl library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = sbl_lib

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
SRCDIR = src src/tda2xx
INCDIR = . src src/tda2xx
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
SRCDIR = src src/tda3xx
INCDIR = . src src/tda3xx
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = csl

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)
PACKAGE_SRCS_COMMON = . ../tools ../sbl_auto_component.mk ../docs ../makefile ../.gitignore
PACKAGE_SRCS_COMMON += ../../docs/Doxyfile ../../docs/doxygen/tilogo.gif
PACKAGE_SRCS_COMMON += ../../docs/doxygen/titagline.gif ../../docs/doxygen/tifooter.htm
PACKAGE_SRCS_COMMON += ../../docs/doxygen/tiheader.htm

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON = sbl_lib_common.c sbl_lib_board.c sbl_lib_weak.c
SRCS_tda3xx = sbl_lib_tda3xx_platform.c sbl_lib_tda3xx_prcm_dpll.c
SRCS_tda2xx = sbl_lib_tda2xx_platform.c sbl_lib_tda2xx_prcm_dpll.c sbl_lib_tda2xx_hs.c
SRCS_tda2px = sbl_lib_tda2xx_platform.c sbl_lib_tda2xx_prcm_dpll.c sbl_lib_tda2xx_hs.c
SRCS_tda2ex = sbl_lib_tda2xx_platform.c sbl_lib_tda2xx_prcm_dpll.c sbl_lib_tda2xx_hs.c
SRCS_dra78x = sbl_lib_tda3xx_platform.c sbl_lib_tda3xx_prcm_dpll.c
SRCS_dra72x = sbl_lib_tda2xx_platform.c sbl_lib_tda2xx_prcm_dpll.c sbl_lib_tda2xx_hs.c
SRCS_dra75x = sbl_lib_tda2xx_platform.c sbl_lib_tda2xx_prcm_dpll.c sbl_lib_tda2xx_hs.c
SRCS_ASM_a15_0 = sbl_lib_tda2xx_hs_support.asm

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
