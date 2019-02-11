#
# This file is the makefile for building all L3FW UT apps
#

include $(PDK_INSTALL_PATH)/ti/build/Rules.make

.PHONY : all clean

all:
	$(MAKE) -C $(l3fw_permission_all_unit_test_app_PATH)
	$(MAKE) -C $(l3fw_permission_all_unit_test_app_PATH)    sbl_appimagegen
	$(MAKE) -C $(l3fw_writeonly_unit_test_app_PATH)
	$(MAKE) -C $(l3fw_writeonly_unit_test_app_PATH)         sbl_appimagegen

clean:
	$(MAKE) -C $(l3fw_permission_all_unit_test_app_PATH)    clean
	$(MAKE) -C $(l3fw_writeonly_unit_test_app_PATH)         clean
