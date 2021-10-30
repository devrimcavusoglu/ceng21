#include <iostream>
#include "pair.hpp"


int main() {
    Pair p(15,16);
    Pair q(p);
    Pair *hp = new Pair(23,42);
    delete hp;
  
    std::cout << "If this message is printed,"
        << " at least the program hasn't crashed yet!\n"
        << "But check the output of valgrind below\n" 
        << "If you read \"All heap blocks were freed -- no leaks are possible\"\n" 
        << "all is good!" << std::endl;
        
    return 0;
}

