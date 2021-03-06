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
DEFINES  = -Wall -Wextra -O3 -march=native
#DEFINES  = -Wall -O3 -g -pg
#DEFINES += -DNDEBUG
#DEFINES += -DUSE_TRACE
#DEFINES += -DSTATISTICS

puzzle: $(objects) Makefile
	$(CC) -o $@ $(DEFINES) $(objects) -lstdc++
	mv $@ $(HOME)/bin

%.d: %.cpp Makefile
	set -e; $(CC) -M $(CPPFLAGS) $(DEFINES) $(INCLUDE_DIRS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

include $(depends)

%.o :
	$(CC) $(DEFINES) $(INCLUDE_DIRS) -c $< -o $@

clean: Makefile
	-rm $(objects)
	-rm $(depends)

