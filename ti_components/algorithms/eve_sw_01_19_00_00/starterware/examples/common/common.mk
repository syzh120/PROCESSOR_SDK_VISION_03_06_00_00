ifeq ($(TARGET_BUILD), )
    TARGET_BUILD := debug
endif

ifeq ($(TARGET_BUILD),release)
CFLAGS= $(TARGETCC_FLAGS) 
else
CFLAGS= $(TARGETDC_FLAGS)
endif

LINKER_CMD = linker.cmd
COMMON_DIR = $(STARTERWARE_DIR)/examples/common

LFLAGS = $(LN) -c -x -l"$(CORE_LIB)" -l"$(LIB)" -l"$(LINKER_CMD)"

ifeq ($(CORE),dsp)
    COMMON_SRC = $(COMMON_DIR)/dsp/src/INTH_dsp.c 
    COMMON_INC = $(COMMON_DIR)/dsp/inc
endif

ifeq ($(PLATFORM),vayu)
    CFLAGS+= --define EDEN28
endif

CFLAGS += --define $(DEFINE_FLAGS) 
CFLAGS += -I"$(COMPILE_PATH)/include" -I"$(STARTERWARE_DIR)/inc"
CFLAGS += -I"$(COMPILE_PATH)/include/vcop"
CFLAGS += -I"$(STARTERWARE_DIR)/examples/common"
CFLAGS += -I"$(STARTERWARE_DIR)/examples/common/$(TARGET_SOC)/$(CORE)"
CFLAGS += -I"$(BASE_ADDRESS_DIR)"
ifeq ($(CORE),dsp)
CFLAGS += -I"$(COMMON_INC)"
endif