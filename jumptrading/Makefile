CC := g++
CFLAGS := -Wall -g -pg
TARGET := feedhandler

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean
