
INCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/alg_plugins/iss_aewb/inc
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/alg_plugins/iss_aewb $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/alg_plugins/iss_aewb/src

SRCS_$(IPU_PRIMARY_CORE) += issAewb1Link_algPlugin.c algTIaewb.c TIawbCalcData_default.c ae_ti.c dcc_ti.c



