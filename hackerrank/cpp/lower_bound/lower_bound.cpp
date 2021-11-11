#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


std::vector<int> read(std::vector<int> &vec, int size){
    for (int i = 0; i < size; i++){
        int temp;
        std::cin >> temp;
        vec.push_back(temp);
    }
    return vec;
}

void find_lower_bound(std::vector<int> &vec, int value){
    int n = vec.size();

    for (int i = 0; i < n; i++){
        if (value >= vec[i]){
            if (value == vec[i]){
                std::cout << "Yes" << " " << i+1;
                break;
            }
            else if (value < vec[i+1]){
                std::cout << "No" << " " << i+2;
                break;
            }
        }
    }
}

int main() {
    int N;
    int Q;
    std::vector<int> v;
    std::vector<int> q;

    std::cin >> N;
    read(v, N);

    std::cin >> Q;
    read(q, Q);

    for (int i = 0; i<Q; i++){
        find_lower_bound(v, q[i]);
        std::cout << std::endl;
    }

    return 0;
}
