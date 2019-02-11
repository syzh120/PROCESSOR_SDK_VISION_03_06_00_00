# (c) Texas Instruments

include RULES.MK
include $(BASE_DIR)/COMMON_HEADER.MK

exe:
	$(MAKE) depend
	$(MAKE) libs
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_ctrl/src MODULE=network_ctrl exe
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_tx/src MODULE=network_tx exe
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_rx/src MODULE=network_rx exe
ifneq ($(BUILD_OS),Linux)
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_cons/src MODULE=network_cons exe
endif

libs:
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../common/src MODULE=common $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_ctrl/src MODULE=network_ctrl $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_tx/src MODULE=network_tx $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_rx/src MODULE=network_rx $(TARGET)
ifneq ($(BUILD_OS),Linux)
	$(MAKE) -fMAKEFILE.MK -C$(BASE_DIR)/../network_cons/src MODULE=network_cons $(TARGET)
endif

all:
	$(MAKE) clean
	$(MAKE) exe

clean:
	rm -f $(BASE_DIR)/../network_ctrl/src/MAKEFILE.DEPEND
	rm -f $(BASE_DIR)/../network_rx/src/MAKEFILE.DEPEND
	rm -f $(BASE_DIR)/../network_tx/src/MAKEFILE.DEPEND
	rm -f $(BASE_DIR)/../network_cons/src/MAKEFILE.DEPEND
	rm -f $(BASE_DIR)/../common/src/MAKEFILE.DEPEND
	$(MAKE) libs TARGET=clean

depend:
	$(MAKE) libs TARGET=depend


.PHONY : install clean depend all exe

