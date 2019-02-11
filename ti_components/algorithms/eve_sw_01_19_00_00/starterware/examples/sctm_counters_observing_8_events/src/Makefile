#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=eve
TARGET_NAME:=sctm_counters_observing_8_events

include ../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

LOCAL_SRC = eve1_main.c vcop_vec_gradients_xy_and_magnitude.c $(COMMON_DIR)/$(TARGET_SOC)/boot_arp32.asm

KERNEL_SRC = vcop_vec_gradients_xy_and_magnitude_kernel.k

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

