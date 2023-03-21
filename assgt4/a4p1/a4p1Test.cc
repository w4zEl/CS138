#include "gtest/gtest.h"
#include "a4p1.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
TEST(isEmptyPub, expectEmptyPQIsEmpty) {
    PQ pq;
    PQ_init(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));
}
TEST(isEmptyPub, expectNonEmptyPQIsNotEmpty) {
    Queue priority1;
    priority1.first = priority1.last = new Qnode{"test"};
    PQ pq = new PQnode{1, priority1};
    EXPECT_FALSE(PQ_isEmpty(pq));
    delete priority1.first;
    delete pq;
}
TEST(enterPub, enterThreeElementsExpectCorrectContents) {
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 2);
    PQ_enter(pq, "b", 1);
    PQ_enter(pq, "c", 4);
    EXPECT_EQ(pq->priority, 1);
    EXPECT_EQ(pq->q.first, pq->q.last);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "b");
    EXPECT_EQ(pq->q.first->next, nullptr);
    ASSERT_NE(pq->next, nullptr);
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    EXPECT_EQ(pq2->q.first, pq2->q.last);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->val, "a");
    EXPECT_EQ(pq2->q.first->next, nullptr);
    ASSERT_NE(pq2->next, nullptr);
    PQ pq3 = pq2->next;
    EXPECT_EQ(pq3->priority, 4);
    EXPECT_EQ(pq3->q.first, pq3->q.last);
    ASSERT_NE(pq3->q.first, nullptr);
    EXPECT_EQ(pq3->q.first->val, "c");
    EXPECT_EQ(pq3->q.first->next, nullptr);
    EXPECT_EQ(pq3->next, nullptr);
    delete pq3->q.first;
    delete pq3;
    delete pq2->q.first;
    delete pq2;
    delete pq->q.first;
    delete pq;
}
TEST(firstPub, givenEmptyPQExpectFirstDies) {
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_first(pq), "Error, priority queue is empty.");
}
TEST(firstPub, givenTheeElementPQExpectFirstGivesCorrectOutput) {
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};
    EXPECT_EQ(PQ_first(pq), "alpha");
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}
TEST(leavePub, givenEmptyPQExpectLeaveDies) {
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_leave(pq), "Error, priority queue is empty.");
}
TEST(leavePub, givenTheeElementPQExpectLeaveRemovesFirst) {
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};
    PQ_leave(pq);
    delete pq->next;
    delete pq;
    delete priority1.last;
    delete priority2.first;
}
TEST(sizePub, givenEmptyPQExpectSizeIsZero) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_size(pq), 0);
}
TEST(sizePub, givenTheeElementPQExpectSizeIsThree) {
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};
    EXPECT_EQ(PQ_size(pq), 3);
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}
TEST(sizeByPriorityPub, givenEmptyPQExpectSizeByPriorityIsZero) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 0);
}
TEST(sizeByPriorityPub, givenTheeElementPQExpectSizeByPriorityIsTwo) {
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 2);
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}
TEST(numPrioritiesPub, givenEmptyPQExpectZeroPriorities) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_numPriorities(pq), 0);
}
TEST(nukePub, givenTheeElementPQExpectNukeCleansUp) {
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};
    PQ_nuke(pq);
    EXPECT_EQ(pq, nullptr);
}
TEST(All, All) {
    PQ pq{};
    std::vector<std::pair<std::string, int>> els{{"a", 1}, {"a2", 1}, {"b", 0}, {"c", 3}, {"b2", 0}, {"b3", 0}, {"d", 2}, {"cc", 3}, {"d2", 2}, {"6", 6}, {"5", 5}, {"55", 5}, {"66", 6}, {"4", 4}, {"-1", -1}, {"8", 8}, {"7", 7}, {"7", 7}};
    std::unordered_map<int, int> freq;
    for (const auto &x : els) {
        PQ_enter(pq, x.first, x.second);
        ++freq[x.second];
    }
    EXPECT_EQ(PQ_size(pq), els.size());
    for (const auto &f : freq)
        EXPECT_EQ(PQ_sizeByPriority(pq, f.first), f.second);
    EXPECT_EQ(PQ_sizeByPriority(pq, -99), 0);
    EXPECT_EQ(PQ_numPriorities(pq), freq.size());
    std::stable_sort(els.begin(), els.end(), [](auto a, auto b){return a.second < b.second;});
    for (const auto& x : els) {
        EXPECT_EQ(PQ_first(pq), x.first);
        PQ_leave(pq);
    }
    EXPECT_TRUE(PQ_isEmpty(pq));
    PQ_nuke(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));
}