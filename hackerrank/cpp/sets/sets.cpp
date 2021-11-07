#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>


std::vector<int> read(std::vector<int> &vec, int size){
    for (int i = 0; i < size; i++){
        int qtype, qval;
        std::cin >> qtype >> qval;
        int *query = new int[2]{qtype, qval};
        vec.push_back(*query);
    }
    return vec;
}

void query(std::set<int> &set, int *query){
    if (query[0] == 1)
        set.insert(query[1]);
    else if (query[0] == 2){
        if (set.find(query[1]) != set.end())
            set.erase(query[1]);
    }
    else if (query[0] == 3){
        if (set.find(query[1]) != set.end())
            std::cout << "Yes";
        else
            std::cout << "No";
        std::cout << "\n";
    }
}

int main() {
    int Q;
    std::set<int> s;
    std::vector<int> q;

    std::cin >> Q;
    read(q, Q);

    for (int i = 0; i<Q; i++){
        query(s, &q[i]);
    }

    return 0;
}

