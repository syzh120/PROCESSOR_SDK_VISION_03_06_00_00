#
# This file is the makefile for building all SBL boot modes.
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

.PHONY : all clean

SBL_BUILD_OPTIONS  = CORE=$(sbl_auto_$(SOC)_CORELIST)
SBL_BUILD_OPTIONS += SBL_CONFIG=$(SBL_CONFIG)
SBL_BUILD_OPTIONS += SBL_OPT_MODE=$(SBL_OPT_MODE)
SBL_BUILD_OPTIONS += SBL_TRACE_MODE=$(SBL_TRACE_MODE)
SBL_BUILD_OPTIONS += SBL_BUILD_MODE=$(SBL_BUILD_MODE)
SBL_BUILD_OPTIONS += EMIFMODE=$(EMIFMODE)
SBL_BUILD_OPTIONS += FORCE_OPPMODE=$(FORCE_OPPMODE)

all:
	$(foreach bootmode, $(SBL_BOOTMODE_LIST_$(SOC)),\
	$(MAKE) -C $(sbl_PATH)              BOOTMODE=$(bootmode) OPPMODE=opp_nom $(SBL_BUILD_OPTIONS);\
	$(MAKE) -C $(sbl_PATH) sbl_imagegen BOOTMODE=$(bootmode) OPPMODE=opp_nom $(SBL_BUILD_OPTIONS);\
	)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
	$(MAKE) -C $(sbl_PATH)              BOOTMODE=sd          OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
	$(MAKE) -C $(sbl_PATH) sbl_imagegen BOOTMODE=sd          OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
	$(MAKE) -C $(sbl_PATH)              BOOTMODE=qspi_sd     OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
	$(MAKE) -C $(sbl_PATH) sbl_imagegen BOOTMODE=qspi_sd     OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x tda2px tda2ex tda2xx))
	$(MAKE) -C $(sbl_PATH)              BOOTMODE=uart        OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TYPE=mflash
	$(MAKE) -C $(sbl_PATH) sbl_imagegen BOOTMODE=uart        OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TYPE=mflash
endif

clean:
	$(foreach bootmode, $(SBL_BOOTMODE_LIST_$(SOC)),\
	$(MAKE) -C $(sbl_PATH) clean        BOOTMODE=$(bootmode) OPPMODE=opp_nom $(SBL_BUILD_OPTIONS);\
	)
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
	$(MAKE) -C $(sbl_PATH) clean        BOOTMODE=sd          OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
	$(MAKE) -C $(sbl_PATH) clean        BOOTMODE=qspi_sd     OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TEST_AUTO=yes
endif
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x tda2px tda2ex tda2xx))
	$(MAKE) -C $(sbl_PATH) clean        BOOTMODE=uart        OPPMODE=opp_nom $(SBL_BUILD_OPTIONS) SBL_TYPE=mflash
endif
