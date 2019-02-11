SD_CARD_DRIVE=

# This is disabled as decryption software is not optimized and results in
# significant increase in boot-time. To try this feature, make sure
# SECURITYLIB_APPIMAGE_DECRYPTION is defined in PDK in
# pdk/packages/ti/drv/security/include/tda3xx/tda3xx_gp_prime.h
SECURITYLIB_APPIMAGE_DECRYPTION=no

CRC_CALCULATE=no

ifeq ($(HS_DEVICE),yes)
OUT_PATH=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/sbl_boot_hs
else
OUT_PATH=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/sbl_boot
endif

PDK_TOOLS=$(pdk_PATH)/packages/ti/boot/sbl_auto/tools/

ifeq ($(OS),Windows_NT)
OUT2RPRC=$(PDK_TOOLS)/out2rprc/out2rprc.exe
MULTICORE_IMAGE_GEN=$(PDK_TOOLS)/multicore_image_generator/v2/MulticoreImageGen.exe
CRC_MULTICORE_IMAGE_GEN=$(PDK_TOOLS)/crc_multicore_image/crc_multicore_image.exe
else
OUT2RPRC=mono $(PDK_TOOLS)/out2rprc/out2rprc.exe
MULTICORE_IMAGE_GEN=$(PDK_TOOLS)/multicore_image_generator/v2/MulticoreImageGen
CRC_MULTICORE_IMAGE_GEN=$(PDK_TOOLS)/crc_multicore_image/crc_multicore_image
endif

ifeq ($(SOC),tda2xx)
DEV_ID=55
ifeq ($(DUAL_A15_SMP_BIOS),yes)
MPU_CPU0_ID=14
else
MPU_CPU0_ID=0
endif
IPU1_CPU0_ID=2
IPU1_CPU1_ID=3
IPU2_CPU_SMP_ID=7
DSP1_ID=8
DSP2_ID=9
EVE1_ID=10
EVE2_ID=11
EVE3_ID=12
EVE4_ID=13
MPU_SMP_ID=14
CRC_CALCULATE=no
endif

ifeq ($(SOC),tda2px)
DEV_ID=88
ifeq ($(DUAL_A15_SMP_BIOS),yes)
MPU_CPU0_ID=14
else
MPU_CPU0_ID=0
endif
IPU1_CPU0_ID=2
IPU1_CPU1_ID=3
IPU2_CPU_SMP_ID=7
DSP1_ID=8
DSP2_ID=9
EVE1_ID=10
EVE2_ID=11
MPU_SMP_ID=14
CRC_CALCULATE=no
endif

ifeq ($(SOC),tda3xx)
DEV_ID=77
ifeq ($(IPU1_SMP_BIOS),yes)
IPU1_CPU_SMP_ID=14
endif
IPU1_CPU0_ID=2
IPU1_CPU1_ID=3
DSP1_ID=6
DSP2_ID=7
EVE1_ID=8
ifeq ($(FAST_BOOT_INCLUDE),yes)
CRC_CALCULATE=yes
endif
#Force no-crc for TDA3x GP PRIME devices
ifeq ($(HS_DEVICE),yes)
CRC_CALCULATE=no
endif
endif

ifeq ($(SOC),tda2ex)
DEV_ID=66
MPU_CPU0_ID=0
IPU1_CPU0_ID=2
IPU1_CPU1_ID=3
IPU2_CPU_SMP_ID=7
DSP1_ID=8
CRC_CALCULATE=no
endif

App_MPU_CPU0=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_a15_0_$(PROFILE_a15_0).xa15fg
App_IPU1_CPU0=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4
App_IPU1_CPU1=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_1_$(PROFILE_ipu1_1).xem4
App_IPU1_CPU_SMP=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu1_0_$(PROFILE_ipu1_0).xem4
App_IPU2_CPU_SMP=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_ipu2_$(PROFILE_ipu2).xem4
App_DSP1=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_1_$(PROFILE_c66xdsp_1).xe66
App_DSP2=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_c66xdsp_2_$(PROFILE_c66xdsp_2).xe66
App_EVE1=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_arp32_1_$(PROFILE_arp32_1).xearp32F
App_EVE2=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_arp32_2_$(PROFILE_arp32_2).xearp32F
App_EVE3=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_arp32_3_$(PROFILE_arp32_3).xearp32F
App_EVE4=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/vision_sdk_arp32_4_$(PROFILE_arp32_4).xearp32F

INPUT_RPRC=
INPUT_RPRC_UC_EARLY=
INPUT_RPRC_UC_LATE=
ifeq ($(PROC_A15_0_INCLUDE),yes)
INPUT_RPRC+=$(MPU_CPU0_ID) $(App_MPU_CPU0).rprc
endif

ifeq ($(IPU1_SMP_BIOS),yes)
INPUT_RPRC+=$(IPU1_CPU_SMP_ID) $(App_IPU1_CPU_SMP).rprc
INPUT_RPRC_UC_EARLY+=$(IPU1_CPU_SMP_ID) $(App_IPU1_CPU_SMP).rprc
else
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
INPUT_RPRC+=$(IPU1_CPU0_ID) $(App_IPU1_CPU0).rprc
INPUT_RPRC_UC_EARLY+=$(IPU1_CPU0_ID) $(App_IPU1_CPU0).rprc
endif
ifeq ($(PROC_IPU1_1_INCLUDE),yes)
INPUT_RPRC+=$(IPU1_CPU1_ID) $(App_IPU1_CPU1).rprc
INPUT_RPRC_UC_EARLY+=$(IPU1_CPU1_ID) $(App_IPU1_CPU1).rprc
endif
endif

ifeq ($(PROC_IPU2_INCLUDE),yes)
INPUT_RPRC+=$(IPU2_CPU_SMP_ID) $(App_IPU2_CPU_SMP).rprc
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
INPUT_RPRC+=$(DSP1_ID) $(App_DSP1).rprc
INPUT_RPRC_UC_LATE+=$(DSP1_ID) $(App_DSP1).rprc
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
INPUT_RPRC+=$(DSP2_ID) $(App_DSP2).rprc
INPUT_RPRC_UC_LATE+=$(DSP2_ID) $(App_DSP2).rprc
endif
ifeq ($(PROC_EVE1_INCLUDE),yes)
INPUT_RPRC+=$(EVE1_ID) $(App_EVE1).rprc
INPUT_RPRC_UC_LATE+=$(EVE1_ID) $(App_EVE1).rprc
endif
ifeq ($(PROC_EVE2_INCLUDE),yes)
INPUT_RPRC+=$(EVE2_ID) $(App_EVE2).rprc
endif
ifeq ($(PROC_EVE3_INCLUDE),yes)
INPUT_RPRC+=$(EVE3_ID) $(App_EVE3).rprc
endif
ifeq ($(PROC_EVE4_INCLUDE),yes)
INPUT_RPRC+=$(EVE4_ID) $(App_EVE4).rprc
endif

all:
	-$(MKDIR) -p $(OUT_PATH)
	@echo '# Creating Vision SDK AppImage ...'
ifeq ($(PROC_A15_0_INCLUDE),yes)
	@echo '# Including A15 ...'
	$(OUT2RPRC) $(App_MPU_CPU0) $(App_MPU_CPU0).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_MPU_CPU0).rprc
endif
ifeq ($(IPU1_SMP_BIOS),yes)
	@echo '# Including IPU1 SMP ...'
	$(OUT2RPRC) $(App_IPU1_CPU_SMP) $(App_IPU1_CPU_SMP).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_IPU1_CPU_SMP).rprc
else
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	@echo '# Including IPU1-0 ...'
	$(OUT2RPRC) $(App_IPU1_CPU0) $(App_IPU1_CPU0).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_IPU1_CPU0).rprc
endif
ifeq ($(PROC_IPU1_1_INCLUDE),yes)
	@echo '# Including IPU1-1 ...'
	$(OUT2RPRC) $(App_IPU1_CPU1) $(App_IPU1_CPU1).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_IPU1_CPU1).rprc
endif
endif
ifeq ($(PROC_IPU2_INCLUDE),yes)
	@echo '# Including IPU2 ...'
	$(OUT2RPRC) $(App_IPU2_CPU_SMP) $(App_IPU2_CPU_SMP).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_IPU2_CPU_SMP).rprc
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
	@echo '# Including DSP1 ...'
	$(OUT2RPRC) $(App_DSP1) $(App_DSP1).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_DSP1).rprc
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
	@echo '# Including DSP2 ...'
	$(OUT2RPRC) $(App_DSP2) $(App_DSP2).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_DSP2).rprc
endif
ifeq ($(PROC_EVE1_INCLUDE),yes)
	@echo '# Including EVE1 ...'
	$(OUT2RPRC) $(App_EVE1) $(App_EVE1).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_EVE1).rprc
endif
ifeq ($(PROC_EVE2_INCLUDE),yes)
	@echo '# Including EVE2 ...'
	$(OUT2RPRC) $(App_EVE2) $(App_EVE2).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_EVE2).rprc
endif
ifeq ($(PROC_EVE3_INCLUDE),yes)
	@echo '# Including EVE3 ...'
	$(OUT2RPRC) $(App_EVE3) $(App_EVE3).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_EVE3).rprc
endif
ifeq ($(PROC_EVE4_INCLUDE),yes)
	@echo '# Including EVE4 ...'
	$(OUT2RPRC) $(App_EVE4) $(App_EVE4).rprc
	$(MAKE) -fbuild_multi_core_image_gen.mk sign_rprc_image INPUT_IMAGE=$(App_EVE4).rprc
endif
ifeq ($(FAST_BOOT_INCLUDE),yes)
	$(MAKE) -fbuild_multi_core_image_gen.mk fast_boot
else
	$(MAKE) -fbuild_multi_core_image_gen.mk normal_boot
endif

normal_boot:
	@echo '# Generating LE AppImage ...'
	$(CHMOD) u+x $(MULTICORE_IMAGE_GEN)
	$(MULTICORE_IMAGE_GEN) LE $(DEV_ID) $(OUT_PATH)/AppImage_LE $(INPUT_RPRC)
	@echo '# Generating BE AppImage ...'
	$(MULTICORE_IMAGE_GEN) BE $(DEV_ID) $(OUT_PATH)/AppImage_BE $(INPUT_RPRC)
ifeq ($(CRC_CALCULATE),yes)
	@echo '# Calculating CRC for AppImage ...'
	$(RM) $(OUT_PATH)/AppImage_BE
	$(CRC_MULTICORE_IMAGE_GEN) $(OUT_PATH)/AppImage_LE $(OUT_PATH)/AppImage_BE
endif
	$(COPY) $(OUT_PATH)/AppImage_LE $(OUT_PATH)/AppImage
	@echo '# AppImage is @ $(OUT_PATH)/AppImage'
ifneq ($(SD_CARD_DRIVE),)
	@echo '# Copying AppImage to [ $(SD_CARD_DRIVE) ] ...'
	$(COPY) $(OUT_PATH)/AppImage $(SD_CARD_DRIVE)/.
	@echo '# Copying AppImage to [ $(SD_CARD_DRIVE) ] ... DONE !!!'
endif

fast_boot:
	@echo '# Generating LE AppImage for UC Early ...'
	$(CHMOD) u+x $(MULTICORE_IMAGE_GEN)
	$(MULTICORE_IMAGE_GEN) LE $(DEV_ID) $(OUT_PATH)/AppImage_UcEarly_LE $(INPUT_RPRC_UC_EARLY)
	@echo '# Generating BE AppImage for UC Early ...'
	$(MULTICORE_IMAGE_GEN) BE $(DEV_ID) $(OUT_PATH)/AppImage_UcEarly_BE $(INPUT_RPRC_UC_EARLY)
	@echo '# Generating LE AppImage for UC Late ...'
	$(MULTICORE_IMAGE_GEN) LE $(DEV_ID) $(OUT_PATH)/AppImage_UcLate_LE $(INPUT_RPRC_UC_LATE)
	@echo '# Generating BE AppImage for UC Late ...'
	$(MULTICORE_IMAGE_GEN) BE $(DEV_ID) $(OUT_PATH)/AppImage_UcLate_BE $(INPUT_RPRC_UC_LATE)
ifeq ($(CRC_CALCULATE),yes)
	@echo '# Calculating CRC for AppImage UC Early not required ...'
	@echo '# Calculating CRC for AppImage UC Late ...'
	$(RM) $(OUT_PATH)/AppImage_UcLate_BE
	$(CRC_MULTICORE_IMAGE_GEN) $(OUT_PATH)/AppImage_UcLate_LE $(OUT_PATH)/AppImage_UcLate_BE
endif
	$(RM) $(OUT_PATH)/AppImage_UcEarly_LE
	$(RM) $(OUT_PATH)/AppImage_UcLate_LE
	@echo '# AppImage UC Early is @ $(OUT_PATH)/AppImage_UcEarly_BE'
	@echo '# AppImage UC Late is @ $(OUT_PATH)/AppImage_UcLate_BE'

sign_rprc_image:
ifeq ($(HS_DEVICE),yes)
ifeq ($(VSDK_BOARD_TYPE),$(filter $(VSDK_BOARD_TYPE), TDA2XX_EVM TDA2EX_EVM TDA2PX_EVM TDA2XX_RVP))
	$(MSHIELD_DK_DIR)/scripts/ift-image-sign.sh dra7xx $(INPUT_IMAGE) $(INPUT_IMAGE).signed > /dev/null
	$(MV) $(INPUT_IMAGE).signed $(INPUT_IMAGE)
endif
ifeq ($(VSDK_BOARD_TYPE),$(filter $(VSDK_BOARD_TYPE), TDA3XX_EVM TDA3XX_RVP))
ifeq ($(SECURITYLIB_APPIMAGE_DECRYPTION),yes)
	$(COPY) $(INPUT_IMAGE) $(INPUT_IMAGE).unsigned
	# AES + CBC-HMAC
	# AES encryption
	@echo '# Encrypting AppImage'
	@echo '# Generating random IV'
	dd if=/dev/urandom of=$(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.bin bs=1 count=16  2> /dev/null > /dev/null
	xxd -p $(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.bin > $(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.txt
	$(COPY) $(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.txt $(INPUT_IMAGE).iv.txt
	openssl enc -e -aes-128-cbc -in $(INPUT_IMAGE) -out $(INPUT_IMAGE).enc -K `cat $(TDA3X_SIGNING_TOOL_DIR)/image_enc_key.txt` -iv `cat $(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.txt`
	# Append IV to the image
	xxd -r -p $(TDA3X_SIGNING_TOOL_DIR)/image_enc_iv.txt >> $(INPUT_IMAGE).enc
	# CBC+HMAC digest generation
	@echo '# Generating and appending HMAC digest'
	$(COPY) $(INPUT_IMAGE).enc $(INPUT_IMAGE).signed
	openssl dgst -mac hmac -binary -macopt hexkey:`cat $(TDA3X_SIGNING_TOOL_DIR)/image_enc_key.txt` -sha256 $(INPUT_IMAGE).enc >> $(INPUT_IMAGE).signed
	$(MV) $(INPUT_IMAGE).signed $(INPUT_IMAGE)
else
	$(COPY) $(INPUT_IMAGE) $(INPUT_IMAGE).unsigned
	$(COPY) $(INPUT_IMAGE) $(INPUT_IMAGE).signed
	# Only CBC-HMAC
	# CBC+HMAC digest generation
	@echo '# Generating and appending HMAC digest'
	openssl dgst -mac hmac -binary -macopt hexkey:`cat $(TDA3X_SIGNING_TOOL_DIR)/image_enc_key.txt` -sha256 $(INPUT_IMAGE) >> $(INPUT_IMAGE).signed
	$(MV) $(INPUT_IMAGE).signed $(INPUT_IMAGE)
endif
endif
endif
