#ifndef HASHSTRINGTABLE_H
#define HASHSTRINGTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#define REMOVED "XXX"

using namespace std;

class HashStringTable{
public:
    // Constructor that initializes the elements as a vector of size 11 with "" values.
    // It also initializes other private data members.
    HashStringTable();

    // Adds string value to elements. It first checks the load factor.
    // If the load factor of elements is >=0.75 then the size is doubled and all data are rehashed. 
    // During insertion duplicate values are ignored (i.e. they are not added to the hash table).
    void add(string value);

    // Returns the size of the hash table.
    int get_size();

    // Returns the number of data values in the hash table.
    int get_count();

    // Returns the average number of probes for successful search.
    double get_avgProbe();

    // Returns the average number of probes for unsuccessful search.
    double get_unsuccessProbe();

    // Returns true if the string value is in the hash table; false otherwise.
    bool contains(string value);

    // Returns true if the string value is removed successfully from the hash table; false otherwise.
    // For the deleted items, you should use the "REMOVED" macro.
    bool remove(string value);

private:
    vector<string> elements; // the hash table implemented as a vector
    int cnt; // current number of items in the table
    int total_probes; // total number of probes that helps calculating the average number of probes for successful search

    // Hash function that finds the hash code corresponding to string str.
    // It should map the given string to an integer value between 0 and "hashTableSize - 1".
    // Make sure that your hash function uses all characters of the string in the computation.
    int hashcode(string str);

    // Resizes the hash table by doubling its size. The new size will be "(oldSize * 2) + 1".
    void rehash();

    double get_load_factor();
    int get_id(std::string value);
};

HashStringTable::HashStringTable() {
    elements.resize(11, "");
    cnt = 0;
    total_probes = 0;
}

void HashStringTable::add(string value) {
    if (contains(value))
        return;
    
    if (this->get_load_factor() >= 0.75) 
        this->rehash();

    int i = 0;
    int id = this->hashcode(value);
    int index;
    while (true) {
        index = (id + i) % this->get_size();
        if (this->elements[index] == "" or this->elements[index] == REMOVED) {
            this->elements[index] = value;
            cnt++;
            break;
        }
        i++;
    }
    total_probes += i;
}

int HashStringTable::get_size() {
    return elements.size();
}

int HashStringTable::get_count() {
    return cnt;
}

double HashStringTable::get_avgProbe() {
    return (cnt == 0) ? 1 : (double)total_probes/(double)cnt;
}

double HashStringTable::get_unsuccessProbe() {
    double lambda = this->get_load_factor();
    double avg = 1.0 / (1.0 - lambda);
    return avg;
}

bool HashStringTable::contains(string value) {
    return (this->get_id(value) == -1) ? false : true;
}

bool HashStringTable::remove(string value) {
    int id = this->get_id(value);
    if (id == -1)
        return false;
    this->elements[id] = REMOVED;
    cnt--;
    return true;
}

int HashStringTable::hashcode(string str) {
    int h = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        h = 31 * h + str[i];
    }
    h %= elements.size();
    if (h < 0)   /* in case overflows occurs */
        h += elements.size();

    return h;
}

void HashStringTable::rehash() {
    std::vector<string> items;

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] != "" and elements[i] != REMOVED)
            items.push_back(elements[i]);
    }

    int new_size = this->get_size() * 2 + 1;
    elements.clear();
    elements.resize(new_size, "");
    
    for (int i = 0; i < items.size(); i++) {
        this->add(items[i]);
    }
    cnt -= items.size();
}

// UDF

double HashStringTable::get_load_factor() {
    return (double)this->get_count() / (double)this->get_size();
}

int HashStringTable::get_id(std::string value) {
    int id = this->hashcode(value);
    int index;
    for (int i = 0; i < this->get_size(); i++) {
        index = (id + i) % this->get_size();
        if (this->elements[index] == value)
            return index;
    }
    return -1;
}

#endif //HASHSTRINGTABLE_H
