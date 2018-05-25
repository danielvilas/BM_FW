CFLAGS  = -g -std=gnu99 -Wall -Werror
CFLAGS += -I/opt/redpitaya/include
LDFLAGS = -L/opt/redpitaya/lib
LDLIBS = -lm -lpthread

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
OUT_BINARY=datalogger_dummy

all: $(OUT_BINARY)

datalogger_dummy: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o
	$(RM) $(OUT_BINARY)
