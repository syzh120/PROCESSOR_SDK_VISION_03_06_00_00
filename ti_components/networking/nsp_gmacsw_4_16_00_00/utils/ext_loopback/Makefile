SOURCES := external_loopback_daemon.c
OBJS := $(SOURCES:.c=.o)
CFLAGS := -O2

.PHONY: clean

all: external_loopback_daemon

external_loopback_daemon: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)
    
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) *.o
