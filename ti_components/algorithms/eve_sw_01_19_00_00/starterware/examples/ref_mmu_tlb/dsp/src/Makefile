#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=dsp
TARGET_NAME :=dsp_mmu_tlb

include ../../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

LOCAL_SRC = dsp1_main.c ref_tc_dsp1.c

all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean helper_functions no_optimization local_functions
	$(LN) -c -x -l"$(LINKER_CMD)" -l"$(CORE_LIB)" -l"$(LIB)" $(wildcard $(OBJ_DIR)/*.obj) -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map 

helper_functions : $(COMMON_SRC)
	$(CC) $(CFLAGS) $(COMMON_SRC) --obj_directory "$(OBJ_DIR)" 

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)" 

no_optimization:intvecs.asm
	$(CC) $(CFLAGS) --no_compress intvecs.asm --obj_directory "$(OBJ_DIR)"
	
clean :  
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map
