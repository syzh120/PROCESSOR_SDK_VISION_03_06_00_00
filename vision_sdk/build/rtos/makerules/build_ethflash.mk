IPADDR ?= 172.24.190.29
#Available options SBL_QSPI SBL_QSPI_SD SBL_SD
MODE ?= SBL_QSPI_SD
#Available options low nom od high
OPPMODE ?= nom

ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2xx-evm tda2px-evm tda2ex-evm tda2xx-rvp))
CORE = a15_0
endif

ifeq ($(PLATFORM), $(filter $(PLATFORM), tda3xx-evm tda3xx-rvp))
CORE = ipu1_0
endif

ifeq ($(MODE),SBL_QSPI)
SBLIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/sbl/qspi/opp_$(OPPMODE)/$(PDK_BOARD)/sbl_qspi_opp_$(OPPMODE)_$(CORE)_$(PROFILE).tiimage
APPIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/sbl_boot/AppImage_BE
endif

ifeq ($(MODE),SBL_QSPI_SD)
SBLIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/sbl/qspi_sd/opp_$(OPPMODE)/$(PDK_BOARD)/sbl_qspi_sd_opp_$(OPPMODE)_$(CORE)_$(PROFILE).tiimage
APPIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/sbl_boot/AppImage
endif

ifeq ($(MODE),SBL_SD)
SBLIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/sbl/sd/opp_$(OPPMODE)/$(PDK_BOARD)/MLO
APPIMAGE=$(vision_sdk_PATH)/binaries/$(MAKEAPPNAME)/$(MAKECONFIG)/vision_sdk/bin/$(PLATFORM)/sbl_boot/AppImage
endif

ifeq ($(BUILD_OS),Linux)
NETWORK_CTRL=$(vision_sdk_PATH)/apps/tools/network_tools/bin/network_ctrl.out
else
NETWORK_CTRL=$(vision_sdk_PATH)/apps/tools/network_tools/bin/network_ctrl.exe
endif


eth_flash_appimage:
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd qspi_wr 80000 $(APPIMAGE)
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd sys_reset

eth_flash_sbl:
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd qspi_wr 0 $(SBLIMAGE)

eth_writesd_appimage:
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd mmc_wr_appimage $(APPIMAGE)
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd sys_reset

eth_writesd_sbl:
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd mmc_wr_sbl $(SBLIMAGE)

eth_reset:
	$(NETWORK_CTRL) --ipaddr $(IPADDR) --cmd sys_reset
