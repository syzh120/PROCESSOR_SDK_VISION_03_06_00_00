# File: stw_unit_test_component.mk
#       This file is component include make file of STW unit test.
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
ifeq ($(stw_unit_test_component_make_include), )

stw_unit_test_default_SOCLIST = tda2xx tda2px tda2ex tda3xx
stw_unit_test_default_tda2xx_CORELIST = a15_0
stw_unit_test_default_tda2px_CORELIST = a15_0
stw_unit_test_default_tda2ex_CORELIST = a15_0
stw_unit_test_default_tda3xx_CORELIST = ipu1_0

############################
# stw_unit_test package
# List of components included under stw_unit_test
# The components included here are built and will be part of stw_unit_test lib
############################
stw_unit_test_LIB_LIST =

############################
# stw_unit_test examples
# List of examples under stw_unit_test (+= is used at each example definition)
# All the tests mentioned in list are built when test target is called
# List below all examples for allowed values
############################
stw_unit_test_EXAMPLE_LIST =
stw_unit_test_DUP_EXAMPLE_LIST =

# ADC unit test app
adc_unit_test_app_COMP_LIST = adc_unit_test_app
adc_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/adcUt
adc_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/adcUt
adc_unit_test_app_BOARD_DEPENDENCY = yes
adc_unit_test_app_CORE_DEPENDENCY = yes
export adc_unit_test_app_COMP_LIST
export adc_unit_test_app_BOARD_DEPENDENCY
export adc_unit_test_app_CORE_DEPENDENCY
adc_unit_test_app_PKG_LIST = adc_unit_test_app
adc_unit_test_app_INCLUDE = $(adc_unit_test_app_PATH)
adc_unit_test_app_BOARDLIST = tda3xx-evm
export adc_unit_test_app_BOARDLIST
adc_unit_test_app_$(SOC)_CORELIST = ipu1_0
export adc_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += adc_unit_test_app
adc_unit_test_app_SBL_APPIMAGEGEN = yes
export adc_unit_test_app_SBL_APPIMAGEGEN

# CRC unit test app
crc_unit_test_app_COMP_LIST = crc_unit_test_app
crc_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/crcUt
crc_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/crcUt
crc_unit_test_app_BOARD_DEPENDENCY = yes
crc_unit_test_app_CORE_DEPENDENCY = yes
export crc_unit_test_app_COMP_LIST
export crc_unit_test_app_BOARD_DEPENDENCY
export crc_unit_test_app_CORE_DEPENDENCY
crc_unit_test_app_PKG_LIST = crc_unit_test_app
crc_unit_test_app_INCLUDE = $(crc_unit_test_app_PATH)
crc_unit_test_app_BOARDLIST = tda3xx-evm
export crc_unit_test_app_BOARDLIST
crc_unit_test_app_$(SOC)_CORELIST = ipu1_0 c66x c66xdsp_2
export crc_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += crc_unit_test_app
crc_unit_test_app_SBL_APPIMAGEGEN = yes
export crc_unit_test_app_SBL_APPIMAGEGEN

# DCAN unit test app
dcan_unit_test_app_COMP_LIST = dcan_unit_test_app
dcan_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/dcan/dcanUt
dcan_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/dcan/dcanUt
dcan_unit_test_app_BOARD_DEPENDENCY = yes
dcan_unit_test_app_CORE_DEPENDENCY = yes
export dcan_unit_test_app_COMP_LIST
export dcan_unit_test_app_BOARD_DEPENDENCY
export dcan_unit_test_app_CORE_DEPENDENCY
dcan_unit_test_app_PKG_LIST = dcan_unit_test_app
dcan_unit_test_app_INCLUDE = $(dcan_unit_test_app_PATH)
dcan_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export dcan_unit_test_app_BOARDLIST
dcan_unit_test_app_$(SOC)_CORELIST = ipu1_0
export dcan_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += dcan_unit_test_app
dcan_unit_test_app_SBL_APPIMAGEGEN = yes
export dcan_unit_test_app_SBL_APPIMAGEGEN

# DCAN unit test stub app
dcan_unit_test_stub_app_COMP_LIST = dcan_unit_test_stub_app
dcan_unit_test_stub_app_RELPATH = ti/drv/stw_lld/unit_test/dcan/dcantestStub
dcan_unit_test_stub_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/dcan/dcantestStub
dcan_unit_test_stub_app_BOARD_DEPENDENCY = yes
dcan_unit_test_stub_app_CORE_DEPENDENCY = yes
export dcan_unit_test_stub_app_COMP_LIST
export dcan_unit_test_stub_app_BOARD_DEPENDENCY
export dcan_unit_test_stub_app_CORE_DEPENDENCY
dcan_unit_test_stub_app_PKG_LIST = dcan_unit_test_stub_app
dcan_unit_test_stub_app_INCLUDE = $(dcan_unit_test_stub_app_PATH)
dcan_unit_test_stub_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export dcan_unit_test_stub_app_BOARDLIST
dcan_unit_test_stub_app_$(SOC)_CORELIST = ipu1_0
export dcan_unit_test_stub_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += dcan_unit_test_stub_app
dcan_unit_test_stub_app_SBL_APPIMAGEGEN = yes
export dcan_unit_test_stub_app_SBL_APPIMAGEGEN

# DCC unit test app
dcc_unit_test_app_COMP_LIST = dcc_unit_test_app
dcc_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/dccUt
dcc_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/dccUt
dcc_unit_test_app_BOARD_DEPENDENCY = yes
dcc_unit_test_app_CORE_DEPENDENCY = yes
export dcc_unit_test_app_COMP_LIST
export dcc_unit_test_app_BOARD_DEPENDENCY
export dcc_unit_test_app_CORE_DEPENDENCY
dcc_unit_test_app_PKG_LIST = dcc_unit_test_app
dcc_unit_test_app_INCLUDE = $(dcc_unit_test_app_PATH)
dcc_unit_test_app_BOARDLIST = tda3xx-evm
export dcc_unit_test_app_BOARDLIST
dcc_unit_test_app_$(SOC)_CORELIST = ipu1_0
export dcc_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += dcc_unit_test_app
dcc_unit_test_app_SBL_APPIMAGEGEN = yes
export dcc_unit_test_app_SBL_APPIMAGEGEN

# ECC unit test app
ecc_unit_test_app_COMP_LIST = ecc_unit_test_app
ecc_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/eccUt
ecc_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/eccUt
ecc_unit_test_app_BOARD_DEPENDENCY = yes
ecc_unit_test_app_CORE_DEPENDENCY = yes
export ecc_unit_test_app_COMP_LIST
export ecc_unit_test_app_BOARD_DEPENDENCY
export ecc_unit_test_app_CORE_DEPENDENCY
ecc_unit_test_app_PKG_LIST = ecc_unit_test_app
ecc_unit_test_app_INCLUDE = $(ecc_unit_test_app_PATH)
ecc_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export ecc_unit_test_app_BOARDLIST
ecc_unit_test_app_$(SOC)_CORELIST = ipu1_0
export ecc_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += ecc_unit_test_app
ecc_unit_test_app_SBL_APPIMAGEGEN = yes
export ecc_unit_test_app_SBL_APPIMAGEGEN

# ESM unit test app
esm_unit_test_app_COMP_LIST = esm_unit_test_app
esm_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/esmUt
esm_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/esmUt
esm_unit_test_app_BOARD_DEPENDENCY = yes
esm_unit_test_app_CORE_DEPENDENCY = yes
export esm_unit_test_app_COMP_LIST
export esm_unit_test_app_BOARD_DEPENDENCY
export esm_unit_test_app_CORE_DEPENDENCY
esm_unit_test_app_PKG_LIST = esm_unit_test_app
esm_unit_test_app_INCLUDE = $(esm_unit_test_app_PATH)
esm_unit_test_app_BOARDLIST = tda3xx-evm
export esm_unit_test_app_BOARDLIST
esm_unit_test_app_$(SOC)_CORELIST = ipu1_0
export esm_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += esm_unit_test_app
esm_unit_test_app_SBL_APPIMAGEGEN = yes
export esm_unit_test_app_SBL_APPIMAGEGEN

# McSPI unit test app
mcspi_unit_test_app_COMP_LIST = mcspi_unit_test_app
mcspi_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/mcspiUt
mcspi_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/mcspiUt
mcspi_unit_test_app_BOARD_DEPENDENCY = yes
mcspi_unit_test_app_CORE_DEPENDENCY = yes
export mcspi_unit_test_app_COMP_LIST
export mcspi_unit_test_app_BOARD_DEPENDENCY
export mcspi_unit_test_app_CORE_DEPENDENCY
mcspi_unit_test_app_PKG_LIST = mcspi_unit_test_app
mcspi_unit_test_app_INCLUDE = $(mcspi_unit_test_app_PATH)
mcspi_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export mcspi_unit_test_app_BOARDLIST
mcspi_unit_test_app_$(SOC)_CORELIST = ipu1_0
export mcspi_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += mcspi_unit_test_app
mcspi_unit_test_app_SBL_APPIMAGEGEN = yes
export mcspi_unit_test_app_SBL_APPIMAGEGEN

# QSPI unit test app
qspi_unit_test_app_COMP_LIST = qspi_unit_test_app
qspi_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/qspiUt
qspi_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/qspiUt
qspi_unit_test_app_BOARD_DEPENDENCY = yes
qspi_unit_test_app_CORE_DEPENDENCY = yes
export qspi_unit_test_app_COMP_LIST
export qspi_unit_test_app_BOARD_DEPENDENCY
export qspi_unit_test_app_CORE_DEPENDENCY
qspi_unit_test_app_PKG_LIST = qspi_unit_test_app
qspi_unit_test_app_INCLUDE = $(qspi_unit_test_app_PATH)
qspi_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export qspi_unit_test_app_BOARDLIST
qspi_unit_test_app_$(SOC)_CORELIST = ipu1_0
export qspi_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += qspi_unit_test_app
qspi_unit_test_app_SBL_APPIMAGEGEN = yes
export qspi_unit_test_app_SBL_APPIMAGEGEN

# L3FW UT - dummy target to build all test case apps
l3fwUt_COMP_LIST = l3fwUt
l3fwUt_RELPATH = ti/drv/stw_lld/unit_test/l3fwUt
l3fwUt_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/l3fwUt
l3fwUt_BOARD_DEPENDENCY = yes
l3fwUt_CORE_DEPENDENCY = yes
export l3fwUt_COMP_LIST
export l3fwUt_BOARD_DEPENDENCY
export l3fwUt_CORE_DEPENDENCY
l3fwUt_PKG_LIST = l3fwUt
l3fwUt_INCLUDE = $(l3fwUt_PATH)
l3fwUt_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export l3fwUt_BOARDLIST
l3fwUt_$(SOC)_CORELIST = $(stw_unit_test_default_$(SOC)_CORELIST)
export l3fwUt_$(SOC)_CORELIST
stw_unit_test_DUP_EXAMPLE_LIST += l3fwUt

# L3FW unit test app
l3fw_permission_all_unit_test_app_COMP_LIST = l3fw_permission_all_unit_test_app
l3fw_permission_all_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/l3fwUt/l3fw_permission_all
l3fw_permission_all_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/l3fwUt/l3fw_permission_all
l3fw_permission_all_unit_test_app_BOARD_DEPENDENCY = yes
l3fw_permission_all_unit_test_app_CORE_DEPENDENCY = yes
export l3fw_permission_all_unit_test_app_COMP_LIST
export l3fw_permission_all_unit_test_app_BOARD_DEPENDENCY
export l3fw_permission_all_unit_test_app_CORE_DEPENDENCY
l3fw_permission_all_unit_test_app_PKG_LIST = l3fw_permission_all_unit_test_app
l3fw_permission_all_unit_test_app_INCLUDE = $(l3fw_permission_all_unit_test_app_PATH)
l3fw_permission_all_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export l3fw_permission_all_unit_test_app_BOARDLIST
l3fw_permission_all_unit_test_app_$(SOC)_CORELIST = $(stw_unit_test_default_$(SOC)_CORELIST)
export l3fw_permission_all_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += l3fw_permission_all_unit_test_app
l3fw_permission_all_unit_test_app_SBL_APPIMAGEGEN = yes
export l3fw_permission_all_unit_test_app_SBL_APPIMAGEGEN

# L3FW unit test app
l3fw_writeonly_unit_test_app_COMP_LIST = l3fw_writeonly_unit_test_app
l3fw_writeonly_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/l3fwUt/l3fw_writeOnly
l3fw_writeonly_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/l3fwUt/l3fw_writeOnly
l3fw_writeonly_unit_test_app_BOARD_DEPENDENCY = yes
l3fw_writeonly_unit_test_app_CORE_DEPENDENCY = yes
export l3fw_writeonly_unit_test_app_COMP_LIST
export l3fw_writeonly_unit_test_app_BOARD_DEPENDENCY
export l3fw_writeonly_unit_test_app_CORE_DEPENDENCY
l3fw_writeonly_unit_test_app_PKG_LIST = l3fw_writeonly_unit_test_app
l3fw_writeonly_unit_test_app_INCLUDE = $(l3fw_writeonly_unit_test_app_PATH)
l3fw_writeonly_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export l3fw_writeonly_unit_test_app_BOARDLIST
l3fw_writeonly_unit_test_app_$(SOC)_CORELIST = $(stw_unit_test_default_$(SOC)_CORELIST)
export l3fw_writeonly_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += l3fw_writeonly_unit_test_app
l3fw_writeonly_unit_test_app_SBL_APPIMAGEGEN = yes
export l3fw_writeonly_unit_test_app_SBL_APPIMAGEGEN

# PM UT - dummy target to build all test case apps
pmUt_COMP_LIST = pmUt
pmUt_RELPATH = ti/drv/stw_lld/unit_test/pmUt
pmUt_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt
pmUt_BOARD_DEPENDENCY = yes
pmUt_CORE_DEPENDENCY = yes
export pmUt_COMP_LIST
export pmUt_BOARD_DEPENDENCY
export pmUt_CORE_DEPENDENCY
pmUt_PKG_LIST = pmUt
pmUt_INCLUDE = $(pmUt_PATH)
pmUt_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmUt_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
  pmUt_$(SOC)_CORELIST = a15_0 ipu1_0 c66x arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
  pmUt_$(SOC)_CORELIST = a15_0 ipu1_0 c66x
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmUt_$(SOC)_CORELIST = ipu1_0 c66x arp32_1
endif
export pmUt_$(SOC)_CORELIST
stw_unit_test_DUP_EXAMPLE_LIST += pmUt

# PM UT unit test app - PM LIB AUTOCG
pmlib_autocg_unit_test_app_COMP_LIST = pmlib_autocg_unit_test_app
pmlib_autocg_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/hwapps_char_tests/pmlib_autocg
pmlib_autocg_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/hwapps_char_tests/pmlib_autocg
pmlib_autocg_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_autocg_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_autocg_unit_test_app_COMP_LIST
export pmlib_autocg_unit_test_app_BOARD_DEPENDENCY
export pmlib_autocg_unit_test_app_CORE_DEPENDENCY
pmlib_autocg_unit_test_app_PKG_LIST = pmlib_autocg_unit_test_app
pmlib_autocg_unit_test_app_INCLUDE = $(pmlib_autocg_unit_test_app_PATH)
pmlib_autocg_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_autocg_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
  pmlib_autocg_unit_test_app_$(SOC)_CORELIST = c66x arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
  pmlib_autocg_unit_test_app_$(SOC)_CORELIST = c66x
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_autocg_unit_test_app_$(SOC)_CORELIST = c66x arp32_1
endif
export pmlib_autocg_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_autocg_unit_test_app
pmlib_autocg_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_autocg_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PM LIB IDLE
pmlib_idle_unit_test_app_COMP_LIST = pmlib_idle_unit_test_app
pmlib_idle_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/hwapps_char_tests/pmlib_idle
pmlib_idle_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/hwapps_char_tests/pmlib_idle
pmlib_idle_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_idle_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_idle_unit_test_app_COMP_LIST
export pmlib_idle_unit_test_app_BOARD_DEPENDENCY
export pmlib_idle_unit_test_app_CORE_DEPENDENCY
pmlib_idle_unit_test_app_PKG_LIST = pmlib_idle_unit_test_app
pmlib_idle_unit_test_app_INCLUDE = $(pmlib_idle_unit_test_app_PATH)
pmlib_idle_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_idle_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
  pmlib_idle_unit_test_app_$(SOC)_CORELIST = c66x arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
  pmlib_idle_unit_test_app_$(SOC)_CORELIST = c66x
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_idle_unit_test_app_$(SOC)_CORELIST = c66x arp32_1
endif
export pmlib_idle_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_idle_unit_test_app
pmlib_idle_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_idle_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PM LIB PDOFF
pmlib_pdoff_unit_test_app_COMP_LIST = pmlib_pdoff_unit_test_app
pmlib_pdoff_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/hwapps_char_tests/pmlib_pdoff
pmlib_pdoff_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/hwapps_char_tests/pmlib_pdoff
pmlib_pdoff_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_pdoff_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_pdoff_unit_test_app_COMP_LIST
export pmlib_pdoff_unit_test_app_BOARD_DEPENDENCY
export pmlib_pdoff_unit_test_app_CORE_DEPENDENCY
pmlib_pdoff_unit_test_app_PKG_LIST = pmlib_pdoff_unit_test_app
pmlib_pdoff_unit_test_app_INCLUDE = $(pmlib_pdoff_unit_test_app_PATH)
pmlib_pdoff_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_pdoff_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px))
  pmlib_pdoff_unit_test_app_$(SOC)_CORELIST = ipu1_0 c66x arp32_1
endif
ifeq ($(SOC),$(filter $(SOC), tda2ex))
  pmlib_pdoff_unit_test_app_$(SOC)_CORELIST = c66x
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_pdoff_unit_test_app_$(SOC)_CORELIST = c66x arp32_1
endif
export pmlib_pdoff_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_pdoff_unit_test_app
pmlib_pdoff_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_pdoff_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PM Leakage
pm_leakage_unit_test_app_COMP_LIST = pm_leakage_unit_test_app
pm_leakage_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pm_leakage_test
pm_leakage_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pm_leakage_test
pm_leakage_unit_test_app_BOARD_DEPENDENCY = yes
pm_leakage_unit_test_app_CORE_DEPENDENCY = yes
export pm_leakage_unit_test_app_COMP_LIST
export pm_leakage_unit_test_app_BOARD_DEPENDENCY
export pm_leakage_unit_test_app_CORE_DEPENDENCY
pm_leakage_unit_test_app_PKG_LIST = pm_leakage_unit_test_app
pm_leakage_unit_test_app_INCLUDE = $(pm_leakage_unit_test_app_PATH)
pm_leakage_unit_test_app_BOARDLIST = tda2xx-evm tda3xx-evm
export pm_leakage_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx))
pm_leakage_unit_test_app_$(SOC)_CORELIST = a15_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
pm_leakage_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pm_leakage_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pm_leakage_unit_test_app
pm_leakage_unit_test_app_SBL_APPIMAGEGEN = yes
export pm_leakage_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMHAL DPLL CORE SYSCLK2
pmhal_dpll_core_sysclk2_unit_test_app_COMP_LIST = pmhal_dpll_core_sysclk2_unit_test_app
pmhal_dpll_core_sysclk2_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmhal_dpll_core_sysclk2
pmhal_dpll_core_sysclk2_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmhal_dpll_core_sysclk2
pmhal_dpll_core_sysclk2_unit_test_app_BOARD_DEPENDENCY = yes
pmhal_dpll_core_sysclk2_unit_test_app_CORE_DEPENDENCY = yes
export pmhal_dpll_core_sysclk2_unit_test_app_COMP_LIST
export pmhal_dpll_core_sysclk2_unit_test_app_BOARD_DEPENDENCY
export pmhal_dpll_core_sysclk2_unit_test_app_CORE_DEPENDENCY
pmhal_dpll_core_sysclk2_unit_test_app_PKG_LIST = pmhal_dpll_core_sysclk2_unit_test_app
pmhal_dpll_core_sysclk2_unit_test_app_INCLUDE = $(pmhal_dpll_core_sysclk2_unit_test_app_PATH)
pmhal_dpll_core_sysclk2_unit_test_app_BOARDLIST = tda3xx-evm
export pmhal_dpll_core_sysclk2_unit_test_app_BOARDLIST
pmhal_dpll_core_sysclk2_unit_test_app_$(SOC)_CORELIST = ipu1_0
export pmhal_dpll_core_sysclk2_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmhal_dpll_core_sysclk2_unit_test_app
pmhal_dpll_core_sysclk2_unit_test_app_SBL_APPIMAGEGEN = yes
export pmhal_dpll_core_sysclk2_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMHAL SW cold reset
pmhal_coldreset_unit_test_app_COMP_LIST = pmhal_coldreset_unit_test_app
pmhal_coldreset_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmhal_sw_cold_reset
pmhal_coldreset_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmhal_sw_cold_reset
pmhal_coldreset_unit_test_app_BOARD_DEPENDENCY = yes
pmhal_coldreset_unit_test_app_CORE_DEPENDENCY = yes
export pmhal_coldreset_unit_test_app_COMP_LIST
export pmhal_coldreset_unit_test_app_BOARD_DEPENDENCY
export pmhal_coldreset_unit_test_app_CORE_DEPENDENCY
pmhal_coldreset_unit_test_app_PKG_LIST = pmhal_coldreset_unit_test_app
pmhal_coldreset_unit_test_app_INCLUDE = $(pmhal_coldreset_unit_test_app_PATH)
pmhal_coldreset_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmhal_coldreset_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmhal_coldreset_unit_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmhal_coldreset_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmhal_coldreset_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmhal_coldreset_unit_test_app
pmhal_coldreset_unit_test_app_SBL_APPIMAGEGEN = yes
export pmhal_coldreset_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMHAL SW warm reset
pmhal_warmreset_unit_test_app_COMP_LIST = pmhal_warmreset_unit_test_app
pmhal_warmreset_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmhal_sw_warm_reset
pmhal_warmreset_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmhal_sw_warm_reset
pmhal_warmreset_unit_test_app_BOARD_DEPENDENCY = yes
pmhal_warmreset_unit_test_app_CORE_DEPENDENCY = yes
export pmhal_warmreset_unit_test_app_COMP_LIST
export pmhal_warmreset_unit_test_app_BOARD_DEPENDENCY
export pmhal_warmreset_unit_test_app_CORE_DEPENDENCY
pmhal_warmreset_unit_test_app_PKG_LIST = pmhal_warmreset_unit_test_app
pmhal_warmreset_unit_test_app_INCLUDE = $(pmhal_warmreset_unit_test_app_PATH)
pmhal_warmreset_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmhal_warmreset_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmhal_warmreset_unit_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmhal_warmreset_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmhal_warmreset_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmhal_warmreset_unit_test_app
pmhal_warmreset_unit_test_app_SBL_APPIMAGEGEN = yes
export pmhal_warmreset_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMHAL VM
pmhal_vm_unit_test_app_COMP_LIST = pmhal_vm_unit_test_app
pmhal_vm_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmhal_vmapp
pmhal_vm_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmhal_vmapp
pmhal_vm_unit_test_app_BOARD_DEPENDENCY = yes
pmhal_vm_unit_test_app_CORE_DEPENDENCY = yes
export pmhal_vm_unit_test_app_COMP_LIST
export pmhal_vm_unit_test_app_BOARD_DEPENDENCY
export pmhal_vm_unit_test_app_CORE_DEPENDENCY
pmhal_vm_unit_test_app_PKG_LIST = pmhal_vm_unit_test_app
pmhal_vm_unit_test_app_INCLUDE = $(pmhal_vm_unit_test_app_PATH)
pmhal_vm_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmhal_vm_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmhal_vm_unit_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmhal_vm_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmhal_vm_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmhal_vm_unit_test_app
pmhal_vm_unit_test_app_SBL_APPIMAGEGEN = yes
export pmhal_vm_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMLIB Clock rate
pmlib_clkrate_unit_test_app_COMP_LIST = pmlib_clkrate_unit_test_app
pmlib_clkrate_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmlib_clkrate
pmlib_clkrate_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmlib_clkrate
pmlib_clkrate_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_clkrate_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_clkrate_unit_test_app_COMP_LIST
export pmlib_clkrate_unit_test_app_BOARD_DEPENDENCY
export pmlib_clkrate_unit_test_app_CORE_DEPENDENCY
pmlib_clkrate_unit_test_app_PKG_LIST = pmlib_clkrate_unit_test_app
pmlib_clkrate_unit_test_app_INCLUDE = $(pmlib_clkrate_unit_test_app_PATH)
pmlib_clkrate_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_clkrate_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmlib_clkrate_unit_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_clkrate_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmlib_clkrate_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_clkrate_unit_test_app
pmlib_clkrate_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_clkrate_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMLIB Sysconfig
pmlib_syscfg_unit_test_app_COMP_LIST = pmlib_syscfg_unit_test_app
pmlib_syscfg_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmlib_sysconfig
pmlib_syscfg_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmlib_sysconfig
pmlib_syscfg_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_syscfg_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_syscfg_unit_test_app_COMP_LIST
export pmlib_syscfg_unit_test_app_BOARD_DEPENDENCY
export pmlib_syscfg_unit_test_app_CORE_DEPENDENCY
pmlib_syscfg_unit_test_app_PKG_LIST = pmlib_syscfg_unit_test_app
pmlib_syscfg_unit_test_app_INCLUDE = $(pmlib_syscfg_unit_test_app_PATH)
pmlib_syscfg_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_syscfg_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmlib_syscfg_unit_test_app_$(SOC)_CORELIST = a15_0 ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_syscfg_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmlib_syscfg_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_syscfg_unit_test_app
pmlib_syscfg_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_syscfg_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMLIB Video PLL
pmlib_videopll_unit_test_app_COMP_LIST = pmlib_videopll_unit_test_app
pmlib_videopll_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmlib_videopll
pmlib_videopll_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmlib_videopll
pmlib_videopll_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_videopll_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_videopll_unit_test_app_COMP_LIST
export pmlib_videopll_unit_test_app_BOARD_DEPENDENCY
export pmlib_videopll_unit_test_app_CORE_DEPENDENCY
pmlib_videopll_unit_test_app_PKG_LIST = pmlib_videopll_unit_test_app
pmlib_videopll_unit_test_app_INCLUDE = $(pmlib_videopll_unit_test_app_PATH)
pmlib_videopll_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_videopll_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmlib_videopll_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_videopll_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmlib_videopll_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_videopll_unit_test_app
pmlib_videopll_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_videopll_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMLIB Video PLL Calculator
pmlib_videopllcalc_unit_test_app_COMP_LIST = pmlib_videopllcalc_unit_test_app
pmlib_videopllcalc_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmlib_videopll_calculator
pmlib_videopllcalc_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmlib_videopll_calculator
pmlib_videopllcalc_unit_test_app_BOARD_DEPENDENCY = yes
pmlib_videopllcalc_unit_test_app_CORE_DEPENDENCY = yes
export pmlib_videopllcalc_unit_test_app_COMP_LIST
export pmlib_videopllcalc_unit_test_app_BOARD_DEPENDENCY
export pmlib_videopllcalc_unit_test_app_CORE_DEPENDENCY
pmlib_videopllcalc_unit_test_app_PKG_LIST = pmlib_videopllcalc_unit_test_app
pmlib_videopllcalc_unit_test_app_INCLUDE = $(pmlib_videopllcalc_unit_test_app_PATH)
pmlib_videopllcalc_unit_test_app_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export pmlib_videopllcalc_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex))
  pmlib_videopllcalc_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  pmlib_videopllcalc_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmlib_videopllcalc_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmlib_videopllcalc_unit_test_app
pmlib_videopllcalc_unit_test_app_SBL_APPIMAGEGEN = yes
export pmlib_videopllcalc_unit_test_app_SBL_APPIMAGEGEN

# PM UT unit test app - PMHAL fractional multiplier
pmhal_dpll_fracm_unit_test_app_COMP_LIST = pmhal_dpll_fracm_unit_test_app
pmhal_dpll_fracm_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/pmUt/pmhal_dpll_fracm
pmhal_dpll_fracm_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/pmUt/pmhal_dpll_fracm
pmhal_dpll_fracm_unit_test_app_BOARD_DEPENDENCY = yes
pmhal_dpll_fracm_unit_test_app_CORE_DEPENDENCY = yes
export pmhal_dpll_fracm_unit_test_app_COMP_LIST
export pmhal_dpll_fracm_unit_test_app_BOARD_DEPENDENCY
export pmhal_dpll_fracm_unit_test_app_CORE_DEPENDENCY
pmhal_dpll_fracm_unit_test_app_PKG_LIST = pmhal_dpll_fracm_unit_test_app
pmhal_dpll_fracm_unit_test_app_INCLUDE = $(pmhal_dpll_fracm_unit_test_app_PATH)
pmhal_dpll_fracm_unit_test_app_BOARDLIST = tda2px-evm
export pmhal_dpll_fracm_unit_test_app_BOARDLIST
ifeq ($(SOC),$(filter $(SOC), tda2px))
  pmhal_dpll_fracm_unit_test_app_$(SOC)_CORELIST = ipu1_0
endif
export pmhal_dpll_fracm_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += pmhal_dpll_fracm_unit_test_app
pmhal_dpll_fracm_unit_test_app_SBL_APPIMAGEGEN = yes
export pmhal_dpll_fracm_unit_test_app_SBL_APPIMAGEGEN

# RTI UT - dummy target to build all test case apps
rtiUt_COMP_LIST = rtiUt
rtiUt_RELPATH = ti/drv/stw_lld/unit_test/rtiUt
rtiUt_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt
rtiUt_BOARD_DEPENDENCY = yes
rtiUt_CORE_DEPENDENCY = yes
export rtiUt_COMP_LIST
export rtiUt_BOARD_DEPENDENCY
export rtiUt_CORE_DEPENDENCY
rtiUt_PKG_LIST = rtiUt
rtiUt_INCLUDE = $(rtiUt_PATH)
rtiUt_BOARDLIST = tda3xx-evm
export rtiUt_BOARDLIST
rtiUt_$(SOC)_CORELIST = ipu1_0 c66x arp32_1
export rtiUt_$(SOC)_CORELIST
stw_unit_test_DUP_EXAMPLE_LIST += rtiUt

#RTI UT unit test app - rti_dwwd_generate_reset
rti_dwwd_generate_reset_unit_test_app_COMP_LIST = rti_dwwd_generate_reset_unit_test_app
rti_dwwd_generate_reset_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_generate_reset
rti_dwwd_generate_reset_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_generate_reset
rti_dwwd_generate_reset_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_generate_reset_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_generate_reset_unit_test_app_COMP_LIST
export rti_dwwd_generate_reset_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_generate_reset_unit_test_app_CORE_DEPENDENCY
rti_dwwd_generate_reset_unit_test_app_PKG_LIST = rti_dwwd_generate_reset_unit_test_app
rti_dwwd_generate_reset_unit_test_app_INCLUDE = $(rti_dwwd_generate_reset_unit_test_app_PATH)
rti_dwwd_generate_reset_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_generate_reset_unit_test_app_BOARDLIST
rti_dwwd_generate_reset_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_generate_reset_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_generate_reset_unit_test_app
rti_dwwd_generate_reset_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_generate_reset_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_nmi_generation
rti_dwwd_nmi_generation_unit_test_app_COMP_LIST = rti_dwwd_nmi_generation_unit_test_app
rti_dwwd_nmi_generation_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_nmi_generation
rti_dwwd_nmi_generation_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_nmi_generation
rti_dwwd_nmi_generation_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_nmi_generation_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_nmi_generation_unit_test_app_COMP_LIST
export rti_dwwd_nmi_generation_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_nmi_generation_unit_test_app_CORE_DEPENDENCY
rti_dwwd_nmi_generation_unit_test_app_PKG_LIST = rti_dwwd_nmi_generation_unit_test_app
rti_dwwd_nmi_generation_unit_test_app_INCLUDE = $(rti_dwwd_nmi_generation_unit_test_app_PATH)
rti_dwwd_nmi_generation_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_nmi_generation_unit_test_app_BOARDLIST
rti_dwwd_nmi_generation_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_nmi_generation_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_nmi_generation_unit_test_app
rti_dwwd_nmi_generation_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_nmi_generation_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_reaction_change_in_closed_window
rti_dwwd_reaction_change_in_closed_window_unit_test_app_COMP_LIST = rti_dwwd_reaction_change_in_closed_window_unit_test_app
rti_dwwd_reaction_change_in_closed_window_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_reaction_change_in_closed_window
rti_dwwd_reaction_change_in_closed_window_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_reaction_change_in_closed_window
rti_dwwd_reaction_change_in_closed_window_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_reaction_change_in_closed_window_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_COMP_LIST
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_CORE_DEPENDENCY
rti_dwwd_reaction_change_in_closed_window_unit_test_app_PKG_LIST = rti_dwwd_reaction_change_in_closed_window_unit_test_app
rti_dwwd_reaction_change_in_closed_window_unit_test_app_INCLUDE = $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_PATH)
rti_dwwd_reaction_change_in_closed_window_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_BOARDLIST
rti_dwwd_reaction_change_in_closed_window_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_reaction_change_in_closed_window_unit_test_app
rti_dwwd_reaction_change_in_closed_window_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_reaction_change_in_closed_window_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_reaction_change_in_open_window
rti_dwwd_reaction_change_in_open_window_unit_test_app_COMP_LIST = rti_dwwd_reaction_change_in_open_window_unit_test_app
rti_dwwd_reaction_change_in_open_window_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_reaction_change_in_open_window
rti_dwwd_reaction_change_in_open_window_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_reaction_change_in_open_window
rti_dwwd_reaction_change_in_open_window_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_reaction_change_in_open_window_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_reaction_change_in_open_window_unit_test_app_COMP_LIST
export rti_dwwd_reaction_change_in_open_window_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_reaction_change_in_open_window_unit_test_app_CORE_DEPENDENCY
rti_dwwd_reaction_change_in_open_window_unit_test_app_PKG_LIST = rti_dwwd_reaction_change_in_open_window_unit_test_app
rti_dwwd_reaction_change_in_open_window_unit_test_app_INCLUDE = $(rti_dwwd_reaction_change_in_open_window_unit_test_app_PATH)
rti_dwwd_reaction_change_in_open_window_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_reaction_change_in_open_window_unit_test_app_BOARDLIST
rti_dwwd_reaction_change_in_open_window_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_reaction_change_in_open_window_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_reaction_change_in_open_window_unit_test_app
rti_dwwd_reaction_change_in_open_window_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_reaction_change_in_open_window_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_reset_status
rti_dwwd_reset_status_unit_test_app_COMP_LIST = rti_dwwd_reset_status_unit_test_app
rti_dwwd_reset_status_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_reset_status
rti_dwwd_reset_status_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_reset_status
rti_dwwd_reset_status_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_reset_status_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_reset_status_unit_test_app_COMP_LIST
export rti_dwwd_reset_status_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_reset_status_unit_test_app_CORE_DEPENDENCY
rti_dwwd_reset_status_unit_test_app_PKG_LIST = rti_dwwd_reset_status_unit_test_app
rti_dwwd_reset_status_unit_test_app_INCLUDE = $(rti_dwwd_reset_status_unit_test_app_PATH)
rti_dwwd_reset_status_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_reset_status_unit_test_app_BOARDLIST
rti_dwwd_reset_status_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_reset_status_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_reset_status_unit_test_app
rti_dwwd_reset_status_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_reset_status_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_suspend_dsp_core0
rti_dwwd_suspend_dsp_core0_unit_test_app_COMP_LIST = rti_dwwd_suspend_dsp_core0_unit_test_app
rti_dwwd_suspend_dsp_core0_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_suspend_dsp_core0
rti_dwwd_suspend_dsp_core0_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_suspend_dsp_core0
rti_dwwd_suspend_dsp_core0_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_suspend_dsp_core0_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_suspend_dsp_core0_unit_test_app_COMP_LIST
export rti_dwwd_suspend_dsp_core0_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_suspend_dsp_core0_unit_test_app_CORE_DEPENDENCY
rti_dwwd_suspend_dsp_core0_unit_test_app_PKG_LIST = rti_dwwd_suspend_dsp_core0_unit_test_app
rti_dwwd_suspend_dsp_core0_unit_test_app_INCLUDE = $(rti_dwwd_suspend_dsp_core0_unit_test_app_PATH)
rti_dwwd_suspend_dsp_core0_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_suspend_dsp_core0_unit_test_app_BOARDLIST
rti_dwwd_suspend_dsp_core0_unit_test_app_$(SOC)_CORELIST = c66x
export rti_dwwd_suspend_dsp_core0_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_suspend_dsp_core0_unit_test_app
rti_dwwd_suspend_dsp_core0_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_suspend_dsp_core0_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_suspend_dsp_core1
rti_dwwd_suspend_dsp_core1_unit_test_app_COMP_LIST = rti_dwwd_suspend_dsp_core1_unit_test_app
rti_dwwd_suspend_dsp_core1_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_suspend_dsp_core1
rti_dwwd_suspend_dsp_core1_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_suspend_dsp_core1
rti_dwwd_suspend_dsp_core1_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_suspend_dsp_core1_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_suspend_dsp_core1_unit_test_app_COMP_LIST
export rti_dwwd_suspend_dsp_core1_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_suspend_dsp_core1_unit_test_app_CORE_DEPENDENCY
rti_dwwd_suspend_dsp_core1_unit_test_app_PKG_LIST = rti_dwwd_suspend_dsp_core1_unit_test_app
rti_dwwd_suspend_dsp_core1_unit_test_app_INCLUDE = $(rti_dwwd_suspend_dsp_core1_unit_test_app_PATH)
rti_dwwd_suspend_dsp_core1_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_suspend_dsp_core1_unit_test_app_BOARDLIST
rti_dwwd_suspend_dsp_core1_unit_test_app_$(SOC)_CORELIST = c66x
export rti_dwwd_suspend_dsp_core1_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_suspend_dsp_core1_unit_test_app
rti_dwwd_suspend_dsp_core1_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_suspend_dsp_core1_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_suspend_eve
rti_dwwd_suspend_eve_unit_test_app_COMP_LIST = rti_dwwd_suspend_eve_unit_test_app
rti_dwwd_suspend_eve_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_suspend_eve
rti_dwwd_suspend_eve_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_suspend_eve
rti_dwwd_suspend_eve_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_suspend_eve_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_suspend_eve_unit_test_app_COMP_LIST
export rti_dwwd_suspend_eve_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_suspend_eve_unit_test_app_CORE_DEPENDENCY
rti_dwwd_suspend_eve_unit_test_app_PKG_LIST = rti_dwwd_suspend_eve_unit_test_app
rti_dwwd_suspend_eve_unit_test_app_INCLUDE = $(rti_dwwd_suspend_eve_unit_test_app_PATH)
rti_dwwd_suspend_eve_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_suspend_eve_unit_test_app_BOARDLIST
rti_dwwd_suspend_eve_unit_test_app_$(SOC)_CORELIST = arp32_1
export rti_dwwd_suspend_eve_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_suspend_eve_unit_test_app
rti_dwwd_suspend_eve_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_suspend_eve_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_suspend_ipu_core0
rti_dwwd_suspend_ipu_core0_unit_test_app_COMP_LIST = rti_dwwd_suspend_ipu_core0_unit_test_app
rti_dwwd_suspend_ipu_core0_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_suspend_ipu_core0
rti_dwwd_suspend_ipu_core0_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_suspend_ipu_core0
rti_dwwd_suspend_ipu_core0_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_suspend_ipu_core0_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_suspend_ipu_core0_unit_test_app_COMP_LIST
export rti_dwwd_suspend_ipu_core0_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_suspend_ipu_core0_unit_test_app_CORE_DEPENDENCY
rti_dwwd_suspend_ipu_core0_unit_test_app_PKG_LIST = rti_dwwd_suspend_ipu_core0_unit_test_app
rti_dwwd_suspend_ipu_core0_unit_test_app_INCLUDE = $(rti_dwwd_suspend_ipu_core0_unit_test_app_PATH)
rti_dwwd_suspend_ipu_core0_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_suspend_ipu_core0_unit_test_app_BOARDLIST
rti_dwwd_suspend_ipu_core0_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_suspend_ipu_core0_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_suspend_ipu_core0_unit_test_app
rti_dwwd_suspend_ipu_core0_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_suspend_ipu_core0_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_suspend_ipu_core1
rti_dwwd_suspend_ipu_core1_unit_test_app_COMP_LIST = rti_dwwd_suspend_ipu_core1_unit_test_app
rti_dwwd_suspend_ipu_core1_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_suspend_ipu_core1
rti_dwwd_suspend_ipu_core1_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_suspend_ipu_core1
rti_dwwd_suspend_ipu_core1_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_suspend_ipu_core1_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_suspend_ipu_core1_unit_test_app_COMP_LIST
export rti_dwwd_suspend_ipu_core1_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_suspend_ipu_core1_unit_test_app_CORE_DEPENDENCY
rti_dwwd_suspend_ipu_core1_unit_test_app_PKG_LIST = rti_dwwd_suspend_ipu_core1_unit_test_app
rti_dwwd_suspend_ipu_core1_unit_test_app_INCLUDE = $(rti_dwwd_suspend_ipu_core1_unit_test_app_PATH)
rti_dwwd_suspend_ipu_core1_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_suspend_ipu_core1_unit_test_app_BOARDLIST
rti_dwwd_suspend_ipu_core1_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_suspend_ipu_core1_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_suspend_ipu_core1_unit_test_app
rti_dwwd_suspend_ipu_core1_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_suspend_ipu_core1_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_100
rti_dwwd_wz_100_unit_test_app_COMP_LIST = rti_dwwd_wz_100_unit_test_app
rti_dwwd_wz_100_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_100
rti_dwwd_wz_100_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_100
rti_dwwd_wz_100_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_100_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_100_unit_test_app_COMP_LIST
export rti_dwwd_wz_100_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_100_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_100_unit_test_app_PKG_LIST = rti_dwwd_wz_100_unit_test_app
rti_dwwd_wz_100_unit_test_app_INCLUDE = $(rti_dwwd_wz_100_unit_test_app_PATH)
rti_dwwd_wz_100_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_100_unit_test_app_BOARDLIST
rti_dwwd_wz_100_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_100_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_100_unit_test_app
rti_dwwd_wz_100_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_100_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_12_5
rti_dwwd_wz_12_5_unit_test_app_COMP_LIST = rti_dwwd_wz_12_5_unit_test_app
rti_dwwd_wz_12_5_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_12_5
rti_dwwd_wz_12_5_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_12_5
rti_dwwd_wz_12_5_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_12_5_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_12_5_unit_test_app_COMP_LIST
export rti_dwwd_wz_12_5_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_12_5_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_12_5_unit_test_app_PKG_LIST = rti_dwwd_wz_12_5_unit_test_app
rti_dwwd_wz_12_5_unit_test_app_INCLUDE = $(rti_dwwd_wz_12_5_unit_test_app_PATH)
rti_dwwd_wz_12_5_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_12_5_unit_test_app_BOARDLIST
rti_dwwd_wz_12_5_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_12_5_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_12_5_unit_test_app
rti_dwwd_wz_12_5_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_12_5_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_25
rti_dwwd_wz_25_unit_test_app_COMP_LIST = rti_dwwd_wz_25_unit_test_app
rti_dwwd_wz_25_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_25
rti_dwwd_wz_25_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_25
rti_dwwd_wz_25_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_25_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_25_unit_test_app_COMP_LIST
export rti_dwwd_wz_25_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_25_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_25_unit_test_app_PKG_LIST = rti_dwwd_wz_25_unit_test_app
rti_dwwd_wz_25_unit_test_app_INCLUDE = $(rti_dwwd_wz_25_unit_test_app_PATH)
rti_dwwd_wz_25_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_25_unit_test_app_BOARDLIST
rti_dwwd_wz_25_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_25_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_25_unit_test_app
rti_dwwd_wz_25_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_25_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_3_125
rti_dwwd_wz_3_125_unit_test_app_COMP_LIST = rti_dwwd_wz_3_125_unit_test_app
rti_dwwd_wz_3_125_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_3_125
rti_dwwd_wz_3_125_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_3_125
rti_dwwd_wz_3_125_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_3_125_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_3_125_unit_test_app_COMP_LIST
export rti_dwwd_wz_3_125_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_3_125_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_3_125_unit_test_app_PKG_LIST = rti_dwwd_wz_3_125_unit_test_app
rti_dwwd_wz_3_125_unit_test_app_INCLUDE = $(rti_dwwd_wz_3_125_unit_test_app_PATH)
rti_dwwd_wz_3_125_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_3_125_unit_test_app_BOARDLIST
rti_dwwd_wz_3_125_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_3_125_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_3_125_unit_test_app
rti_dwwd_wz_3_125_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_3_125_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_50
rti_dwwd_wz_50_unit_test_app_COMP_LIST = rti_dwwd_wz_50_unit_test_app
rti_dwwd_wz_50_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_50
rti_dwwd_wz_50_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_50
rti_dwwd_wz_50_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_50_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_50_unit_test_app_COMP_LIST
export rti_dwwd_wz_50_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_50_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_50_unit_test_app_PKG_LIST = rti_dwwd_wz_50_unit_test_app
rti_dwwd_wz_50_unit_test_app_INCLUDE = $(rti_dwwd_wz_50_unit_test_app_PATH)
rti_dwwd_wz_50_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_50_unit_test_app_BOARDLIST
rti_dwwd_wz_50_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_50_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_50_unit_test_app
rti_dwwd_wz_50_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_50_unit_test_app_SBL_APPIMAGEGEN

#RTI UT unit test app - rti_dwwd_wz_6_25
rti_dwwd_wz_6_25_unit_test_app_COMP_LIST = rti_dwwd_wz_6_25_unit_test_app
rti_dwwd_wz_6_25_unit_test_app_RELPATH = ti/drv/stw_lld/unit_test/rtiUt/rti_dwwd_wz_6_25
rti_dwwd_wz_6_25_unit_test_app_PATH = $(PDK_STW_UNIT_TEST_COMP_PATH)/rtiUt/rti_dwwd_wz_6_25
rti_dwwd_wz_6_25_unit_test_app_BOARD_DEPENDENCY = yes
rti_dwwd_wz_6_25_unit_test_app_CORE_DEPENDENCY = yes
export rti_dwwd_wz_6_25_unit_test_app_COMP_LIST
export rti_dwwd_wz_6_25_unit_test_app_BOARD_DEPENDENCY
export rti_dwwd_wz_6_25_unit_test_app_CORE_DEPENDENCY
rti_dwwd_wz_6_25_unit_test_app_PKG_LIST = rti_dwwd_wz_6_25_unit_test_app
rti_dwwd_wz_6_25_unit_test_app_INCLUDE = $(rti_dwwd_wz_6_25_unit_test_app_PATH)
rti_dwwd_wz_6_25_unit_test_app_BOARDLIST = tda3xx-evm
export rti_dwwd_wz_6_25_unit_test_app_BOARDLIST
rti_dwwd_wz_6_25_unit_test_app_$(SOC)_CORELIST = ipu1_0
export rti_dwwd_wz_6_25_unit_test_app_$(SOC)_CORELIST
stw_unit_test_EXAMPLE_LIST += rti_dwwd_wz_6_25_unit_test_app
rti_dwwd_wz_6_25_unit_test_app_SBL_APPIMAGEGEN = yes
export rti_dwwd_wz_6_25_unit_test_app_SBL_APPIMAGEGEN

export stw_unit_test_LIB_LIST
export stw_unit_test_EXAMPLE_LIST
export stw_unit_test_DUP_EXAMPLE_LIST

stw_unit_test_component_make_include := 1
endif
