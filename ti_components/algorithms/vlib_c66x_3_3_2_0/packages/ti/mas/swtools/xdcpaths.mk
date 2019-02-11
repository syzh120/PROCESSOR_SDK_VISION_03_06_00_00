#  ======== xdcpaths.mk ========
#  definition of XDC paths and commands
#
#  This makefile constructs the "search path" for the XDC tools where it finds
#  numerous components and packages needed to build Codec Engine examples and
#  programs.
#
#  USER NOTE:
#  1) you must specify various <component>_INSTALL_DIRs directores below to
#     reflect your installation
#  2) you must specify compiler path and name in CGTOOLS_* variables below

# (Mandatory) Specify where various components are installed.
# What you need depends on what device(s) you're building for, what type(s) of
# programs you are building for, and whether your Codec Engine distribution
# is a "big" one that contains all the minor components in its "cetools"
# directory. The legend:
# XDC     - XDC tools (Arm and DSP)
# XDAIS   - XDAIS header files (Arm and DSP)
#
# you can omit directory specifications for the components you think you don't
# need (will be warned if you do, based on your DEVICES + PROGRAMS selection
# above).

# XDC_INSTALL_DIR       := _your_XDCTOOLS_installation_directory/xdctools_3_20_05_76
XDC_INSTALL_DIR       := /apps/ti/xdc/xdctools_3_20_05_76

XDAIS_INSTALL_DIR := /apps/ti/codec_engine/codec_engine_2_10_01/cetools

export SDOARCH_INSTALL_DIR := /tmp/sdoarch/sdoarch_standards_1_00_00/packages

export C64CODEGENTOOL := /apps/ti/cgt/c60_6_1_0

export MVARM9CGTOOL := /apps/montavista/mv_pro_4.0.1-gt/arm_v5t_le/1/montavista/pro/devkit/arm/v5t_le

export GCARMV6CGTOOL := /apps/montavista/mv_pro_5.0/arm_v6t_le/0/montavista/opt/montavista/pro/devkit/arm/v6_le

export GCARMV7ACGTOOL := /apps/codesourcery/arm-2009q1


export TI_DOXYGEN_TEMPLATES := /apps/free/doxygen/TI_Templates/10-01-2007

export DOXYGEN_INSTALL_DIR := /apps/free/doxygen/current/bin

export XDCBUILDCFG :=   /vobs/dsps_gtmas/ti/mas/swtools/config.bld

export COVPATH := /apps/cmdevtools/coverity/prevent-linux-3.8.0

export MAS_INSTALL_DIR := /vobs/dsps_gtmas


# determine which components are necessary based on DEVICES and PROGRAMS
REQUIRE_XDC   := 1
REQUIRE_XDAIS := 1


# Build the XDC path from the necessary components, verifying along the way
# that the required compoments are present
XDC_PATH :=

# XDC_INSTALL_DIR is the location of your XDCTOOLS installation.
ifeq ($(REQUIRE_XDC), 1)
    TEST_FILE := $(XDC_INSTALL_DIR)/packages/xdc/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error XDC_INSTALL_DIR is set to "$(XDC_INSTALL_DIR)", $(ERRMSG))
    endif
endif

ifeq ($(REQUIRE_XDAIS), 1)
    TEST_FILE := $(XDAIS_INSTALL_DIR)/packages/ti/xdais/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
         $(error XDAIS_INSTALL_DIR is set to "$(XDAIS_INSTALL_DIR)", $(ERRMSG))
    endif
endif

# XDC_PATH is complete. Any other components you could add as
# XDC_PATH := <your component>/packages;$(XDC_PATH)
XDC_PATH := $(SDOARCH_INSTALL_DIR)
XDC_PATH := $(XDAIS_INSTALL_DIR)/packages;$(XDC_PATH)
XDC_PATH := $(XDC_INSTALL_DIR)/packages;$(XDC_PATH)
XDC_PATH := $(DOXYGEN_INSTALL_DIR);$(XDC_PATH)
XDC_PATH := $(MAS_INSTALL_DIR);$(XDC_PATH)

export PATH := $(PATH):$(XDC_INSTALL_DIR):/apps/free/installJammer/current:/apps/free/php/5.3.3b/bin

