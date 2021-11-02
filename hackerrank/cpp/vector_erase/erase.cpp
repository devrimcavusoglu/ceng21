// https://www.hackerrank.com/challenges/vector-erase/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

std::vector<int> read(std::vector<int> &v, int size){
    for (int i = 0; i < size; i++){
        int temp;
        std::cin >> temp;
        v.push_back(temp);
    }
    return v;
}

void printArray(std::vector<int> &v){
    int n = v.size();
    for(int i = 0; i < n; i++){
        if (i == n-1)
            std::cout << v[i];
        else
            std::cout << v[i] << " ";
    }
}


int main() {
    int N;
    int rm_index;
    int rm_start, rm_end;
    std::vector<int> v;

    std::cin >> N;
    read(v, N);
    std::cin >> rm_index;
    std::cin >> rm_start >> rm_end;

    // queries indicies start from 1.
    rm_index--;
    rm_start--;
    rm_end--;

    v.erase(v.begin() + rm_index);
    v.erase(v.begin() + rm_start, v.begin() + rm_end);

    std::cout << v.size() << std::endl;
    printArray(v);

    return 0;
}
