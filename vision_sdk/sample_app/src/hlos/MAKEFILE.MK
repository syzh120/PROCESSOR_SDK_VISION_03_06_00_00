
include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

apps:
# Add Algplugins here
ifeq ($(ALG_framecopy),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/alg_plugins/framecopy MODNAME=$(MAKEAPPNAME) CORE=a15_0 depend
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/alg_plugins/framecopy MODNAME=$(MAKEAPPNAME) CORE=a15_0 lib
endif
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/usecases/nullSrc_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 depend
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/usecases/nullSrc_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 lib
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/chains_common MODNAME=$(MAKEAPPNAME) CORE=a15_0 lib
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/chains_common MODNAME=$(MAKEAPPNAME) CORE=a15_0 exe

clean:
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/usecases/nullSrc_display MODNAME=$(MAKEAPPNAME) CORE=a15_0 clean
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/chains_common MODNAME=$(MAKEAPPNAME) CORE=a15_0 clean
# Clean Algplugins here
ifeq ($(ALG_framecopy),yes)
	$(MAKE) -fMAKEFILE.MK -C$($(MAKEAPPNAME)_PATH)/src/hlos/alg_plugins/framecopy MODNAME=$(MAKEAPPNAME) CORE=a15_0 clean
endif
all: clean apps

.PHONY: apps clean all
