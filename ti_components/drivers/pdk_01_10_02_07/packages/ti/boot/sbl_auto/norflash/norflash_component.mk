# File: norflash_component.mk
#       This file is component include make file of NORFLASH library.
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
ifeq ($(norflash_component_make_include), )

norflash_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
norflash_tda2xx_CORELIST = a15_0 ipu1_0
norflash_tda2px_CORELIST = a15_0 ipu1_0
norflash_tda2ex_CORELIST = a15_0 ipu1_0
norflash_tda3xx_CORELIST = ipu1_0
norflash_dra72x_CORELIST = a15_0 ipu1_0
norflash_dra75x_CORELIST = a15_0 ipu1_0
norflash_dra78x_CORELIST = ipu1_0
norflash_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm evmDRA72x evmDRA75x evmDRA78x tda3xx-evm-radar tda2xx-evm-radar tda2px-evm-radar tda3xx-ar12-booster tda3xx-ar12-alps tda3xx-ar12-rvp tda2ex-eth-srv tda2xx-rvp tda2xx-cascade-radar

############################
# norflash package
# List of components included under norflash
# The components included here are built and will be part of norflash
############################
norflash_LIB_LIST = norflash_lib

############################
# norflash examples
# List of examples under norflash (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
norflash_EXAMPLE_LIST = nor_flash_writer

#
# NORFLASH Modules
#

# NORFLASH LIB
norflash_lib_COMP_LIST = norflash_lib
norflash_lib_RELPATH = ti/boot/sbl_auto/norflash
norflash_lib_PATH = $(PDK_NORFLASH_COMP_PATH)
norflash_lib_LIBNAME = norflash_lib
norflash_lib_LIBPATH = $(PDK_NORFLASH_COMP_PATH)/lib
norflash_lib_MAKEFILE = -fsrc/makefile
export norflash_lib_MAKEFILE
export norflash_lib_LIBNAME
export norflash_lib_LIBPATH
norflash_lib_BOARD_DEPENDENCY = no
norflash_lib_CORE_DEPENDENCY = no
export norflash_lib_COMP_LIST
export norflash_lib_BOARD_DEPENDENCY
export norflash_lib_CORE_DEPENDENCY
norflash_lib_PKG_LIST = norflash_lib
norflash_lib_INCLUDE = $(norflash_lib_PATH)
norflash_lib_SOCLIST = $(norflash_SOCLIST)
export norflash_lib_SOCLIST
norflash_lib_$(SOC)_CORELIST = $(norflash_$(SOC)_CORELIST)
export norflash_lib_$(SOC)_CORELIST

#
# NORFLASH Examples
#

# nor_flash_writer example
nor_flash_writer_COMP_LIST = nor_flash_writer
nor_flash_writer_RELPATH = ti/boot/sbl_auto/norflash/examples/nor_flash_writer/
nor_flash_writer_PATH = $(PDK_NORFLASH_COMP_PATH)/examples/nor_flash_writer/
nor_flash_writer_BOARD_DEPENDENCY = yes
nor_flash_writer_CORE_DEPENDENCY = no
export nor_flash_writer_COMP_LIST
export nor_flash_writer_BOARD_DEPENDENCY
export nor_flash_writer_CORE_DEPENDENCY
nor_flash_writer_PKG_LIST = nor_flash_writer
nor_flash_writer_INCLUDE = $(nor_flash_writer_PATH)
nor_flash_writer_BOARDLIST = $(norflash_BOARDLIST)
export nor_flash_writer_BOARDLIST
nor_flash_writer_$(SOC)_CORELIST = ipu1_0
export nor_flash_writer_$(SOC)_CORELIST

export norflash_LIB_LIST
export norflash_EXAMPLE_LIST

norflash_component_make_include := 1
endif
