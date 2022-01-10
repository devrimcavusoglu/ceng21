#include "HashTable.h"


int main()
{
    KeyedHashTable ht;
    KeyedHashTable ht2;
    ht.Insert("A", std::vector<int>());
    ht.Insert("X", std::vector<int>());
    ht.Insert("U", std::vector<int>());
    
    ht.Print();

    ht2 = KeyedHashTable(ht);
    ht2.Print();
/*
    ht.ClearTable();
    ht.Print();
    ht2.Print();*/
}