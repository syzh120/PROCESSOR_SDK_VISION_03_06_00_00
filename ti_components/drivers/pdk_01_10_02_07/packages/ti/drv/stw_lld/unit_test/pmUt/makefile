#
# This file is the makefile for building all PM UT apps
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

.PHONY : all clean

all:
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_autocg_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_autocg_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_autocg_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_autocg_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_idle_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_idle_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_idle_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_idle_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_pdoff_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_pdoff_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_pdoff_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_pdoff_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pm_leakage_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pm_leakage_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pm_leakage_unit_test_app_PATH)
	$(MAKE) -C $(pm_leakage_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmhal_dpll_core_sysclk2_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmhal_dpll_core_sysclk2_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmhal_dpll_core_sysclk2_unit_test_app_PATH)
	$(MAKE) -C $(pmhal_dpll_core_sysclk2_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmhal_coldreset_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmhal_coldreset_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmhal_coldreset_unit_test_app_PATH)
	$(MAKE) -C $(pmhal_coldreset_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmhal_warmreset_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmhal_warmreset_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmhal_warmreset_unit_test_app_PATH)
	$(MAKE) -C $(pmhal_warmreset_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmhal_vm_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmhal_vm_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmhal_vm_unit_test_app_PATH)
	$(MAKE) -C $(pmhal_vm_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_clkrate_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_clkrate_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_clkrate_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_clkrate_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_syscfg_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_syscfg_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_syscfg_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_syscfg_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_videopll_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_videopll_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_videopll_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_videopll_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(pmlib_videopllcalc_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(pmlib_videopllcalc_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(pmlib_videopllcalc_unit_test_app_PATH)
	$(MAKE) -C $(pmlib_videopllcalc_unit_test_app_PATH) sbl_appimagegen
  endif
endif

clean:
	$(MAKE) -C $(pmlib_autocg_unit_test_app_PATH)               clean
	$(MAKE) -C $(pmlib_idle_unit_test_app_PATH)                 clean
	$(MAKE) -C $(pmlib_pdoff_unit_test_app_PATH)                clean
	$(MAKE) -C $(pm_leakage_unit_test_app_PATH)                 clean
	$(MAKE) -C $(pmhal_dpll_core_sysclk2_unit_test_app_PATH)    clean
	$(MAKE) -C $(pmhal_coldreset_unit_test_app_PATH)            clean
	$(MAKE) -C $(pmhal_warmreset_unit_test_app_PATH)            clean
	$(MAKE) -C $(pmhal_vm_unit_test_app_PATH)                   clean
	$(MAKE) -C $(pmlib_clkrate_unit_test_app_PATH)              clean
	$(MAKE) -C $(pmlib_syscfg_unit_test_app_PATH)               clean
	$(MAKE) -C $(pmlib_videopll_unit_test_app_PATH)             clean
	$(MAKE) -C $(pmlib_videopllcalc_unit_test_app_PATH)         clean
