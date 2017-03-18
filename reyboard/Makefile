CC := g++
CFLAGS := -Wall -g
TARGET := reyboard

# $(wildcard *.cc /xxx/xxx/*.cc): get all .cc files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard src/*.cc)
# $(patsubst %.cc,%.o,$(SRCS)): substitute all ".cc" file name strings to ".o" file name strings
OBJS := $(addprefix obj/,$(notdir $(SRCS:.cc=.o)))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
obj/%.o: src/%.cc
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf $(TARGET) obj/*.o

.PHONY: all clean
