#include <string>
#include <vector>
#include "a2p2.h"
#include "gtest/gtest.h"
TEST(TestMakeList, SimpleList) {
    std::vector<std::string> input{"alice", "bob"};
    Node *out = makeList(input);
    EXPECT_EQ("alice", out->val);
    EXPECT_EQ("bob", out->next->val);
    EXPECT_TRUE(out->next->next == nullptr);
}
TEST(TestList2String, SimpleList) {
    std::vector<std::string> input{"alice", "bob"};
    Node *out = makeList(input);
    EXPECT_EQ("alice bob", list2string(out));
}
TEST(TestPair2String, SimpleList) {
    Node *p1 = new Node{"alpha"}, *p2 = new Node{"omega"};
    EXPECT_EQ("alpha omega", pair2sortedString(p1, p2));
    EXPECT_EQ("alpha omega", pair2sortedString(p2, p1));
}
TEST(TestPair2String, DeathTest) {
    EXPECT_DEATH(pair2sortedString(new Node, nullptr), "Assertion");
    EXPECT_DEATH(pair2sortedString(nullptr, nullptr), "Assertion");
}
TEST(TestSorting, SimpleList) {
    Node *p1 = new Node{"alpha"}, *p2 = new Node{"omega"};
    EXPECT_EQ("alpha omega", list2string(makeSortedPairList(p1->val, p2->val)));
    EXPECT_EQ("alpha omega", list2string(sortPair(p1, p2)));
}
TEST(TestSorting, SimpleListRev) {
    Node *p1 = new Node{"omega"}, *p2 = new Node{"alpha"};
    EXPECT_EQ("alpha omega", list2string(makeSortedPairList(p1->val, p2->val)));
    EXPECT_EQ("alpha omega", list2string(sortPair(p1, p2)));
}
TEST(TestAppending, SimpleList) {
    std::vector<std::string> list1{"alpha", "baker", "charlie"}, list2{"delta", "echo"};
    EXPECT_EQ("alpha baker charlie delta echo", list2string(append(makeList(list1), makeList(list2))));
}
TEST(TestAppending, WithNull) {
    EXPECT_EQ("alpha beta", list2string(append(nullptr, makeList({"alpha", "beta"}))));
    EXPECT_EQ("alpha beta", list2string(append(makeList({"alpha", "beta"}), nullptr)));
}