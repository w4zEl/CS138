#include "gtest/gtest.h"
#include "a4p2.h"
TEST(removePub, givenEmptyBSTExpectRemoveDies) {
    BST bst;
    BST_init(bst);
    EXPECT_DEATH(BST_remove(bst, "thisStringIsATest"), "Error, couldn't find \"thisStringIsATest\" in the BST");
}
TEST(removePub, givenOneElementBSTExpectRemovingThatElementLeavesBSTEmpty) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "alpha");
    BST_remove(bst, "alpha");
    EXPECT_TRUE(BST_isEmpty(bst));
}
TEST(nukePub, givenEmptyBSTExpectNukeDoesNothing) {
    BST bst;
    BST_init(bst);
    BST_nuke(bst);
}
TEST(nukePub, givenOneElementBSTExpectNukeCleansUp) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "alpha");
    BST_nuke(bst);
}
TEST(All, All) {
    BST bst{};
    const std::string els[]{"e", "b", "a", "d", "c", "h", "f", "i", "j"};
    for (auto& s : els) {
        BST_insert(bst, s);
        EXPECT_TRUE(BST_has(bst, s));
    }
    for (auto& r : {"d", "i", "f", "b", "e"}) {
        BST_remove(bst, r);
        EXPECT_FALSE(BST_has(bst, r));
    }
    BST_nuke(bst);
    EXPECT_TRUE(BST_isEmpty(bst));
}