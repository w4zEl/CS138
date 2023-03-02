#include "a3p1.h"
#include "gtest/gtest.h"
TEST(IsValidNode, GivenOneValidNodeInvokedIsValidNodeExpectedTrueReturnValue) {
    EXPECT_TRUE(isValidNode({"alpha"}));
}
TEST(IsValidNode, GivenTwoConnectedNodesInvokedIsValidNodeExpectedTrueReturnValue) {
    Node n1{"alpha"}, n2{"beta"};
    n1.next = &n2;
    n2.prev = &n1;
    EXPECT_TRUE(isValidNode(n1));
    EXPECT_TRUE(isValidNode(n2));
}
TEST(IsValidNode, GivenSelfCycleNodeInNextInvokedIsValidNodeExpectedFalseAssertion) {
    Node n{"alpha", &n};
    EXPECT_DEATH(isValidNode(n), "");
}
TEST(IsValidNode, GivenSelfCycleNodeInPrevInvokedIsValidNodeExpectedFalseAssertion) {
    Node n{"alpha", nullptr, &n};
    EXPECT_DEATH(isValidNode(n), "");
}
TEST(IsValidNode, GivenNotSimpleGraphInvokedIsValidNodeExpectedFalseAssertion) {
    Node n1{"alpha"}, n2{"beta", &n1, &n1};
    EXPECT_DEATH(isValidNode(n2), "");
}
TEST(IsValidStew, GivenEmptyStewInvokedIsValidStewAndIsEmptyExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    EXPECT_TRUE(isEmpty(s));
    EXPECT_TRUE(isValidStew(s));
}
TEST(IsValidStew, GivenOneNodeInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    Node n1{"alpha"};
    s.first = s.last = &n1;
    EXPECT_TRUE(isValidStew(s));
}
TEST(IsValidStew, GivenTwoConnectedNodesInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    Node n1{"alpha"}, n2{"beta"};
    n1.next = &n2;
    n2.prev = &n1;
    s.first = &n1;
    s.last = &n2;
    EXPECT_TRUE(isValidStew(s));
}
TEST(IsValidStew, GivenThreeConnectedNodesInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    Node n1{"alpha"}, n2{"beta"}, n3{"gamma"};
    n1.next = &n2;
    n2.next = &n3;
    n2.prev = &n1;
    n3.prev = &n2;
    s.first = &n1;
    s.last = &n3;
    EXPECT_TRUE(isValidStew(s));
}
TEST(IsValidStew, GivenNullptrFirstAndNotNullLastInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1{"alpha"};
    s.last = &n1;
    EXPECT_DEATH(isValidStew(s), "");
}
TEST(IsValidStew, GivenNullptrLastAndNotNullFirstInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1{"alpha"};
    s.first = &n1;
    EXPECT_DEATH(isValidStew(s), "");
}
TEST(IsValidStew, GivenSelfCycleFirstNodeInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1{"alpha", &n1};
    s.first = s.last = &n1;
    EXPECT_DEATH(isValidStew(s), "");
}
TEST(IsValidStew, GivenTwoNodesAndNullptrNextForFirstInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1{"alpha"}, n2{"beta"};
    s.first = &n1;
    s.last = &n2;
    s.last->prev = &n1;
    EXPECT_DEATH(isValidStew(s), "");
}
TEST(IsValidStew, GivenTwoNodesAndNullptrPrevForLastInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1{"alpha"}, n2{"beta"};
    s.first = &n1;
    s.last = &n2;
    s.first->next = &n2;
    EXPECT_DEATH(isValidStew(s), "");
}
TEST(Front, GivenEmptyStackThenExpectPeekFrontFails) {
    Stew s1;
    initStew(s1);
    EXPECT_DEATH(peekFront(s1), "");
}
TEST(Front, GivenEmptyStackThenExpectLeaveFrontFails) {
    Stew s1;
    initStew(s1);
    EXPECT_DEATH(leaveFront(s1), "");
}
TEST(Front, GivenOneElementIsAddedToFrontThenExpectItAtBothEnds) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    EXPECT_EQ(s1.first, s1.last);
    ASSERT_NE(s1.first, nullptr);
    EXPECT_EQ(nullptr, s1.first->next);
    EXPECT_EQ(nullptr, s1.first->prev);
    EXPECT_EQ("alpha", s1.first->val);
    nuke(s1);
}
TEST(Front, GivenOneElementIsAddedToFrontThenExpectItPeekingBothEnds) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    EXPECT_EQ("alpha", peekFront(s1));
    EXPECT_EQ("alpha", peekBack(s1));
    nuke(s1);
}
TEST(Front, GivenAddLeaveThenExpectEmpty) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    leaveFront(s1);
    EXPECT_TRUE(isEmpty(s1));
}
TEST(Front, GivenThreeElementsAreAddedToFrontWhenLeaveFrontIsInvokedFirstIsExpectedToBeTheSecondOneThatAdded) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    addFront(s1, "beta");
    addFront(s1, "delta");
    leaveFront(s1);
    EXPECT_EQ("beta", peekFront(s1));
    nuke(s1);
}
TEST(Front, GivenThreeElementsAreAddedToFrontWhenLeaveFrontIsInvokedFirstIsExpectedToBeTheFirstOneThatAdded) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    addFront(s1, "beta");
    addFront(s1, "delta");
    leaveFront(s1);
    EXPECT_EQ("alpha", peekBack(s1));
    nuke(s1);
}
TEST(Back, GivenEmptyStackThenExpectPeekBackFails) {
    Stew s1;
    initStew(s1);
    EXPECT_DEATH(peekBack(s1), "");
}
TEST(Back, GivenEmptyStackThenExpectLeaveBackFails) {
    Stew s1;
    initStew(s1);
    EXPECT_DEATH(leaveBack(s1), "");
}
TEST(Back, GivenOneElementIsAddedToBackThenExpectItAtBothEnds) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");
    EXPECT_EQ(s1.first, s1.last);
    ASSERT_NE(s1.first, nullptr);
    EXPECT_EQ(nullptr, s1.first->next);
    EXPECT_EQ(nullptr, s1.first->prev);
    EXPECT_EQ("alpha", s1.first->val);
    nuke(s1);
}
TEST(Back, GivenOneElementIsAddedToBackThenExpectItPeekingBothEnds) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");
    EXPECT_EQ("alpha", peekFront(s1));
    EXPECT_EQ("alpha", peekBack(s1));
    nuke(s1);
}
TEST(Back, GivenThreeElementsAreAddedToBackWhenLeaveBackIsInvokedLastIsExpectedToBeTheSecondOneThatAdded) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");
    addBack(s1, "beta");
    addBack(s1, "delta");
    leaveBack(s1);
    EXPECT_EQ("beta", peekBack(s1));
    nuke(s1);
}
TEST(ToString, GivenIllegaDirectionToToStringTheErrorMessageIsExpected) {
    Stew s1;
    initStew(s1);
    EXPECT_EQ("Error, illegal direction: (k)", toString(s1, 'k'));
}
TEST(ToString, GivenEmptyListWhenToStringIsInvokedAnEmptyStringIsExpected) {
    Stew s1;
    initStew(s1);
    EXPECT_EQ("[]", toString(s1, 'f'));
}
TEST(ToString, GivenAnElementAddedWithAddFrontWhenToStringIsInvokedTheSameItemExpectedInTheString) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    EXPECT_EQ("[alpha]", toString(s1, 'f'));
    nuke(s1);
}
TEST(ToString, GivenAnElementAddedToFrontAndOneFromBackWhenReverseToStringIsInvokedFirstIsExpectedToBeAfterSecond) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");
    addBack(s1, "delta");
    EXPECT_EQ("[delta, alpha]", toString(s1, 'r'));
    nuke(s1);
}
TEST(ToString, GivenAnElementAddedToFrontAndOneFromBackWhenToStringIsInvokedSecondIsExpectedToBeAfterFirst) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");
    addBack(s1, "delta");
    EXPECT_EQ("[alpha, delta]", toString(s1, 'f'));
    nuke(s1);
}
TEST(Nuke, GivenAnElementAddedToFrontWhenNukeIsInvokedAnEmptyListIsExpected) {
    Stew s1;
    initStew(s1);
    addFront(s1, "alpha");
    nuke(s1);
    EXPECT_TRUE(isEmpty(s1));
}