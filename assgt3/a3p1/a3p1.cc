#include "a3p1.h"
#include <string>
#include <cassert>
void initStew(Stew& q) {
    q.first = q.last = nullptr;
}
bool isEmpty(const Stew& q) {
    return !q.first && !q.last;
}
bool isValidNode(const Node& n) {
    assert(n.prev != &n && n.next != &n && (!n.prev || n.prev != n.next));
    return true;
}
bool isValidStew(const Stew& s) {
    assert(!s.first == !s.last);
    for (auto n = s.first; n; n = n->next) isValidNode(*n), assert(!n->next || n->next->prev == n);
    for (auto n = s.last; n; n = n->prev) assert(!n->prev || n->prev->next == n);
    return true;
}
static void link(Node* n1, Node* n2) {
    if (n1) n1->next = n2;
    if (n2) n2->prev = n1;
}
void addFront(Stew& q, std::string val) {
    Node* node = new Node{val};
    link(node, q.first);
    q.first = node;
    if (!q.last) q.last = node;
}
void addBack(Stew& q, std::string val) {
    Node* node = new Node{val};
    link(q.last, node);
    q.last = node;
    if (!q.first) q.first = node;
}
void leaveFront(Stew& q) {
    assert(!isEmpty(q));
    auto next = q.first->next;
    delete q.first;
    link(nullptr, q.first = next);
    if (!next) q.last = next;
}
void leaveBack(Stew& q) {
    assert(!isEmpty(q));
    auto prev = q.last->prev;
    delete q.last;
    link(q.last = prev, nullptr);
    if (!prev) q.first = prev;
}
std::string peekBack(const Stew& q) {
    assert(!isEmpty(q));
    return q.last->val;
}
std::string peekFront(const Stew& q) {
    assert(!isEmpty(q));
    return q.first->val;
}
std::string toString(const Stew& q, char direction) {
    std::string res, sep;
    if (direction != 'f' && direction != 'r') return res + "Error, illegal direction: (" + direction + ')';
    for (auto n = direction == 'f' ? q.first : q.last; n; n = direction == 'f' ? n->next : n->prev) res += sep + n->val, sep = ", ";
    return '[' + res + ']';
}
void nuke(Stew& q) {
    while (q.last) leaveBack(q);
}