#include <string>
#include <fstream>
#include "gtest/gtest.h"
#include "a6p2.h"
TEST(SmartHashTablePub, testConstructorsPub) {
    SmartHashTable ht1;
    EXPECT_EQ(ht1.getTableSize(), 1000);
    for(int i = 1; i < 20; ++i) {
        SmartHashTable ht2{i};
        EXPECT_EQ(ht2.getTableSize(), i);
    }
}
TEST(SmartHashTablePub, testThatTheHashFunctionWorks) {
    SmartHashTable ht;
    ht.insert("abc");
    EXPECT_EQ(ht.toString(), std::to_string(ht.hash("abc")) + ": abc\n");
}
TEST(SmartHashTablePub, printReport) {
    SmartHashTable ht{100000};
    std::ifstream dictionary{"twl-words.txt"};
    ht.insert(dictionary);
    ht.report();
}