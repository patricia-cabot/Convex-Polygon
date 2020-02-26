# Defines the flags for compiling with C++.
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include
LIB_DIR = $(HOME)/libs/lib

# Rule to compile everything (make all).
# Because it is the first rule, it is also the default rule (make).
all: main.exe

# Rule to clean object and executable files (make clean).
clean:
	rm -f main.exe *.o

# Rule to link the executable from then object files.
# The following default variables are used:
# 		$^ is the names of all the prerequisites
# 		$@ is the name of the target of the rule
# 		$(CXX) is the name of the C++ compile
main.exe: main.o Point.o Polygon.o
		$(CXX) $^ -o $@ -L $(LIB_DIR) #-l PNGwriter -l png

## Dependencies between files
# (we don't need to precise how to produce them, Makefile already knows)

main.o: main.cc Point.hh Polygon.hh

Polygon.o: Polygon.cc Polygon.hh Point.hh