CXXFLAGS=-Wall -std=c++20
SRCS = main.cpp hw2_output.c parser.cpp private.cpp proper_private.cpp smoker.cpp
EXENAME=hw2


build:
	g++ $(CXXFLAGS) -o $(EXENAME) $(SRCS)

clean:
	rm -rf *.o
	rm -rf *.out

all: clean
	$(MAKE)
