# File: stw_examples_component.mk
#       This file is component include make file of STW Examples library.
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
ifeq ($(stw_examples_component_make_include), )

stw_examples_default_SOCLIST = tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x
stw_examples_default_tda2xx_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_examples_default_tda2px_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_examples_default_tda2ex_CORELIST = a15_0 ipu1_0 c66x
stw_examples_default_tda3xx_CORELIST = ipu1_0 c66x arp32_1
stw_examples_default_dra72x_CORELIST = a15_0 ipu1_0 c66x
stw_examples_default_dra75x_CORELIST = a15_0 ipu1_0 c66x arp32_1
stw_examples_default_dra78x_CORELIST = ipu1_0 c66x arp32_1

############################
# stw_examples package
# List of components included under stw_examples
# The components included here are built and will be part of stw_examples lib
############################
stw_examples_LIB_LIST = stw_examples_utility

############################
# stw_examples examples
# List of examples under stw_examples (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_examples_EXAMPLE_LIST =

#
# STW Devices Modules
#

# STW Devices Lib
stw_examples_utility_COMP_LIST = stw_examples_utility
stw_examples_utility_RELPATH = ti/drv/stw_lld/examples/utility
stw_examples_utility_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/utility
stw_examples_utility_LIBNAME = stw_examples_utility
stw_examples_utility_LIBPATH = $(PDK_STW_EXAMPLE_COMP_PATH)/utility/lib
stw_examples_utility_MAKEFILE = -fsrc/makefile
export stw_examples_utility_MAKEFILE
export stw_examples_utility_LIBNAME
export stw_examples_utility_LIBPATH
stw_examples_utility_BOARD_DEPENDENCY = no
stw_examples_utility_CORE_DEPENDENCY = no
export stw_examples_utility_COMP_LIST
export stw_examples_utility_BOARD_DEPENDENCY
export stw_examples_utility_CORE_DEPENDENCY
stw_examples_utility_PKG_LIST = stw_examples_utility
stw_examples_utility_INCLUDE = $(stw_examples_utility_PATH)
stw_examples_utility_SOCLIST = $(stw_examples_default_SOCLIST)
export stw_examples_utility_SOCLIST
stw_examples_utility_$(SOC)_CORELIST = $(stw_examples_default_$(SOC)_CORELIST)
export stw_examples_utility_$(SOC)_CORELIST

# VIP baremetal test app
vps_examples_vip_baremetal_COMP_LIST = vps_examples_vip_baremetal
vps_examples_vip_baremetal_RELPATH = ti/drv/stw_lld/examples/vps/vip_baremetal_app
vps_examples_vip_baremetal_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/vps/vip_baremetal_app
vps_examples_vip_baremetal_BOARD_DEPENDENCY = yes
vps_examples_vip_baremetal_CORE_DEPENDENCY = yes
export vps_examples_vip_baremetal_COMP_LIST
export vps_examples_vip_baremetal_BOARD_DEPENDENCY
export vps_examples_vip_baremetal_CORE_DEPENDENCY
vps_examples_vip_baremetal_PKG_LIST = vps_examples_vip_baremetal
vps_examples_vip_baremetal_INCLUDE = $(vps_examples_vip_baremetal_PATH)
vps_examples_vip_baremetal_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export vps_examples_vip_baremetal_BOARDLIST
vps_examples_vip_baremetal_$(SOC)_CORELIST = ipu1_0
export vps_examples_vip_baremetal_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += vps_examples_vip_baremetal
vps_examples_vip_baremetal_SBL_APPIMAGEGEN = yes
export vps_examples_vip_baremetal_SBL_APPIMAGEGEN

# OV sensor baremetal test app
vps_examples_ovsensor_baremetal_COMP_LIST = vps_examples_ovsensor_baremetal
vps_examples_ovsensor_baremetal_RELPATH = ti/drv/stw_lld/examples/vps/ovsensor_baremetal_app
vps_examples_ovsensor_baremetal_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/vps/ovsensor_baremetal_app
vps_examples_ovsensor_baremetal_BOARD_DEPENDENCY = yes
vps_examples_ovsensor_baremetal_CORE_DEPENDENCY = yes
export vps_examples_ovsensor_baremetal_COMP_LIST
export vps_examples_ovsensor_baremetal_BOARD_DEPENDENCY
export vps_examples_ovsensor_baremetal_CORE_DEPENDENCY
vps_examples_ovsensor_baremetal_PKG_LIST = vps_examples_ovsensor_baremetal
vps_examples_ovsensor_baremetal_INCLUDE = $(vps_examples_ovsensor_baremetal_PATH)
vps_examples_ovsensor_baremetal_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export vps_examples_ovsensor_baremetal_BOARDLIST
vps_examples_ovsensor_baremetal_$(SOC)_CORELIST = ipu1_0
export vps_examples_ovsensor_baremetal_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += vps_examples_ovsensor_baremetal
vps_examples_ovsensor_baremetal_SBL_APPIMAGEGEN = yes
export vps_examples_ovsensor_baremetal_SBL_APPIMAGEGEN

# i2c eeprom app
drv_stw_lld_i2c_eeprom_app_COMP_LIST = drv_stw_lld_i2c_eeprom_app
drv_stw_lld_i2c_eeprom_app_RELPATH = ti/drv/stw_lld/examples/i2c/i2c_eeprom_app
drv_stw_lld_i2c_eeprom_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/i2c/i2c_eeprom_app
drv_stw_lld_i2c_eeprom_app_BOARD_DEPENDENCY = yes
drv_stw_lld_i2c_eeprom_app_CORE_DEPENDENCY = yes
export drv_stw_lld_i2c_eeprom_app_COMP_LIST
export drv_stw_lld_i2c_eeprom_app_BOARD_DEPENDENCY
export drv_stw_lld_i2c_eeprom_app_CORE_DEPENDENCY
drv_stw_lld_i2c_eeprom_app_PKG_LIST = drv_stw_lld_i2c_eeprom_app
drv_stw_lld_i2c_eeprom_app_INCLUDE = $(drv_stw_lld_i2c_eeprom_app_PATH)
drv_stw_lld_i2c_eeprom_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export drv_stw_lld_i2c_eeprom_app_BOARDLIST
drv_stw_lld_i2c_eeprom_app_tda2xx_CORELIST = a15_0
drv_stw_lld_i2c_eeprom_app_tda2px_CORELIST = a15_0
drv_stw_lld_i2c_eeprom_app_tda2ex_CORELIST = a15_0
drv_stw_lld_i2c_eeprom_app_tda3xx_CORELIST = ipu1_0
export drv_stw_lld_i2c_eeprom_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_i2c_eeprom_app
drv_stw_lld_i2c_eeprom_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_i2c_eeprom_app_SBL_APPIMAGEGEN

# edid programmer app
drv_stw_lld_edid_programmer_app_COMP_LIST = drv_stw_lld_edid_programmer_app
drv_stw_lld_edid_programmer_app_RELPATH = ti/drv/stw_lld/examples/i2c/edid_programmer
drv_stw_lld_edid_programmer_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/i2c/edid_programmer
drv_stw_lld_edid_programmer_app_BOARD_DEPENDENCY = yes
drv_stw_lld_edid_programmer_app_CORE_DEPENDENCY = yes
export drv_stw_lld_edid_programmer_app_COMP_LIST
export drv_stw_lld_edid_programmer_app_BOARD_DEPENDENCY
export drv_stw_lld_edid_programmer_app_CORE_DEPENDENCY
drv_stw_lld_edid_programmer_app_PKG_LIST = drv_stw_lld_edid_programmer_app
drv_stw_lld_edid_programmer_app_INCLUDE = $(drv_stw_lld_edid_programmer_app_PATH)
drv_stw_lld_edid_programmer_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export drv_stw_lld_edid_programmer_app_BOARDLIST
drv_stw_lld_edid_programmer_app_tda2xx_CORELIST = a15_0
drv_stw_lld_edid_programmer_app_tda2px_CORELIST = a15_0
drv_stw_lld_edid_programmer_app_tda2ex_CORELIST = a15_0
drv_stw_lld_edid_programmer_app_tda3xx_CORELIST = ipu1_0
export drv_stw_lld_edid_programmer_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_edid_programmer_app
drv_stw_lld_edid_programmer_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_edid_programmer_app_SBL_APPIMAGEGEN

# i2c slave app
drv_stw_lld_i2c_slave_app_COMP_LIST = drv_stw_lld_i2c_slave_app
drv_stw_lld_i2c_slave_app_RELPATH = ti/drv/stw_lld/examples/i2c/i2c_slave_app
drv_stw_lld_i2c_slave_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/i2c/i2c_slave_app
drv_stw_lld_i2c_slave_app_BOARD_DEPENDENCY = yes
drv_stw_lld_i2c_slave_app_CORE_DEPENDENCY = yes
export drv_stw_lld_i2c_slave_app_COMP_LIST
export drv_stw_lld_i2c_slave_app_BOARD_DEPENDENCY
export drv_stw_lld_i2c_slave_app_CORE_DEPENDENCY
drv_stw_lld_i2c_slave_app_PKG_LIST = drv_stw_lld_i2c_slave_app
drv_stw_lld_i2c_slave_app_INCLUDE = $(drv_stw_lld_i2c_slave_app_PATH)
drv_stw_lld_i2c_slave_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export drv_stw_lld_i2c_slave_app_BOARDLIST
drv_stw_lld_i2c_slave_app_tda2xx_CORELIST = a15_0
drv_stw_lld_i2c_slave_app_tda2px_CORELIST = a15_0
drv_stw_lld_i2c_slave_app_tda2ex_CORELIST = a15_0
drv_stw_lld_i2c_slave_app_tda3xx_CORELIST = ipu1_0
export drv_stw_lld_i2c_slave_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_i2c_slave_app
drv_stw_lld_i2c_slave_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_i2c_slave_app_SBL_APPIMAGEGEN

# mcasp sinetone app
drv_stw_lld_mcasp_sinetone_app_COMP_LIST = drv_stw_lld_mcasp_sinetone_app
drv_stw_lld_mcasp_sinetone_app_RELPATH = ti/drv/stw_lld/examples/mcasp/mcasp_sinetone
drv_stw_lld_mcasp_sinetone_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/mcasp/mcasp_sinetone
drv_stw_lld_mcasp_sinetone_app_BOARD_DEPENDENCY = yes
drv_stw_lld_mcasp_sinetone_app_CORE_DEPENDENCY = yes
export drv_stw_lld_mcasp_sinetone_app_COMP_LIST
export drv_stw_lld_mcasp_sinetone_app_BOARD_DEPENDENCY
export drv_stw_lld_mcasp_sinetone_app_CORE_DEPENDENCY
drv_stw_lld_mcasp_sinetone_app_PKG_LIST = drv_stw_lld_mcasp_sinetone_app
drv_stw_lld_mcasp_sinetone_app_INCLUDE = $(drv_stw_lld_mcasp_sinetone_app_PATH)
drv_stw_lld_mcasp_sinetone_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm
export drv_stw_lld_mcasp_sinetone_app_BOARDLIST
drv_stw_lld_mcasp_sinetone_app_$(SOC)_CORELIST = a15_0 c66x
export drv_stw_lld_mcasp_sinetone_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_mcasp_sinetone_app
drv_stw_lld_mcasp_sinetone_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_mcasp_sinetone_app_SBL_APPIMAGEGEN

# DCAN test app evm loopback
drv_stw_lld_dcan_evm_loopback_app_COMP_LIST = drv_stw_lld_dcan_evm_loopback_app
drv_stw_lld_dcan_evm_loopback_app_RELPATH = ti/drv/stw_lld/examples/dcan/dcanEvmLoopback
drv_stw_lld_dcan_evm_loopback_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/dcan/dcanEvmLoopback
drv_stw_lld_dcan_evm_loopback_app_BOARD_DEPENDENCY = yes
drv_stw_lld_dcan_evm_loopback_app_CORE_DEPENDENCY = yes
export drv_stw_lld_dcan_evm_loopback_app_COMP_LIST
export drv_stw_lld_dcan_evm_loopback_app_BOARD_DEPENDENCY
export drv_stw_lld_dcan_evm_loopback_app_CORE_DEPENDENCY
drv_stw_lld_dcan_evm_loopback_app_PKG_LIST = drv_stw_lld_dcan_evm_loopback_app
drv_stw_lld_dcan_evm_loopback_app_INCLUDE = $(drv_stw_lld_dcan_evm_loopback_app_PATH)
drv_stw_lld_dcan_evm_loopback_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export drv_stw_lld_dcan_evm_loopback_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), tda2xx-evm tda2px-evm tda2ex-evm))
drv_stw_lld_dcan_evm_loopback_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(BOARD),$(filter $(BOARD), tda3xx-evm))
drv_stw_lld_dcan_evm_loopback_app_$(SOC)_CORELIST = ipu1_0
endif
export drv_stw_lld_dcan_evm_loopback_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_dcan_evm_loopback_app
drv_stw_lld_dcan_evm_loopback_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_dcan_evm_loopback_app_SBL_APPIMAGEGEN

# DCC 32K RC OSCCLK app
drv_stw_lld_dcc6_32k_rc_oscclk_app_COMP_LIST = drv_stw_lld_dcc6_32k_rc_oscclk_app
drv_stw_lld_dcc6_32k_rc_oscclk_app_RELPATH = ti/drv/stw_lld/examples/dcc6_32k_rc_oscclk_app
drv_stw_lld_dcc6_32k_rc_oscclk_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/dcc6_32k_rc_oscclk_app
drv_stw_lld_dcc6_32k_rc_oscclk_app_BOARD_DEPENDENCY = no
drv_stw_lld_dcc6_32k_rc_oscclk_app_CORE_DEPENDENCY = yes
export drv_stw_lld_dcc6_32k_rc_oscclk_app_COMP_LIST
export drv_stw_lld_dcc6_32k_rc_oscclk_app_BOARD_DEPENDENCY
export drv_stw_lld_dcc6_32k_rc_oscclk_app_CORE_DEPENDENCY
drv_stw_lld_dcc6_32k_rc_oscclk_app_PKG_LIST = drv_stw_lld_dcc6_32k_rc_oscclk_app
drv_stw_lld_dcc6_32k_rc_oscclk_app_INCLUDE = $(drv_stw_lld_dcc6_32k_rc_oscclk_app_PATH)
drv_stw_lld_dcc6_32k_rc_oscclk_app_BOARDLIST = tda3xx-evm
export drv_stw_lld_dcc6_32k_rc_oscclk_app_BOARDLIST
drv_stw_lld_dcc6_32k_rc_oscclk_app_$(SOC)_CORELIST = ipu1_0
export drv_stw_lld_dcc6_32k_rc_oscclk_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_dcc6_32k_rc_oscclk_app
drv_stw_lld_dcc6_32k_rc_oscclk_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_dcc6_32k_rc_oscclk_app_SBL_APPIMAGEGEN

# mmcsd file iO app
drv_stw_lld_mmcsd_file_io_app_COMP_LIST = drv_stw_lld_mmcsd_file_io_app
drv_stw_lld_mmcsd_file_io_app_RELPATH = ti/drv/stw_lld/examples/mmcsd/sd_file_io
drv_stw_lld_mmcsd_file_io_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/mmcsd/sd_file_io
drv_stw_lld_mmcsd_file_io_app_BOARD_DEPENDENCY = yes
drv_stw_lld_mmcsd_file_io_app_CORE_DEPENDENCY = yes
export drv_stw_lld_mmcsd_file_io_app_COMP_LIST
export drv_stw_lld_mmcsd_file_io_app_BOARD_DEPENDENCY
export drv_stw_lld_mmcsd_file_io_app_CORE_DEPENDENCY
drv_stw_lld_mmcsd_file_io_app_PKG_LIST = drv_stw_lld_mmcsd_file_io_app
drv_stw_lld_mmcsd_file_io_app_INCLUDE = $(drv_stw_lld_mmcsd_file_io_app_PATH)
drv_stw_lld_mmcsd_file_io_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export drv_stw_lld_mmcsd_file_io_app_BOARDLIST
drv_stw_lld_mmcsd_file_io_app_$(SOC)_CORELIST = ipu1_0
export drv_stw_lld_mmcsd_file_io_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += drv_stw_lld_mmcsd_file_io_app
drv_stw_lld_mmcsd_file_io_app_SBL_APPIMAGEGEN = yes
export drv_stw_lld_mmcsd_file_io_app_SBL_APPIMAGEGEN

# diag lib Test app
diag_test_app_COMP_LIST = diag_test_app
diag_test_app_RELPATH = ti/drv/stw_lld/examples/diag_test_app
diag_test_app_PATH = $(PDK_STW_EXAMPLE_COMP_PATH)/diag_test_app
diag_test_app_BOARD_DEPENDENCY = no
diag_test_app_CORE_DEPENDENCY = yes
diag_test_app_XDC_CONFIGURO = no
export diag_test_app_COMP_LIST
export diag_test_app_BOARD_DEPENDENCY
export diag_test_app_CORE_DEPENDENCY
export diag_test_app_XDC_CONFIGURO
diag_test_app_PKG_LIST = diag_test_app
diag_test_app_INCLUDE = $(diag_test_app_PATH)
diag_test_app_SOCLIST = tda2xx tda2px tda2ex tda3xx
export diag_test_app_SOCLIST
diag_test_app_$(SOC)_CORELIST = ipu1_0
export diag_test_app_$(SOC)_CORELIST
stw_examples_EXAMPLE_LIST += diag_test_app
diag_test_app_SBL_APPIMAGEGEN = yes
export diag_test_app_SBL_APPIMAGEGEN


export stw_examples_LIB_LIST
export stw_examples_EXAMPLE_LIST

stw_examples_component_make_include := 1
endif
