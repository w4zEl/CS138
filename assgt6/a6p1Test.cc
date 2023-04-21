#include <string>
#include "gtest/gtest.h"
#include "a6p1.h"
TEST(SimpleHashTablePub, testConstructorsPub) {
    SimpleHashTable ht1;
    EXPECT_EQ(ht1.getTableSize(), 1000);
    for(int i = 1; i < 20; ++i) {
        SimpleHashTable ht2{i};
        EXPECT_EQ(ht2.getTableSize(), i);
    }
}
TEST(SimpleHashTablePub, testHashFunctionPub) {
    SimpleHashTable ht;
    EXPECT_EQ(ht.hash("abc"), 'a' + 'b' + 'c');
}
TEST(removePub, testRemoveMissingElementDoesNothing) {
    SimpleHashTable ht;
    ht.insert("one");
    ht.insert("two");
    ht.remove("three");
    EXPECT_EQ(ht.toString(), std::to_string('o' + 'n' + 'e') + ": one\n" + std::to_string('t' + 'w' + 'o') + ": two\n");
}
TEST(removePub, testRemovingTheOnlyElementLeavesEmptyHT) {
    SimpleHashTable ht;
    ht.insert("one");
    ht.remove("one");
    EXPECT_EQ(ht.toString(), "");
}
TEST(insertPub, testInsertSimpleFile) {
    SimpleHashTable ht;
    std::ifstream file{"test.txt"};
    ht.insert(file);
    EXPECT_EQ(ht.toString(), std::to_string('o' + 'n' + 'e') + ": one\n" + std::to_string('t' + 'w' + 'o') + ": two\n");
}
TEST(removePub, remove) {
    SimpleHashTable ht;
    ht.insert("ac");
    EXPECT_EQ(ht.toString(), "196: ac\n");
    ht.insert("bb");
    EXPECT_EQ(ht.toString(), "196: bb ac\n");
    ht.remove("ca");
    EXPECT_EQ(ht.toString(), "196: bb ac\n");
    ht.remove("ac");
    EXPECT_EQ(ht.toString(), "196: bb\n");
    ht.remove("bb");
    EXPECT_EQ(ht.toString(), "");
}