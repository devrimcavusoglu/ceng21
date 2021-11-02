// https://www.hackerrank.com/challenges/box-it/problem

#include "box.hpp"

Box::Box(){
    l = b = h = 0;
}

Box::Box(int length, int breadth, int height){
    l = length;
    b = breadth;
    h = height;
}

Box::Box(const Box& other){
    l = other.l;
    b = other.b;
    h = other.h;
}

int Box::getLength(){
    return l;
}

int Box::getBreadth(){
    return b;
}

int Box::getHeight(){
    return h;
}

long long Box::CalculateVolume(){
    return (long long) l*b*h;
}


bool Box::operator<(Box& other){
    if (l < other.l) return true;
    else if (b < other.b and l == other.l) return true;
    else if (h < other.h and b == other.b and l == other.l) return true;
    else return false;
}


std::ostream& operator<<(std::ostream& out, Box& other){
    return out << other.l << " " << other.b << " " << other.h;
}
