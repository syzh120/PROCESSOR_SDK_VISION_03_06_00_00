#
#            This file takes the generated rprc formats of eve binaries and 
#            creates an AppImage out of it. This AppImage is used to generate
#            utils_eve_firmware.h included by ipu based eveloader module. 


ifeq ($(BUILD_MACHINE),64BIT)
MULTICOREIMAGEGEN:=$(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/tools/MulticoreImageGen64.out
BIN2CHEADERGEN:=$(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/tools/bin2c64.out
endif
ifeq ($(BUILD_MACHINE),32BIT)
MULTICOREIMAGEGEN:=$(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/tools/MulticoreImageGen32.out
BIN2CHEADERGEN:=$(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/tools/bin2c32.out
endif

EVE_FIRMWARE_HEADER:=$(vision_sdk_PATH)/links_fw/src/rtos/utils_common/src/eveloader/utils_eve_firmware.h
ENDIANNESS:=LE
BINDIR:=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)
OUTIMAGE:=$(BINDIR)/AppImage
INPUTRPRCS:=
EVE1_ID:=10
EVE2_ID:=11
EVE3_ID:=12
EVE4_ID:=13
EVE1_RPRC_PATH:=$(BINDIR)/vision_sdk_arp32_1_$(PROFILE_arp32_1).xearp32F.rprc 
EVE2_RPRC_PATH:=$(BINDIR)/vision_sdk_arp32_2_$(PROFILE_arp32_2).xearp32F.rprc 
EVE3_RPRC_PATH:=$(BINDIR)/vision_sdk_arp32_3_$(PROFILE_arp32_3).xearp32F.rprc 
EVE4_RPRC_PATH:=$(BINDIR)/vision_sdk_arp32_4_$(PROFILE_arp32_4).xearp32F.rprc 
# for tda2xx
DEV_ID:=55 

ifeq ($(PROC_EVE1_INCLUDE), yes)
INPUTRPRCS += $(EVE1_ID) $(EVE1_RPRC_PATH) 
endif

ifeq ($(PROC_EVE2_INCLUDE), yes)
INPUTRPRCS += $(EVE2_ID) $(EVE2_RPRC_PATH) 
endif

ifeq ($(PROC_EVE3_INCLUDE), yes)
INPUTRPRCS += $(EVE3_ID) $(EVE3_RPRC_PATH) 
endif

ifeq ($(PROC_EVE4_INCLUDE), yes)
INPUTRPRCS += $(EVE4_ID) $(EVE4_RPRC_PATH) 
endif

all:
	$(MULTICOREIMAGEGEN) $(ENDIANNESS) $(DEV_ID) $(OUTIMAGE) $(INPUTRPRCS)
	$(BIN2CHEADERGEN) $(OUTIMAGE) >	$(EVE_FIRMWARE_HEADER)


