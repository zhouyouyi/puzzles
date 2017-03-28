CXX := g++
CXXFLAGS := -Wall -O3 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
LINKFLAGS := #-ltcmalloc
TARGET := feedhandler

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LINKFLAGS)
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean
