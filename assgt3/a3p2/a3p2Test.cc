#include "a3p2.h"
#include "gtest/gtest.h"
TEST(StackForm, ChunkSizeAboveZero) {
    Stack s;
    s.chunkSize = -1;
    EXPECT_DEATH(isValidStack(s), "");
}
TEST(StackForm, TopEltGreaterThanChunkSize) {
    Stack s;
    s.chunkSize = 1;
    s.topElt = 2;
    EXPECT_DEATH(isValidStack(s), "");
}
TEST(StackForm, EmptyStackWithBadTopElt) {
    Stack s{nullptr, 1};
    EXPECT_TRUE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
}
TEST(StackForm, StackCannotStoreSpecialUnusedSlotValue) {
    Stack s;
    initStack(1, s);
    s.firstChunk = createNewNodeChunk(1);
    s.topElt = 0;
    s.firstChunk->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    s.firstChunk->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}
TEST(StackForm, UnusedStackSlotsShouldNotHaveGhostValues) {
    Stack s;
    initStack(5, s);
    s.firstChunk = createNewNodeChunk(5);
    s.topElt = 2;
    s.firstChunk->val[s.topElt+1] = "ghost value should not be here";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}
TEST(StackForm, SubsequentChunkShouldNotHaveUnusedSlots) {
    Stack s;
    initStack(1, s);
    s.topElt = 0;
    s.firstChunk = createNewNodeChunk(1);
    s.firstChunk->val[0] = "beta";
    s.firstChunk->next = createNewNodeChunk(1);
    s.firstChunk->next->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    s.firstChunk->next->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->next->val;
    delete s.firstChunk->next;
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}
TEST(EndToEnd, GivenOneItemIsPushedTheSameItemExpectedAtTop) {
    Stack s;
    initStack(3, s);
    std::string expected = "alpha";
    push(expected, s);
    EXPECT_EQ(expected, top(s));
    nuke(s);
}
TEST(EndToEnd, GivenTwoPushedElementsTheSecondItemExpectedAtTop) {
    Stack s;
    initStack(3, s);
    push("alpha", s);
    std::string expected = "beta";
    push(expected, s);
    EXPECT_EQ(expected, top(s));
    nuke(s);
}
TEST(EndToEnd, GivenTwoPushedElementsCombinationOfTheseTwoIsExpectedFromToString) {
    Stack s;
    initStack(3, s);
    push("alpha", s);
    push("beta", s);
    EXPECT_EQ("[beta, alpha]", toString(s));
    nuke(s);
}
TEST(EndToEnd, GivenTwoPushedElementsWhenPopIsInvokedSecondOneExpectedToRemain) {
    Stack s;
    initStack(3, s);
    push("alpha", s);
    push("beta", s);
    pop(s);
    EXPECT_EQ("alpha", top(s));
    nuke(s);
}
TEST(EndToEnd, GivenTwoPushedElementsTheSizeOfTwoIsExpected) {
    Stack s;
    initStack(3, s);
    push("alpha", s);
    push("beta", s);
    EXPECT_EQ(2, size(s));
    nuke(s);
}
TEST(EndToEnd, GivenTwoPushedElementsWhenSwapIsInvokedSwappedItemsExpectedFromToString) {
    Stack s;
    initStack(3, s);
    push("alpha", s);
    push("beta", s);
    swap(s);
    EXPECT_EQ("[alpha, beta]", toString(s));
    nuke(s);
}
TEST(EndToEnd, MakeMultipleNewChunks) {
    Stack s;
    initStack(1, s);
    push("a", s);
    push("b", s);
    EXPECT_EQ(2, size(s));
    EXPECT_EQ("[b, a]", toString(s));
    EXPECT_EQ("b", top(s));
    swap(s);
    EXPECT_EQ("a", top(s));
    pop(s);
    EXPECT_EQ("b", top(s));
    pop(s);
    EXPECT_TRUE(isEmpty(s));
    nuke(s);
}
TEST(Nuke, WithMultipleChunks) {
    Stack s;
    initStack(1, s);
    push("a", s);
    push("b", s);
    nuke(s);
    EXPECT_TRUE(isValidStack(s) && isEmpty(s));
}