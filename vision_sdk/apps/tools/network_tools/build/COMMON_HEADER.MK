# (c) Texas Instruments

ifndef $(COMMON_HEADER_MK)
COMMON_HEADER_MK = 1
ifeq ($(BUILD_OS),Windows_NT)
CC=$(CGTOOLS_PATH)/bin/gcc
AR=$(CGTOOLS_PATH)/bin/ar
LD=$(CGTOOLS_PATH)/bin/gcc
endif

ifeq ($(BUILD_OS),Linux)
CC = $(CGTOOLS_PATH)/bin/gcc
AR = $(CGTOOLS_PATH)/bin/gcc-ar
LD = $(CGTOOLS_PATH)/bin/gcc
endif

LIB_BASE_DIR=$(BASE_DIR)/../lib/
OBJ_BASE_DIR=$(BASE_DIR)/../lib/obj
EXE_BASE_DIR=$(BASE_DIR)/../bin/

LIB_DIR=$(LIB_BASE_DIR)/$(CONFIG)

CC_OPTS=-c -Wall

ifeq ($(CONFIG), debug)

CC_OPTS+=-g
OPTI_OPTS=
DEFINE=-DDEBUG

else

CC_OPTS+=
OPTI_OPTS=-O3
DEFINE=

endif

AR_OPTS=-rc
LD_OPTS=

ifeq ($(BUILD_OS),Linux)
CC_OPTS += -Dlinux
LD_OPTS += -lrt
else
LD_OPTS +=-lws2_32 -lwsock32 -lwininet -lnetapi32 -liphlpapi
endif

FILES=$(subst ./, , $(foreach dir,.,$(wildcard $(dir)/*.c)) )

vpath %.a $(LIB_DIR)

include $(BASE_DIR)/INCLUDES.MK

INCLUDE=
INCLUDE+=$(COMMON_INC)

endif # ifndef $(COMMON_HEADER_MK)

