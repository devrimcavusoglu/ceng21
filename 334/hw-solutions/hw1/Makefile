CXXFLAGS=-Wall -std=c++17
EXENAME=hw1


build:
	gcc -Wall -Wextra -std=gnu99 -c parser.c -o parser.o
	g++ $(CXXFLAGS) -c main.cpp -o main.o
	g++ $(CXXFLAGS) -c bundle.cpp -o bundle.o
	g++ -o $(EXENAME) bundle.o parser.o main.o

clean:
	rm -rf *.o
	rm -rf *.exe

new: clean
	$(MAKE)
