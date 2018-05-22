CFLAGS  = -g -std=gnu99 -Wall -Werror
CFLAGS += -I/opt/redpitaya/include
LDFLAGS = -L/opt/redpitaya/lib
LDLIBS = -lm -lpthread -lyaml

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: bmCoordinator

bmCoordinator: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o bmCoordinator $(LDLIBS)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o
	$(RM) $(OBJS)
