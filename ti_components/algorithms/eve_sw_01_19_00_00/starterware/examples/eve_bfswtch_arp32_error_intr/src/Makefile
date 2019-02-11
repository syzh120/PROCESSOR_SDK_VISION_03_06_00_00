#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=eve
TARGET_NAME:=eve_bfswtch_arp32_error_intr

include ../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

LOCAL_SRC = eve1_main.c eve_bfswtch_error_intr_main.c $(COMMON_DIR)/$(TARGET_SOC)/boot_arp32.asm

# 'target' rules
all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean local_functions 
	$(LFLAGS) $(wildcard $(OBJ_DIR)/*.obj) -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)"    

clean : 
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map

