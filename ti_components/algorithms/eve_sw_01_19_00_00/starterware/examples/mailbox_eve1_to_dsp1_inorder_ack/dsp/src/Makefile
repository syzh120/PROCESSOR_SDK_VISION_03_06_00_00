#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=dsp
TARGET_NAME :=dsp_mbox_eve1_to_dsp1_inorder_ack

include ../../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

LOCAL_SRC = eden_mailbox_eve1_to_gem1_gem1.c gem1_main.c tsc_h.asm

all: $(TARGET_NAME).out

$(TARGET_NAME).out: clean helper_functions local_functions no_optimization
	$(LFLAGS) $(wildcard $(OBJ_DIR)/*.obj) -o ../elf_out/$(TARGET_NAME).out -m ../elf_out/$(TARGET_NAME).map 

helper_functions : $(COMMON_SRC)
	$(CC) $(CFLAGS) $(COMMON_SRC) --obj_directory "$(OBJ_DIR)" 

local_functions : $(LOCAL_SRC)
	$(CC) $(CFLAGS) $(LOCAL_SRC) --obj_directory "$(OBJ_DIR)" 

no_optimization:intvecs.asm
	$(CC) $(CFLAGS) --no_compress intvecs.asm --obj_directory "$(OBJ_DIR)" 
clean :  
	$(RM_FILE_CMD) -f $(OBJ_DIR)/*.obj ../elf_out/*.out ../elf_out/*.map

