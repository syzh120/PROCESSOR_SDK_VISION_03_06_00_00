

include $(ROOTDIR)/build/rtos/makerules/platform.mk
include $(ROOTDIR)/build/rtos/makerules/env.mk

libs:
ifeq ($(PROC_IPU_BUILD_INCLUDE),yes)
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=ipu1_0
else ifeq ($(PROC_IPU1_1_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=ipu1_1
endif
endif

# IPU2 is main IPU core for A15 Linux build and
# IPU2 can be enabled without IPU1-0 in the build
ifeq ($(PROC_IPU_BUILD_INCLUDE),yes)
ifeq ($(PROC_IPU2_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=ipu2
endif
endif

ifeq ($(PROC_DSP_BUILD_INCLUDE),yes)
ifeq ($(PROC_DSP1_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=c66xdsp_1
else ifeq ($(PROC_DSP2_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=c66xdsp_2
endif
endif

ifeq ($(PROC_EVE_BUILD_INCLUDE),yes)
ifeq ($(PROC_EVE1_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=arp32_1
else ifeq ($(PROC_EVE2_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=arp32_2
else ifeq ($(PROC_EVE3_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=arp32_3
else ifeq ($(PROC_EVE4_INCLUDE),yes)
	$(MAKE) $(TARGET) CORE=arp32_4
endif
endif

ifeq ($(PROC_A15_0_BUILD_INCLUDE),yes)
ifeq ($(PROC_A15_0_INCLUDE),yes)
ifeq ($(A15_TARGET_OS),Bios)
	$(MAKE) $(TARGET) CORE=a15_0
endif
endif
endif

clean:
	$(MAKE) -fMAKEFILE.MK TARGET=clean

all: clean libs
