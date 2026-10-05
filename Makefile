sources  = main.cpp
sources += initInfo.cpp
sources += block.cpp
sources += statistics.cpp
sources += solver.cpp
sources += bitmap.cpp
sources += orientation.cpp
sources += trace.cpp
sources += array.cpp
objects = $(sources:.cpp=.o)
depends = $(sources:.cpp=.d)
CC = gcc
# Number of bits in a bitmap, i.e. the maximum number of squares on the board.
# Use 256 for the 16x16 puzzle. Run "make clean" after changing it.
BITMAP_BITS ?= 64
DEFINES  = -Wall -Wextra -O3 -march=native -DBITMAP_BITS=$(BITMAP_BITS)
#DEFINES  = -Wall -O3 -g -pg
#DEFINES += -DNDEBUG
#DEFINES += -DUSE_TRACE
#DEFINES += -DSTATISTICS

puzzle: $(objects) Makefile
	$(CC) -o $@ $(DEFINES) $(objects) -lstdc++

install: puzzle
	mkdir -p $(HOME)/bin
	cp puzzle $(HOME)/bin

%.d: %.cpp Makefile
	set -e; $(CC) -M $(CPPFLAGS) $(DEFINES) $(INCLUDE_DIRS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

include $(depends)

%.o :
	$(CC) $(DEFINES) $(INCLUDE_DIRS) -c $< -o $@

clean:
	-rm -f puzzle $(objects) $(depends)

.PHONY: install clean

