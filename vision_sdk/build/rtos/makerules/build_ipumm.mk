# File name: build_ipumm.mk
#            This file builds the IPUMM libs.

ipumm_build:
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda2xx-rvp tda2ex-evm))
ifeq ($(A15_TARGET_OS),$(filter $(A15_TARGET_OS), Linux Qnx))
	$(MAKE) unconfig -C $(mm_PATH)/
	$(MAKE) vayu_smp_config -C $(mm_PATH)/
	$(MAKE) info -C $(mm_PATH)/ PROFILE=$(IPUMM_TARGET) IPCSRC=$(ipc_PATH) BIOSTOOLSROOT=$(TI_SW_ROOT)/os_tools TMS470CGTOOLPATH=$(CODEGEN_PATH_M4) BIOSPROD=$(bios_PATH) XDAISPROD=$(xdais_PATH) XDCDIST_TREE=$(xdc_PATH) CEPROD=$(ce_PATH) FCPROD=$(fc_PATH)
	$(MAKE) $(IPUMM_CMD) -C $(mm_PATH)/ PROFILE=$(IPUMM_TARGET) IPCSRC=$(ipc_PATH) BIOSTOOLSROOT=$(TI_SW_ROOT)/os_tools TMS470CGTOOLPATH=$(CODEGEN_PATH_M4) BIOSPROD=$(bios_PATH) XDAISPROD=$(xdais_PATH) XDCDIST_TREE=$(xdc_PATH) CEPROD=$(ce_PATH) FCPROD=$(fc_PATH)
endif
endif

ipumm:
	$(MAKE) -fbuild_ipumm.mk ipumm_build IPUMM_TARGET=release IPUMM_CMD=lib

ipumm_clean:
	$(MAKE) -fbuild_ipumm.mk ipumm_build IPUMM_TARGET=release IPUMM_CMD=clean
