# (c) Texas Instruments

BASE_DIR = $(abspath .)
BUILD_OS=Linux
CONFIG=release

ifeq ($(BUILD_OS),Windows_NT)
  MAKE = gmake
  CGTOOLS_PATH="c:/Program Files (x86)/CodeBlocks/MinGW"
  AR=$(CGTOOLS_PATH)/bin/ar
  LD_OPTS :=
  EXE_EXT = exe
endif

ifeq ($(BUILD_OS),Linux)
  MAKE = make
  CGTOOLS_PATH=/usr/
  AR = $(CGTOOLS_PATH)/bin/gcc-ar
  CFLAGS := -Dlinux
  LD_OPTS := -lrt
  EXE_EXT = out
endif

CC = $(CGTOOLS_PATH)/bin/gcc
LD = $(CGTOOLS_PATH)/bin/gcc

SOURCES := $(wildcard src/*.c)
OBJS := $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))
EXEC_NAME=image_convert.$(EXE_EXT)

CFLAGS += -MMD -c -Wall
INCLUDES := -I./include

ifeq ($(CONFIG), release)
CFLAGS+=
OPTI_OPTS=-O3
DEFINE=
else
CFLAGS+=-g
OPTI_OPTS=
DEFINE=-DDEBUG
endif


.PHONY: all clean objdir

all:clean objdir $(EXEC_NAME)

objdir:
	@mkdir -p obj

$(EXEC_NAME): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LD_OPTS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(OPTI_OPTS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) -r obj
	$(RM) $(EXEC_NAME)

-include $(OBJS:.o=.d)

