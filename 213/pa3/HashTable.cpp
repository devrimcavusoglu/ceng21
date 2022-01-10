#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

struct InvalidKeyException : public std::runtime_error
{
    // Constructor
    InvalidKeyException()
        : std::runtime_error("A value with an empty key cannot be inserted.")
    {}
};

struct CapacityIsFullException : public std::runtime_error
{
    // Constructor
    CapacityIsFullException()
        : std::runtime_error("Table is full.")
    {}
};

const std::string KeyedHashTable::REMOVED_KEY = "__DELETED__";

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] = {
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

int KeyedHashTable::Hash(const std::string& key) const {
    // h(s) = sum_i(s[i] * prime[i]) % tableSize
    int h = 0;
    for (int i = 0; i < key.length(); i++) {
        h += key[i] * PRIME_LIST[i];
    }
    return h % tableSize;
}

void KeyedHashTable::ReHash() {
    int old_tableSize = tableSize;
    HashData* aux = new HashData[old_tableSize]();
    for (int i = 0; i < old_tableSize; i++) {
        aux[i] = this->table[i];
    }

    int new_tableSize = this->FindNearestLargerPrime(old_tableSize*2);
    delete [] this->table;
    this->table = new HashData[new_tableSize]();
    this->tableSize = new_tableSize;
    for (int i = 0; i < old_tableSize; i++) {
        HashData entry = aux[i];
        if (entry.key.empty() or entry.key == REMOVED_KEY)
            continue;
        this->occupiedElementCount--;
        this->Insert(entry.key, entry.intArray);
    }
    delete [] aux;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity) {
    int val;
    for (int i = 0; i < PRIME_TABLE_COUNT; i++) {
        val = PRIME_LIST[i];
        if (val > requestedCapacity)
            break;
    }
    // Falling back to largest prime if requestedCapacity > largestPrime.
    return val;
}

KeyedHashTable::KeyedHashTable() {
    this->tableSize = PRIME_LIST[0];
    this->table = new HashData[tableSize]();
    this->occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity) {
    this->tableSize = this->FindNearestLargerPrime(requestedCapacity);
    this->table = new HashData[tableSize]();
    this->occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other) {
    this->tableSize = PRIME_LIST[0];
    this->table = new HashData[this->tableSize]();
    this->occupiedElementCount = 0;   
    *this = other;
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other) {
    if (this != &other) {
        delete [] this->table;
        this->occupiedElementCount = other.occupiedElementCount;
        this->tableSize = other.tableSize;
        this->table = new HashData[this->tableSize]();
        for (int i = 0; i<this->tableSize; i++) {
            HashData entry = other.table[i];
            this->table[i] = entry;
        }
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable() {
    delete [] table;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray) {
    if (this->isFull()) 
        throw CapacityIsFullException();
    else if (key.empty())
        throw InvalidKeyException();

    // return false if key already exists
    if (this->get(key))
        return false;

    int id = this->get_available_id(key);
    HashData data;
    data.key = key;
    data.intArray = intArray;
    this->table[id] = data;
    this->occupiedElementCount++;

    // rehash if (occupiedElementCount * EXPAND_THRESHOLD >= tableSize)
    if (occupiedElementCount * EXPAND_THRESHOLD >= tableSize)
        ReHash();
    return true;
}

bool KeyedHashTable::Remove(const std::string& key) {
    // lazy delete of the key.
    HashData *entry = this->get(key);
    entry->key = REMOVED_KEY;
    entry->intArray.clear();
    occupiedElementCount--;
}

void KeyedHashTable::ClearTable() {
    // lazy clear of the table
    for (int i = 0; i < this->tableSize; i++) {
        HashData *entry = &this->table[i];
        if (!entry->key.empty()) {
            entry->key = "";
            entry->intArray.clear();
        }
    }
    this->occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const {
    int id = this->Hash(key);
    for (int i = 0; i < tableSize; i++) {
        id = (id + i*i) % tableSize;
        HashData data = table[id];
        // if any id is empty while traversing, it cannot exists.
        if (data.key.empty())
            return false; 
        else if (data.key == key) {
            for (int j = 0; j < data.intArray.size(); j++) {
                valueOut.push_back(data.intArray[j]);
            }
            return true;
        }
    }
    return false;
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


bool KeyedHashTable::isFull() const {
    return (tableSize == occupiedElementCount) ? true : false;
}

int KeyedHashTable::get_available_id(const std::string &key) const {
    if (this->isFull())
        return -1;

    // If table is not full (which is handled above)
    // it should always be returning an available spot.
    int id = this->Hash(key);
    int p = 0;
    while (true) {
        id = (id + p*p) % tableSize;
        HashData data = table[id];
        if (data.key.empty() or data.key == REMOVED_KEY)
            break; 
        p++;
    }
    return id;
}

HashData* KeyedHashTable::get(const std::string& key) {
    int id = this->Hash(key);
    HashData data;
    for (int i = 0; i < tableSize; i++) {
        id = (id + i*i) % tableSize;
        data = table[id];
        // if any id is empty while traversing, it cannot exists.
        if (data.key.empty())
            return NULL;
        else if (data.key == key) {
            return &table[id];
        }
    }
    return NULL;
}
