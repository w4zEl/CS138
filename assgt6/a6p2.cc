#include <string>
#include "a6p2.h"
SmartHashTable::SmartHashTable() : HashTable() {}
SmartHashTable::SmartHashTable(int k) : HashTable(k) {}
SmartHashTable::~SmartHashTable() {}
int SmartHashTable::hash(std::string key) const {
    int h = 0;
    for (unsigned char c : key) h = (h * 31 + c) % getTableSize();
    return h;
}