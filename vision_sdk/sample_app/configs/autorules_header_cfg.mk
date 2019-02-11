

#
# This file has override conditions
#
# If user gives a conflicting config,
# logic in this file will override to a logically correct config
#

# Default platform
# Supported values: tda2xx-evm, tda2px-evm, tda3xx-evm, tda3xx-rvp
ifeq ($(PLATFORM), )
    ifeq ($(VSDK_BOARD_TYPE), TDA2XX_EVM)
        PLATFORM := tda2xx-evm
    endif
    ifeq ($(VSDK_BOARD_TYPE), TDA2PX_EVM)
        PLATFORM := tda2px-evm
    endif
    ifeq ($(VSDK_BOARD_TYPE), TDA2XX_RVP)
        PLATFORM := tda2xx-rvp
    endif
    ifeq ($(VSDK_BOARD_TYPE), TDA3XX_EVM)
        PLATFORM := tda3xx-evm
    endif
    ifeq ($(VSDK_BOARD_TYPE), TDA3XX_RVP)
        PLATFORM := tda3xx-rvp
    endif
    ifeq ($(VSDK_BOARD_TYPE), TDA2EX_EVM)
        PLATFORM := tda2ex-evm
    endif
endif

PDK_BOARD := $(PLATFORM)
PDK_SBL_CORE := a15_0
ifeq ($(PLATFORM), $(filter $(PLATFORM),tda2xx-evm))
    PDK_SBL_CORE := a15_0
    ifeq ($(RADAR_ONLY),yes)
        ifeq ($(RADAR_BOARD),none)
            PDK_BOARD := tda2xx-evm-radar
        endif
        ifeq ($(RADAR_BOARD),TDA2XX_CASCADE_RADAR)
            PDK_BOARD := tda2xx-cascade-radar
        endif
    endif
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM),tda2px-evm))
    PDK_SBL_CORE := a15_0
    ifeq ($(RADAR_ONLY),yes)
        PDK_BOARD := tda2px-evm-radar
    endif
endif
ifeq ($(PLATFORM), tda2xx-rvp)
    PDK_SBL_CORE := a15_0
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda3xx-evm tda3xx-rvp))
    PDK_SBL_CORE := ipu1_0
    ifeq ($(RADAR_ONLY),yes)
        ifeq ($(RADAR_BOARD),none)
            PDK_BOARD := tda3xx-evm-radar
        endif
        ifeq ($(RADAR_BOARD),TDA3XX_AR12_VIB_DAB_BOOSTER)
            PDK_BOARD := tda3xx-ar12-booster
        endif
        ifeq ($(RADAR_BOARD),TDA3XX_AR12_ALPS)
            PDK_BOARD := tda3xx-ar12-alps
        endif
        ifeq ($(RADAR_BOARD),TDA3XX_RADAR_RVP)
            PDK_BOARD := tda3xx-ar12-rvp
        endif
    endif
endif
ifeq ($(PLATFORM), $(filter $(PLATFORM), tda2ex-evm))
    ifeq ($(TDA2EX_ETHSRV_BOARD),yes)
        ifeq ($(NDK_PROC_TO_USE),none)
            NDK_PROC_TO_USE=ipu1_1
        endif
        ifeq ($(AVB_INCLUDE),none)
            AVB_INCLUDE=yes
        endif
        PDK_BOARD := tda2ex-eth-srv
    endif
endif
