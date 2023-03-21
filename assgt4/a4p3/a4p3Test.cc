#include "gtest/gtest.h"
#include "a4p3.h"
#include <deque>
#include <algorithm>
TEST(initPub, givenUninitializedSBLExpectInitAssignsCorrectValues) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_EQ(sbl.q.first, nullptr);
    EXPECT_EQ(sbl.q.last, nullptr);
    EXPECT_EQ(sbl.root, nullptr);
    EXPECT_EQ(sbl.numElts, 0);
}
TEST(sizePub, givenEmptySBLExpectSizeIsZero) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_EQ(SBL_size(sbl), 0);
}
TEST(sizePub, givenOneElementSBLExpectSizeIsOne) {
    SBL sbl;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    sbl.numElts = 1;
    EXPECT_EQ(SBL_size(sbl), 1);
    delete sbl.root;
}
TEST(arrivePub, givenFourArrivalsExpectCorrectlyConstructedSBL) {
    SBL sbl;
    SBL_init(sbl);
    SBL_arrive(sbl, "first");
    SBL_arrive(sbl, "second");
    SBL_arrive(sbl, "third");
    SBL_arrive(sbl, "fourth");
    EXPECT_EQ(sbl.numElts, 4);
    EXPECT_NE(sbl.q.last, nullptr);
    ASSERT_NE(sbl.q.first, nullptr);
    ASSERT_NE(sbl.root, nullptr);
    Queue q = sbl.q;
    EXPECT_EQ(q.first->name, "first");
    ASSERT_NE(q.first->next, nullptr);
    EXPECT_EQ(q.first->next->name, "second");
    ASSERT_NE(q.first->next->next, nullptr);
    EXPECT_EQ(q.first->next->next->name, "third");
    ASSERT_NE(q.first->next->next->next, nullptr);
    EXPECT_EQ(q.first->next->next->next->name, "fourth");
    ASSERT_EQ(q.first->next->next->next->next, nullptr);
    EXPECT_EQ(q.first->next->next->next, q.last);
    BST bst = sbl.root;
    EXPECT_EQ(bst->name, "first");
    EXPECT_EQ(bst->left, nullptr);
    ASSERT_NE(bst->right, nullptr);
    EXPECT_EQ(bst->right->name, "second");
    ASSERT_NE(bst->right->left, nullptr);
    ASSERT_NE(bst->right->right, nullptr);
    EXPECT_EQ(bst->right->right->name, "third");
    EXPECT_EQ(bst->right->right->left, nullptr);
    EXPECT_EQ(bst->right->right->right, nullptr);
    EXPECT_EQ(bst->right->left->name, "fourth");
    EXPECT_EQ(bst->right->left->left, nullptr);
    EXPECT_EQ(bst->right->left->right, nullptr);
    EXPECT_EQ(q.first, bst);
    EXPECT_EQ(q.first->next, bst->right);
    EXPECT_EQ(q.first->next->next, bst->right->right);
    EXPECT_EQ(q.first->next->next->next, bst->right->left);
    delete q.first->next->next->next;
    delete q.first->next->next;
    delete q.first->next;
    delete q.first;
}
TEST(removePub, givenEmptySBLExpectRemoveDies) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_DEATH(SBL_leave(sbl), "Error, SBL is empty.");
}
TEST(removePub, givenOneElementSBLExpectRemoveLeavesItEmpty) {
    SBL sbl;
    sbl.numElts = 1;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    SBL_leave(sbl);
    EXPECT_EQ(sbl.numElts, 0);
    EXPECT_EQ(sbl.root, nullptr);
    EXPECT_EQ(sbl.q.first, nullptr);
    EXPECT_EQ(sbl.q.last, nullptr);
}
TEST(firstPub, givenEmptySBLExpectFirstDies) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_DEATH(SBL_first(sbl), "Error, SBL is empty.");
}
TEST(firstPub, givenOneElementSBLExpectFirstGivesTheOneElement) {
    SBL sbl;
    sbl.numElts = 1;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    EXPECT_EQ(SBL_first(sbl), "test");
    delete sbl.root;
}
TEST(hasPub, gienEmptySBLExpectHasIsFalse) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_FALSE(SBL_has(sbl, "testInput"));
}
TEST(hasPub, givenOneElementSBLExpectItHasThatOneElement) {
    SBL sbl;
    sbl.numElts = 1;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    EXPECT_TRUE(SBL_has(sbl, "test"));
    delete sbl.root;
}
TEST(toArrivalOrderStringPub, givenEmptySBLExpectArrivalOrderStringIsEmpty) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_EQ(SBL_toArrivalOrderString(sbl), "[]");
}
TEST(toArrivalOrderStringPub, givenOneElementSBLExpectArrivalOrderStringContainsThatElement) {
    SBL sbl;
    sbl.numElts = 1;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    EXPECT_EQ(SBL_toArrivalOrderString(sbl), "[test]");
    delete sbl.root;
}
TEST(toArrivalOrderStringPub, givenThreeElementSBLExpectCorrectArrivalOrderString) {
    SBLnode* alice = new SBLnode{"alice", nullptr, nullptr, nullptr};
    SBLnode* bob = new SBLnode{"bob", nullptr, nullptr, nullptr};
    SBLnode* charlie = new SBLnode{"charlie", nullptr, nullptr, nullptr};
    SBL sbl;
    sbl.numElts = 3;
    sbl.q.first = sbl.root = bob;
    bob->left = alice;
    bob->right = charlie;
    bob->next = alice;
    alice->next = charlie;
    sbl.q.last = charlie;
    EXPECT_EQ(SBL_toArrivalOrderString(sbl), "[bob, alice, charlie]");
    delete alice;
    delete bob;
    delete charlie;
}
TEST(toLexicographicalOrderStringPub, givenEmptySBLExpectLexicographicalOrderStringIsEmpty) {
    SBL sbl;
    SBL_init(sbl);
    EXPECT_EQ(SBL_toLexicographicalOrderString(sbl), "[]");
}
TEST(toLexicographicalOrderStringPub, givenOneElementSBLExpectLexicographicalOrderStringContainsThatElement) {
    SBL sbl;
    sbl.numElts = 1;
    sbl.q.first = sbl.q.last = sbl.root = new SBLnode{"test", nullptr, nullptr, nullptr};
    EXPECT_EQ(SBL_toLexicographicalOrderString(sbl), "[test]");
    delete sbl.root;
}
TEST(toLexicographicalOrderStringPub, givenThreeElementSBLExpectCorrectLexicographicalOrderString) {
    SBLnode* alice = new SBLnode{"alice", nullptr, nullptr, nullptr};
    SBLnode* bob = new SBLnode{"bob", nullptr, nullptr, nullptr};
    SBLnode* charlie = new SBLnode{"charlie", nullptr, nullptr, nullptr};
    SBL sbl;
    sbl.numElts = 3;
    sbl.q.first = sbl.root = bob;
    bob->left = alice;
    bob->right = charlie;
    bob->next = alice;
    alice->next = charlie;
    sbl.q.last = charlie;
    EXPECT_EQ(SBL_toLexicographicalOrderString(sbl), "[alice, bob, charlie]");
    delete alice;
    delete bob;
    delete charlie;
}
TEST(nukePub, givenEmptySBLExpectNukeDoesNothing) {
    SBL sbl;
    SBL_init(sbl);
    SBL_nuke(sbl);
}
TEST(nukePub, givenThreeElementSBLExpectNukeCleansItUp) {
    SBLnode* alice = new SBLnode{"alice", nullptr, nullptr, nullptr};
    SBLnode* bob = new SBLnode{"bob", nullptr, nullptr, nullptr};
    SBLnode* charlie = new SBLnode{"charlie", nullptr, nullptr, nullptr};
    SBL sbl;
    sbl.numElts = 3;
    sbl.q.first = sbl.root = bob;
    bob->left = alice;
    bob->right = charlie;
    bob->next = alice;
    alice->next = charlie;
    sbl.q.last = charlie;
    SBL_nuke(sbl);
}
static std::string join(const std::deque<std::string>& els, int start, int end) {
    std::string res, sep;
    for (int i = start; i <= end; i++) res += sep + els[i], sep = ", ";
    return '[' + res + ']';
}
static std::string sortedJoin(std::deque<std::string> els) {
    std::stable_sort(els.begin(), els.end());
    return join(els, 0, els.size() - 1);
}
TEST(All, All) {
    SBL sbl{};
    std::deque<std::string> els{"e", "b", "a", "d", "c", "h", "f", "i", "j", "g", "ab", "def", "sadfa", "y", "zz", "ey"};
    for (auto it = els.begin(); it != els.end(); ++it) {
        SBL_arrive(sbl, *it);
        EXPECT_TRUE(SBL_has(sbl, *it));
        EXPECT_FALSE(SBL_has(sbl, "ea"));
        EXPECT_EQ(SBL_toArrivalOrderString(sbl), join(els, 0, it - els.begin()));
    }
    for (auto& s : els) {
        EXPECT_EQ(SBL_first(sbl), s);
        SBL_leave(sbl);
        els.pop_front();
        EXPECT_EQ(SBL_toArrivalOrderString(sbl), join(els, 0, els.size() - 1));
        EXPECT_EQ(SBL_toLexicographicalOrderString(sbl), sortedJoin(els));
    }
    EXPECT_EQ(SBL_size(sbl), 0);
    SBL_nuke(sbl);
}