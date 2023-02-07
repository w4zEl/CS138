#include <string>
#include <vector>
#include <cassert>
#include "a2p2.h"
Node* makeList (const std::vector<std::string> v) {
    Node *head = v.size() ? new Node{v[0]} : nullptr, *curr = head;
    for (int i = 1; i < v.size(); i++) curr = curr->next = new Node{v[i]};
    return head;
}
std::string list2string (const Node *first) {
    std::string s;
    for (auto curr = first; curr; curr = curr->next) s += (s.size() ? " " : "") + curr->val;
    return s;
}
std::string pair2sortedString (const Node *p1, const Node *p2) {
    assert(p1 && p2);
    return p1->val < p2->val ? p1->val + ' ' + p2->val : p2->val + ' ' + p1->val;
}
Node* sortPair (Node *p1, Node *p2) {
    assert(p1 && p2);
    p1->next = p2->next = nullptr;
    return p1->val < p2->val ? append(p1, p2) : append(p2, p1);
}
Node* makeSortedPairList (const std::string s1, const std::string s2) {
    return sortPair(new Node{s1}, new Node{s2});
}
Node* append (Node *p1, Node *p2) {
    if (!p1) return p2;
    auto last = p1;
    while (last->next) last = last->next;
    last->next = p2;
    return p1;
}