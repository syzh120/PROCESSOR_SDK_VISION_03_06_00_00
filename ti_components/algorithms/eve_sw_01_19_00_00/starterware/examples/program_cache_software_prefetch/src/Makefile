#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=eve
TARGET_NAME:=eve_program_cache_software_prefetch

include ../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

LOCAL_SRC = eve1_main.c vcop_array_add_uns_char.c $(COMMON_DIR)/$(TARGET_SOC)/boot_arp32.asm

KERNEL_SRC = vcop_array_add_uns_char_kernel.k

# 'target' rules
all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean kernel_functions local_functions 
	$(LFLAGS) $(wildcard $(OBJ_DIR)/*.obj) -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)"    

kernel_functions : $(KERNEL_SRC)	
	$(CC) $(CFLAGS) -kh $(KERNEL_SRC) --obj_directory "$(OBJ_DIR)"    

clean : 
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map ./*.h ./*_kernel.c

