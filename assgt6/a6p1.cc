#include <string>
#include <fstream>
#include "HashTable.h"
#include "a6p1.h"
SimpleHashTable::SimpleHashTable() : HashTable() {}
SimpleHashTable::SimpleHashTable(int k) : HashTable(k) {}
SimpleHashTable::~SimpleHashTable() {}
int SimpleHashTable::hash(std::string key) const {
    int sum = 0;
    for (auto c : key) sum = (sum + c) % getTableSize();
    return sum;
}
void HashTable::remove(std::string word) {
    auto &f = table[hash(word)], n = f, p = n;
    for (; n; p = n, n = n->next)
        if (n->word == word) return (n == p ? f : p->next) = n->next, delete n;
}
void HashTable::insert(std::ifstream& file) {
    for (std::string s; file >> s;) insert(s);
}