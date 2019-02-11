# (c) Texas Instruments

BASE_DIR = $(abspath .)
BUILD_OS=Linux
CONFIG=release

ifeq ($(BUILD_OS),Windows_NT)
  MAKE = gmake
  CGTOOLS_PATH="c:/Program Files (x86)/CodeBlocks/MinGW"
  AR=$(CGTOOLS_PATH)/bin/ar
  LD_OPTS :=-lws2_32 -lwsock32 -lwininet -lnetapi32 -liphlpapi -lpthread
  EXE_EXT = exe
  LIBS:= src/Lib/libwpcap.a
endif

ifeq ($(BUILD_OS),Linux)
  MAKE = make
  CGTOOLS_PATH=/usr/
  AR = $(CGTOOLS_PATH)/bin/gcc-ar
  CFLAGS := -Dlinux
  LD_OPTS := -lrt -lpcap -lpthread
  EXE_EXT = out
endif

CC = $(CGTOOLS_PATH)/bin/gcc
LD = $(CGTOOLS_PATH)/bin/gcc

SOURCES := $(wildcard src/*.c)
OBJS := $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))
EXEC_NAME=avbtp_listener.$(EXE_EXT)

CFLAGS += -MMD -c -Wall
INCLUDES := -Isrc/WpdPack/Include -Isrc/

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

all: objdir $(EXEC_NAME)

objdir:
	@mkdir -p obj

$(EXEC_NAME): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LD_OPTS) $(LIBS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(OPTI_OPTS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) -r obj
	$(RM) $(EXEC_NAME)

-include $(OBJS:.o=.d)
