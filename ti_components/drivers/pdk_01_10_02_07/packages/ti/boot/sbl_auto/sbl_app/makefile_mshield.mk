#
# This file is the makefile for building MSHIELD required for secure boot
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

.PHONY : build_mshield

#Invoke as below. Note: -j doesnt work
#make -C $pdk_dir/packages/ti/boot/sbl_auto/sbl_app -fmakefile_mshield.mk PDK_INSTALL_PATH=$pdk_dir/packages BUILD_HS=yes 2>/dev/null >/dev/null
build_mshield:
ifeq ($(BUILD_HS),yes)
  ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex dra72x dra75x))
	$(ECHO) "# Building PPA using MSHIELD-DK/SECDEV"
	$(ECHO) "# This need to run only once on your PC - you can disable this step after a successful build"
	$(ECHO) "# This will take a few minutes"
	$(MSHIELD_DK_DIR)/scripts/ift-ppa-gen.sh dra7xx
  endif
endif
