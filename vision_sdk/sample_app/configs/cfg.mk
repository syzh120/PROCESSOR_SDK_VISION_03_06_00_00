
#
# This file lists all possible modules that can be included in the build of Vision SDK
#
# Modules includes
# - algplugins
# - use-cases
#
# Config files present in vision_sdk/build/configs/<config-name>/
# select the exact modules that are included in the final Vision SDK build
#
# if <config-name> file does not mark a module as "yes", i.e its
# marked "no" or not defined then the module does not get included in the
# Vision SDK build
#


CHECK_YES = $(filter yes, $(subst emptyreplacement,,$(1)))
export CHECK_YES

include $($(MAKEAPPNAME)_PATH)/configs/$(MAKECONFIG)/cfg.mk

ALG_LIST = \
   ALG_framecopy \

ifeq ($(A15_TARGET_OS), Bios)
ifneq ($(RADAR_ONLY),yes)
UC_LIST = \
   UC_nullSrc_display
else
   UC_LIST =
endif
endif


UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/$(subst UC_,,$(uc))/cfg.mk)
UC_CFGS = $(foreach uc,$(UC_LIST),$(UC_CFG))

#linux build related entries
ifeq ($(A15_TARGET_OS), Linux)
LINUX_UC_LIST = \
   UC_nullSrc_display

LINUX_UC_CFG = $(if $(call CHECK_YES, $($(uc))), $($(MAKEAPPNAME)_PATH)/src/hlos/usecases/$(subst UC_,,$(uc))/cfg.mk)
LINUX_UC_CFGS = $(foreach uc,$(LINUX_UC_LIST),$(LINUX_UC_CFG))
endif

ALL_UC_LIST = $(UC_LIST) $(RADAR_UC_LIST) $(LINUX_UC_LIST)

include $(UC_CFGS) $(LINUX_UC_CFGS)

