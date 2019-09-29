sources  = block.cpp
sources += init.cpp
sources += puzzle.cpp
sources += statistics.cpp
sources += solver.cpp
sources += bitmap.cpp
sources += orientation.cpp
sources += trace.cpp
sources += array.cpp
objects = $(sources:.cpp=.o)
depends = $(sources:.cpp=.d)
CC = gcc
#DEFINES  = -Wall -O3 -g -pg
DEFINES  = -Wall -O3 
#DEFINES += -DNDEBUG
DEFINES += -D__USE_STD_IOSTREAM

puzzle: $(objects) Makefile
	$(CC) -o $@ $(DEFINES) $(objects) -lstdc++
	mv $@ /home/mike/bin

%.d: %.cpp
	set -e; $(CC) -M $(CPPFLAGS) $(DEFINES) $(INCLUDE_DIRS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

include $(depends)

%.o :
	$(CC) $(DEFINES) $(INCLUDE_DIRS) -c $< -o $@

clean:
	-rm $(objects)
	-rm $(depends)

