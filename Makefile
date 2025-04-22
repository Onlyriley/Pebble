CC      = gcc
CFLAGS  = -Wall -g $(shell pkg-config --cflags readline)
LIBS    = -lpthread $(shell pkg-config --libs readline)

SRCS    = main.c input.c exec.c delay.c visuals.c
OBJS    = $(SRCS:.c=.o)

all: pebble

pebble: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# generic rule
%.o: %.c shell.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) pebble
