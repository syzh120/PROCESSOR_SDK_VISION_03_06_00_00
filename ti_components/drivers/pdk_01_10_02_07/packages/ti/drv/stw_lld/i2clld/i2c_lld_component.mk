# File: i2c_lld_component.mk
#       This file is component include make file of STW I2C LLD library.
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
ifeq ($(i2c_lld_component_make_include), )

i2c_lld_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
i2c_lld_default_tda2xx_CORELIST = a15_0 ipu1_0 c66x
i2c_lld_default_tda2px_CORELIST = a15_0 ipu1_0 c66x
i2c_lld_default_tda2ex_CORELIST = a15_0 ipu1_0 c66x
i2c_lld_default_tda3xx_CORELIST = ipu1_0 c66x
i2c_lld_default_dra72x_CORELIST = a15_0 ipu1_0 c66x
i2c_lld_default_dra75x_CORELIST = a15_0 ipu1_0 c66x
i2c_lld_default_dra78x_CORELIST = ipu1_0 c66x

############################
# i2c_lld package
# List of components included under i2c_lld
# The components included here are built and will be part of i2c_lld lib
############################
i2c_lld_LIB_LIST = i2c_lld

############################
# i2c_lld examples
# List of examples under i2c_lld (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
i2c_lld_EXAMPLE_LIST =

#
# I2C LLD Modules
#

# I2C LLD LIB
i2c_lld_COMP_LIST = i2c_lld
i2c_lld_RELPATH = ti/drv/stw_lld/i2clld
i2c_lld_PATH = $(PDK_STW_I2C_LLD_COMP_PATH)
i2c_lld_LIBNAME = i2c_lld
i2c_lld_LIBPATH = $(PDK_STW_I2C_LLD_COMP_PATH)/lib
i2c_lld_MAKEFILE = -fsrc/makefile
export i2c_lld_MAKEFILE
export i2c_lld_LIBNAME
export i2c_lld_LIBPATH
i2c_lld_BOARD_DEPENDENCY = no
i2c_lld_CORE_DEPENDENCY = no
export i2c_lld_COMP_LIST
export i2c_lld_BOARD_DEPENDENCY
export i2c_lld_CORE_DEPENDENCY
i2c_lld_PKG_LIST = i2c_lld
i2c_lld_INCLUDE = $(i2c_lld_PATH)
i2c_lld_SOCLIST = $(i2c_lld_default_SOCLIST)
export i2c_lld_SOCLIST
i2c_lld_$(SOC)_CORELIST = $(i2c_lld_default_$(SOC)_CORELIST)
export i2c_lld_$(SOC)_CORELIST

export i2c_lld_LIB_LIST
export i2c_lld_EXAMPLE_LIST

i2c_lld_component_make_include := 1
endif
