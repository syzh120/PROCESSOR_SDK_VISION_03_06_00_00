#
# This file is the makefile for building all RTI UT apps
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

.PHONY : all clean

all:
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_generate_reset_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_generate_reset_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_generate_reset_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_generate_reset_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_nmi_generation_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_nmi_generation_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_nmi_generation_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_nmi_generation_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_reaction_change_in_open_window_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_reaction_change_in_open_window_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_reaction_change_in_open_window_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_reaction_change_in_open_window_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_reset_status_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_reset_status_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_reset_status_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_reset_status_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_suspend_dsp_core0_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_suspend_dsp_core0_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core0_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core0_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_suspend_dsp_core1_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_suspend_dsp_core1_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core1_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core1_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_suspend_eve_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_suspend_eve_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_suspend_eve_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_suspend_eve_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_suspend_ipu_core0_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_suspend_ipu_core0_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core0_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core0_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_suspend_ipu_core1_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_suspend_ipu_core1_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core1_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core1_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_100_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_100_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_100_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_100_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_12_5_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_12_5_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_12_5_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_12_5_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_25_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_25_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_25_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_25_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_3_125_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_3_125_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_3_125_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_3_125_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_50_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_50_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_50_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_50_unit_test_app_PATH) sbl_appimagegen
  endif
endif
ifeq ($(BOARD),$(filter $(BOARD), $(rti_dwwd_wz_6_25_unit_test_app_BOARDLIST)))
  ifeq ($(CORE),$(filter $(CORE), $(rti_dwwd_wz_6_25_unit_test_app_$(SOC)_CORELIST)))
	$(MAKE) -C $(rti_dwwd_wz_6_25_unit_test_app_PATH)
	$(MAKE) -C $(rti_dwwd_wz_6_25_unit_test_app_PATH) sbl_appimagegen
  endif
endif

clean:
	$(MAKE) -C $(rti_dwwd_generate_reset_unit_test_app_PATH)                    clean
	$(MAKE) -C $(rti_dwwd_nmi_generation_unit_test_app_PATH)                    clean
	$(MAKE) -C $(rti_dwwd_reaction_change_in_closed_window_unit_test_app_PATH)  clean
	$(MAKE) -C $(rti_dwwd_reaction_change_in_open_window_unit_test_app_PATH)    clean
	$(MAKE) -C $(rti_dwwd_reset_status_unit_test_app_PATH)                      clean
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core0_unit_test_app_PATH)                 clean
	$(MAKE) -C $(rti_dwwd_suspend_dsp_core1_unit_test_app_PATH)                 clean
	$(MAKE) -C $(rti_dwwd_suspend_eve_unit_test_app_PATH)                       clean
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core0_unit_test_app_PATH)                 clean
	$(MAKE) -C $(rti_dwwd_suspend_ipu_core1_unit_test_app_PATH)                 clean
	$(MAKE) -C $(rti_dwwd_wz_100_unit_test_app_PATH)                            clean
	$(MAKE) -C $(rti_dwwd_wz_12_5_unit_test_app_PATH)                           clean
	$(MAKE) -C $(rti_dwwd_wz_25_unit_test_app_PATH)                             clean
	$(MAKE) -C $(rti_dwwd_wz_3_125_unit_test_app_PATH)                          clean
	$(MAKE) -C $(rti_dwwd_wz_50_unit_test_app_PATH)                             clean
	$(MAKE) -C $(rti_dwwd_wz_6_25_unit_test_app_PATH)                           clean
