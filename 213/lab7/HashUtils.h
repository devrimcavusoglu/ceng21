#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <string>

#include "HashStringTable.h"

class HashUtils{
public:
    HashUtils() {}

    // Calls addName function to insert entries of the name vector into the hash table.
    void addNameList(vector<string> nameVector) {
        int len = nameVector.size();
        for (int i=0; i<len; i++) {
            addName(nameVector[i]);
        }
        cout << "size = " << hashTable.get_size() << " count = " << hashTable.get_count() << "\n";
    }

    // Calls contains function of the hash table to check whether the hash table contains the entry.
    bool searchName(string name) {
        if (hashTable.contains(name)) {
            cout << name << ": Yes" << "\n";
            return true;
        } else {
            cout << name <<": No" << "\n";
            return false;
        }
    }

    // Calls remove function of the hash table to delete the entry from the hash table.
    void deleteName(string name) {
        if (hashTable.remove(name)) {
            cout << name << " is deleted" << "\n";
        }
        else {
            cout << name <<" does not exist" << "\n";
        }
    }
    
    // Calls add function of the hash table to insert the entry into the hash table.
    void addName(string name) {
        hashTable.add(name);
        cout << name << " is added" << "\n";
    }

    // Lists statistics about the hash table.
    void report() {
        cout << "Table size = " << hashTable.get_size() << "\n";
        cout << "Number of names in the table = " << hashTable.get_count() << "\n";
        cout << "Load factor = " << (double)hashTable.get_count()/hashTable.get_size() << "\n";
    }

private:
    HashStringTable hashTable;
};

#endif //HASHUTILS_H
