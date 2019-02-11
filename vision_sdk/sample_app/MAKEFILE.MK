
include $(ROOTDIR)/build/rtos/makerules/platform.mk

# Include the application libs for each core here:

APP_LIBS_$(IPU_PRIMARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/sample_app_libs.aem4

# Application Algorithm plug in lib
APP_LIBS_$(IPU_PRIMARY_CORE) += $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_$(IPU_PRIMARY_CORE))/app_alg_plugins.aem4
APP_LIBS_ipu1_1 += $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_ipu1_1)/app_alg_plugins.aem4
APP_LIBS_$(IPU_SECONDARY_CORE) = $(DEST_ROOT)/lib/$(PLATFORM)/m4/$(PROFILE_$(IPU_SECONDARY_CORE))/app_alg_plugins.aem4
APP_LIBS_c66xdsp_1 += $(DEST_ROOT)/lib/$(PLATFORM)/66/$(PROFILE_c66xdsp_1)/app_alg_plugins.ae66
APP_LIBS_c66xdsp_2 += $(DEST_ROOT)/lib/$(PLATFORM)/66/$(PROFILE_c66xdsp_2)/app_alg_plugins.ae66
APP_LIBS_arp32_1 += $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_1)/app_alg_plugins.aearp32F
APP_LIBS_arp32_2 += $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_2)/app_alg_plugins.aearp32F
APP_LIBS_arp32_3 += $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_3)/app_alg_plugins.aearp32F
APP_LIBS_arp32_4 += $(DEST_ROOT)/lib/$(PLATFORM)/arp32/$(PROFILE_arp32_4)/app_alg_plugins.aearp32F
APP_LIBS_a15_0 += $(DEST_ROOT)/lib/$(PLATFORM)/a15/$(PROFILE_a15_0)/app_alg_plugins.aa15fg

# EVE algorithms libs
EVE_ALG_LIBS = $(algframework_PATH)/lib/eve/$(PROFILE)/algframework.lib
EVE_ALG_LIBS += $(dmautils_PATH)/libs/eve/$(PROFILE)/dmautils.lib
EVE_ALG_LIBS += $(evealg_PATH)/apps/apps_nonbam/lib/$(PROFILE_arp32_1)/libeveapps.eve.lib


APP_LIBS_arp32_1 += $(EVE_ALG_LIBS)
APP_LIBS_arp32_2 += $(EVE_ALG_LIBS)
APP_LIBS_arp32_3 += $(EVE_ALG_LIBS)
APP_LIBS_arp32_4 += $(EVE_ALG_LIBS)

app_libs:
ifeq ($(PROC_IPU1_0_BUILD_INCLUDE),yes)
ifeq ($(IPU_PRIMARY_CORE),ipu1_0)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH) CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif
endif
endif

ifeq ($(PROC_IPU2_BUILD_INCLUDE),yes)
ifeq ($(IPU_PRIMARY_CORE),ipu2)
ifeq ($(PROC_IPU2_INCLUDE),yes)
	$(MAKE) -C $($(MAKEAPPNAME)_PATH) CORE=$(IPU_PRIMARY_CORE) $(TARGET)
endif
endif
endif

apps:
	$(MAKE) -fMAKEFILE.MK -C $(vision_sdk_PATH)/links_fw/src/rtos apps

clean:
	$(MAKE) -fMAKEFILE.MK app_libs TARGET=clean

all: clean app_libs apps


export APP_LIBS_ipu1_0
export APP_LIBS_ipu1_1
export APP_LIBS_ipu2
export APP_LIBS_c66xdsp_1
export APP_LIBS_c66xdsp_2
export APP_LIBS_arp32_1
export APP_LIBS_arp32_2
export APP_LIBS_arp32_3
export APP_LIBS_arp32_4
export APP_LIBS_a15_0
