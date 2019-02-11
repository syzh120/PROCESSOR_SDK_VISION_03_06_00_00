#
# Simple makefile to build examples on Linux or using MinGW gcc on Windows
#

BUILD_OS=Windows
OBJDIR = objs
OBJS = tfdtp_api.o tfdtp_test_client.o tfdtp_host_app.o tfdtp_utils.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(OBJS))
CC = gcc

ifeq ($(BUILD_OS),Linux)
TARGET = ./bin/tfdtp_test.out
CFLAGS = -c -Wall -Dlinux -g
LDOPTS= -lrt
else
TARGET = ./bin/tfdtp_test.exe
CFLAGS = -c -Wall -D__MINGW32__ -g
LDOPTS = -lwsock32 -lws2_32 -liphlpapi
endif

$(TARGET):  depend $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDOPTS)

depend:
	-mkdir -p objs
	-mkdir -p bin

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

init:
	@rm -rf objs
	@mkdir -p objs

all: init $(TARGET)

clean:
	rm -rf objs
	rm -rf bin
