CXXFLAGS=-Wall -std=c++20
SRCS = main.cpp parser.c fat32.c image.cpp util.cpp
EXENAME=hw3


build:
	g++ $(CXXFLAGS) -o $(EXENAME) $(SRCS)

clean:
	rm -rf hw3
	rm -rf *.o
	rm -rf *.out

all: clean
	$(MAKE)
