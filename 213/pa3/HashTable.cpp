#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO
}

void KeyedHashTable::ReHash()
{
    // TODO
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
}

void KeyedHashTable::ClearTable()
{
   // TODO
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}