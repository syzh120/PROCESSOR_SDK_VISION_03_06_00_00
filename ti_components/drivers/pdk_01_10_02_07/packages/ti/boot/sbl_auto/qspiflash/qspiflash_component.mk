# File: qspiflash_component.mk
#       This file is component include make file of QSPIFLASH library.
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
ifeq ($(qspiflash_component_make_include), )

qspiflash_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
qspiflash_tda2xx_CORELIST = a15_0 ipu1_0
qspiflash_tda2px_CORELIST = a15_0 ipu1_0
qspiflash_tda2ex_CORELIST = a15_0 ipu1_0
qspiflash_tda3xx_CORELIST = ipu1_0
qspiflash_dra72x_CORELIST = a15_0 ipu1_0
qspiflash_dra75x_CORELIST = a15_0 ipu1_0
qspiflash_dra78x_CORELIST = ipu1_0
qspiflash_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda3xx-evm-radar tda2xx-evm-radar tda2px-evm-radar tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp tda2ex-eth-srv tda2xx-rvp tda2xx-cascade-radar

############################
# qspiflash package
# List of components included under qspiflash
# The components included here are built and will be part of qspiflash
############################
qspiflash_LIB_LIST = qspiflash_lib

############################
# qspiflash examples
# List of examples under qspiflash (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
qspiflash_EXAMPLE_LIST = qspi_flash_writer

#
# QSPIFLASH Modules
#

# QSPIFLASH LIB
qspiflash_lib_COMP_LIST = qspiflash_lib
qspiflash_lib_RELPATH = ti/boot/sbl_auto/qspiflash
qspiflash_lib_PATH = $(PDK_QSPIFLASH_COMP_PATH)
qspiflash_lib_LIBNAME = qspiflash_lib
qspiflash_lib_LIBPATH = $(PDK_QSPIFLASH_COMP_PATH)/lib
qspiflash_lib_MAKEFILE = -fsrc/makefile
export qspiflash_lib_MAKEFILE
export qspiflash_lib_LIBNAME
export qspiflash_lib_LIBPATH
qspiflash_lib_BOARD_DEPENDENCY = no
qspiflash_lib_CORE_DEPENDENCY = no
qspiflash_lib_SOC_DEPENDENCY = yes
export qspiflash_lib_COMP_LIST
export qspiflash_lib_BOARD_DEPENDENCY
export qspiflash_lib_CORE_DEPENDENCY
qspiflash_lib_PKG_LIST = qspiflash_lib
qspiflash_lib_INCLUDE = $(qspiflash_lib_PATH)
qspiflash_lib_SOCLIST = $(qspiflash_SOCLIST)
export qspiflash_lib_SOCLIST
qspiflash_lib_$(SOC)_CORELIST = $(qspiflash_$(SOC)_CORELIST)
export qspiflash_lib_$(SOC)_CORELIST

#
# QSPIFLASH Examples
#

# qspi_flash_writer example
qspi_flash_writer_COMP_LIST = qspi_flash_writer
qspi_flash_writer_RELPATH = ti/boot/sbl_auto/qspiflash/examples/qspi_flash_writer
qspi_flash_writer_PATH = $(PDK_QSPIFLASH_COMP_PATH)/examples/qspi_flash_writer
qspi_flash_writer_BOARD_DEPENDENCY = yes
qspi_flash_writer_CORE_DEPENDENCY = no
export qspi_flash_writer_COMP_LIST
export qspi_flash_writer_BOARD_DEPENDENCY
export qspi_flash_writer_CORE_DEPENDENCY
qspi_flash_writer_PKG_LIST = qspi_flash_writer
qspi_flash_writer_INCLUDE = $(qspi_flash_writer_PATH)
qspi_flash_writer_BOARDLIST = $(qspiflash_BOARDLIST)
export qspi_flash_writer_BOARDLIST
qspi_flash_writer_$(SOC)_CORELIST = ipu1_0
export qspi_flash_writer_$(SOC)_CORELIST

export qspiflash_LIB_LIST
export qspiflash_EXAMPLE_LIST

qspiflash_component_make_include := 1
endif
