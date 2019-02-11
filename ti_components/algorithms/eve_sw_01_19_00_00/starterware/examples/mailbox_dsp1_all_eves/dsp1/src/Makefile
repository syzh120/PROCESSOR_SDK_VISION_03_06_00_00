#/*==========================================================================*/
#/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
#/*                      All Rights Reserved                                 */
#/*==========================================================================*/
CORE:=dsp
TARGET_NAME :=dsp_mbox_dsp1_all_eves
include ../../../../Rules.make
include $(STARTERWARE_DIR)/examples/common/common.mk

OBJ_DIR = ../objs

ifeq ($(TARGET_SOC),vayu)
	CFLAGS+= -D EDEN28
endif

LOCAL_SRC = eden_mailbox_eve_to_gem.c gem1_main.c   tsc_h.asm

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

