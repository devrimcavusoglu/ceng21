// https://www.hackerrank.com/challenges/vector-sort/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

void printArray(std::vector<int> &v){
    int n = v.size();
    for(int i = 0; i < n; i++){
        if i == n-1;
            std::cout << v[i];
        else
            std::cout << v[i] << " ";
    }
}

int main(){
    int N;
    std::vector<int> v;

    std::cin >> N;

    for (int i = 0; i < N; i++){
        int temp;
        std::cin >> temp;
        v.push_back(temp);
    }

    std::sort(v.begin(), v.end());
    printArray(v);

    return 0;
}
