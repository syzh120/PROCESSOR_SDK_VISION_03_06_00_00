# File: bsp_mcspi_component.mk
#       This file is component include make file of VPS library.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_BOARD_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#
ifeq ($(bsp_mcspi_component_make_include), )

bsp_mcspi_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
bsp_mcspi_default_tda2xx_CORELIST = ipu1_0
bsp_mcspi_default_tda2px_CORELIST = ipu1_0
bsp_mcspi_default_tda2ex_CORELIST = ipu1_0
bsp_mcspi_default_tda3xx_CORELIST = ipu1_0

############################
# bsp_mcspi package
# List of components included under bsp_mcspi
# The components included here are built and will be part of bsp_mcspi lib
############################
bsp_mcspi_LIB_LIST = bsp_mcspi

############################
# bsp_mcspi examples
# List of examples under bsp_mcspi (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
bsp_mcspi_EXAMPLE_LIST =

#
# BSP MCSPI Modules
#

# BSP MCSPI LIB
bsp_mcspi_COMP_LIST = bsp_mcspi
bsp_mcspi_RELPATH = ti/drv/bsp_lld/mcspi
bsp_mcspi_PATH = $(PDK_BSP_MCSPI_COMP_PATH)
bsp_mcspi_LIBNAME = bsp_mcspi
bsp_mcspi_LIBPATH = $(PDK_BSP_MCSPI_COMP_PATH)/lib
bsp_mcspi_MAKEFILE = -fsrc/makefile
export bsp_mcspi_MAKEFILE
export bsp_mcspi_LIBNAME
export bsp_mcspi_LIBPATH
bsp_mcspi_BOARD_DEPENDENCY = no
bsp_mcspi_CORE_DEPENDENCY = no
export bsp_mcspi_COMP_LIST
export bsp_mcspi_BOARD_DEPENDENCY
export bsp_mcspi_CORE_DEPENDENCY
bsp_mcspi_PKG_LIST = bsp_mcspi
bsp_mcspi_INCLUDE = $(bsp_mcspi_PATH)
bsp_mcspi_SOCLIST = $(bsp_mcspi_default_SOCLIST)
export bsp_mcspi_SOCLIST
bsp_mcspi_$(SOC)_CORELIST = $(bsp_mcspi_default_$(SOC)_CORELIST)
export bsp_mcspi_$(SOC)_CORELIST

# McSPI Loopback Example
bsp_examples_mcspi_loopback_COMP_LIST = bsp_examples_mcspi_loopback
bsp_examples_mcspi_loopback_RELPATH = ti/drv/bsp_lld/mcspi/examples/mcspi_loopback
bsp_examples_mcspi_loopback_PATH = $(PDK_BSP_MCSPI_COMP_PATH)/examples/mcspi_loopback
bsp_examples_mcspi_loopback_BOARD_DEPENDENCY = yes
bsp_examples_mcspi_loopback_CORE_DEPENDENCY = no
bsp_examples_mcspi_loopback_XDC_CONFIGURO = yes
export bsp_examples_mcspi_loopback_COMP_LIST
export bsp_examples_mcspi_loopback_BOARD_DEPENDENCY
export bsp_examples_mcspi_loopback_CORE_DEPENDENCY
export bsp_examples_mcspi_loopback_XDC_CONFIGURO
bsp_examples_mcspi_loopback_PKG_LIST = bsp_examples_mcspi_loopback
bsp_examples_mcspi_loopback_INCLUDE = $(bsp_examples_mcspi_loopback_PATH)
bsp_examples_mcspi_loopback_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export bsp_examples_mcspi_loopback_BOARDLIST
bsp_examples_mcspi_loopback_$(SOC)_CORELIST = ipu1_0
export bsp_examples_mcspi_loopback_$(SOC)_CORELIST
bsp_mcspi_EXAMPLE_LIST += bsp_examples_mcspi_loopback
bsp_examples_mcspi_loopback_SBL_APPIMAGEGEN = yes
export bsp_examples_mcspi_loopback_SBL_APPIMAGEGEN

# McSPI SPI1 to SPI2 Example
bsp_examples_mcspi_spi1tospi2_COMP_LIST = bsp_examples_mcspi_spi1tospi2
bsp_examples_mcspi_spi1tospi2_RELPATH = ti/drv/bsp_lld/mcspi/examples/mcspi_spi1tospi2
bsp_examples_mcspi_spi1tospi2_PATH = $(PDK_BSP_MCSPI_COMP_PATH)/examples/mcspi_spi1tospi2
bsp_examples_mcspi_spi1tospi2_BOARD_DEPENDENCY = yes
bsp_examples_mcspi_spi1tospi2_CORE_DEPENDENCY = no
bsp_examples_mcspi_spi1tospi2_XDC_CONFIGURO = yes
export bsp_examples_mcspi_spi1tospi2_COMP_LIST
export bsp_examples_mcspi_spi1tospi2_BOARD_DEPENDENCY
export bsp_examples_mcspi_spi1tospi2_CORE_DEPENDENCY
export bsp_examples_mcspi_spi1tospi2_XDC_CONFIGURO
bsp_examples_mcspi_spi1tospi2_PKG_LIST = bsp_examples_mcspi_spi1tospi2
bsp_examples_mcspi_spi1tospi2_INCLUDE = $(bsp_examples_mcspi_spi1tospi2_PATH)
bsp_examples_mcspi_spi1tospi2_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export bsp_examples_mcspi_spi1tospi2_BOARDLIST
bsp_examples_mcspi_spi1tospi2_$(SOC)_CORELIST = ipu1_0
export bsp_examples_mcspi_spi1tospi2_$(SOC)_CORELIST
bsp_mcspi_EXAMPLE_LIST += bsp_examples_mcspi_spi1tospi2
bsp_examples_mcspi_spi1tospi2_SBL_APPIMAGEGEN = yes
export bsp_examples_mcspi_spi1tospi2_SBL_APPIMAGEGEN

# McSPI open/close Example
bsp_examples_mcspi_openClose_COMP_LIST = bsp_examples_mcspi_openClose
bsp_examples_mcspi_openClose_RELPATH = ti/drv/bsp_lld/mcspi/examples/mcspi_openClose
bsp_examples_mcspi_openClose_PATH = $(PDK_BSP_MCSPI_COMP_PATH)/examples/mcspi_openClose
bsp_examples_mcspi_openClose_BOARD_DEPENDENCY = yes
bsp_examples_mcspi_openClose_CORE_DEPENDENCY = no
bsp_examples_mcspi_openClose_XDC_CONFIGURO = yes
export bsp_examples_mcspi_openClose_COMP_LIST
export bsp_examples_mcspi_openClose_BOARD_DEPENDENCY
export bsp_examples_mcspi_openClose_CORE_DEPENDENCY
export bsp_examples_mcspi_openClose_XDC_CONFIGURO
bsp_examples_mcspi_openClose_PKG_LIST = bsp_examples_mcspi_openClose
bsp_examples_mcspi_openClose_INCLUDE = $(bsp_examples_mcspi_openClose_PATH)
bsp_examples_mcspi_openClose_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export bsp_examples_mcspi_openClose_BOARDLIST
bsp_examples_mcspi_openClose_$(SOC)_CORELIST = ipu1_0
export bsp_examples_mcspi_openClose_$(SOC)_CORELIST
bsp_mcspi_EXAMPLE_LIST += bsp_examples_mcspi_openClose

export bsp_mcspi_LIB_LIST
export bsp_mcspi_EXAMPLE_LIST

bsp_mcspi_component_make_include := 1
endif
