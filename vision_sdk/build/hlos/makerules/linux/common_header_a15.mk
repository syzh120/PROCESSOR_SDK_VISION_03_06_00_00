# (c) Texas Instruments

ifndef $(COMMON_HEADER_MK)
COMMON_HEADER_MK = 1


CC=$(A15_TOOLCHAIN_PREFIX)gcc
CX=$(A15_TOOLCHAIN_PREFIX)g++
AR=$(A15_TOOLCHAIN_PREFIX)ar
LD=$(A15_TOOLCHAIN_PREFIX)g++


#Change a15 to $(CORE)

LIB_BASE_DIR=$(DEST_ROOT)/lib/$(PLATFORM)/$(CORE)/$(PROFILE_a15_0)
OBJ_BASE_DIR=$(DEST_ROOT)/obj/$(MODNAME)/$(PLATFORM)/$(CORE)/$(PROFILE_a15_0)
EXE_BASE_DIR=$(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)/

LIB_DIR=$(LIB_BASE_DIR)

CC_OPTS=-c -Wall -Warray-bounds -fPIC
CX_OPTS=-c -Wall -Warray-bounds -fPIC

ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)

# Disabling warnings as errors as opencv/cl headers contain lots of warnings
ifeq ($(ENABLE_OPENCV),yes)
CC_OPTS+= -w
else ifeq ($(OPENCL_INCLUDE),yes)
CC_OPTS+= -w
else
CC_OPTS+= -Werror
endif
CX_OPTS+=

endif

# Uncomment below line to build the A15 side binaries in debug mode
# This is required to debug using GDB etc where symbols should be present

#CONFIG=debug

ifeq ($(CONFIG), debug)

CC_OPTS+=-g
CX_OPTS+=-g
OPTI_OPTS=
DEFINE=-DDEBUG

else

CC_OPTS+=
CX_OPTS+=
OPTI_OPTS=-O3
DEFINE=

endif

AR_OPTS=-rc
LD_OPTS=-lpthread -lm $(PLAT_LINK)

DEFINE += $(vision_sdk_CFLAGS)
FILES=$(subst ./, , $(foreach dir,.,$(wildcard $(dir)/*.c)) )
FILESCPP=$(subst ./, , $(foreach dir,.,$(wildcard $(dir)/*.cpp)) )

vpath %.a $(LIB_DIR)

include $(vision_sdk_PATH)/build/hlos/makerules/linux/includes_a15.mk

INCLUDE=
INCLUDE+=$(KERNEL_INC)
INCLUDE+=$(COMMON_INC)


endif # ifndef $(COMMON_HEADER_MK)


