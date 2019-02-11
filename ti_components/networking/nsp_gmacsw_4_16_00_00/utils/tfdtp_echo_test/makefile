#
# Simple makefile to build examples using MinGW gcc on Windows
#

CC = gcc
CFLAGS = -Wall -D__MINGW32__

%.exe : %.c
	$(CC) $(CFLAGS) -o $@ $< -lwsock32 -lws2_32

all: tfdtp_echo_test.exe

clean:
	rm -f *.exe *.o
