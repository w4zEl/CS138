#ifndef A6P1_H
#define A6P1_H
#include <string>
#include "gtest/gtest.h"
#include "HashTable.h"
class SimpleHashTable : public HashTable {
    public:
        SimpleHashTable();
        SimpleHashTable(int k);
        virtual ~SimpleHashTable();
    private:
	    int hash(std::string key) const;
    FRIEND_TEST(SimpleHashTablePub, testConstructorsPub);
    FRIEND_TEST(SimpleHashTablePub, testHashFunctionPub);
};
#endif
