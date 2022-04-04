CXXFLAGS=-Wall -std=c++17
SRCS=main.cpp
EXENAME=hw1


build:
	gcc -Wall -Wextra -std=gnu99 -c parser.c -o parser.o
	g++ $(CXXFLAGS) -c $(SRCS) -o main.o
	g++ -o $(EXENAME) parser.o main.o -static

clean:
	del *.o
	del *.exe

new: clean
	$(MAKE)
