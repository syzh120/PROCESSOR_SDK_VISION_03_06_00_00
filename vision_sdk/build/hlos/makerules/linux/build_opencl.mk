include env.mk

_vision_sdk_opencl:
ifeq ($(BUILD_LLVM), yes)
	$(MAKE) -f llvm/Makefile.ti all.x86 -C /datalocal/ti_components/open_compute/opencl_src/ti-llvm
	$(MAKE) -f llvm/Makefile.ti all.arm -C /datalocal/ti_components/open_compute/opencl_src/ti-llvm
endif
	$(MAKE) -f makefile -C /datalocal/ti_components/open_compute/opencl_src/ti-opencl BUILD_AM57=1
	$(CP) /datalocal/ti_components/open_compute/opencl_src/ti-opencl/install/am57/lib/firmware/* $(LINUX_TARGETFS)/lib/firmware/
	$(CP) -R /datalocal/ti_components/open_compute/opencl_src/ti-opencl/install/am57/usr/share/ti/opencl/* $(LINUX_TARGETFS)/usr/share/ti/opencl/

_vision_sdk_opencl_clean:
ifeq ($(BUILD_LLVM), yes)
	$(MAKE) -f llvm/Makefile.ti all.x86 -C /datalocal/ti_components/open_compute/opencl_src/ti-llvm clean
	$(MAKE) -f llvm/Makefile.ti all.arm -C /datalocal/ti_components/open_compute/opencl_src/ti-llvm clean
endif
	$(MAKE) -f makefile -C /datalocal/ti_components/open_compute/opencl_src/ti-opencl BUILD_AM57=1 clean
	$(RM) -R /datalocal/ti_components/open_compute/opencl_src/ti-opencl/install/am57/lib/firmware/dra7-dsp1-fw.xe66
	$(RM) -R /datalocal/ti_components/open_compute/opencl_src/ti-opencl/install/am57/lib/firmware/dra7-dsp2-fw.xe66
	$(RM) -R /datalocal/ti_components/open_compute/opencl_src/ti-opencl/install/am57/usr/share/ti/opencl/*
