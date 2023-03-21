#include <cassert>
#include "a4p1.h"
void Q_init (Queue& q) {
    q = {};
}
bool Q_isEmpty (const Queue& q) {
    return !q.last;
}
int Q_size (const Queue& q) {
    int sz = 0;
    for (auto n = q.first; n; n = n->next) ++sz;
    return sz;
}
void Q_enter (Queue& q, std::string val) {
    q.last = (q.last ? q.last->next : q.first) = new Qnode{val};
}
std::string Q_first (const Queue& q) {
    assert(q.first);
    return q.first->val;
}
void Q_leave (Queue& q) {
    auto t = q.first;
    assert(t);
    if (!(q.first = t->next)) q.last = {};
    delete t;
}
void Q_nuke (Queue& q) {
    while (q.last) Q_leave(q);
}
void PQ_init (PQ& pq) { 
    pq = {};
}
bool PQ_isEmpty (const PQ& pq) {
    return !pq;
}
void PQ_enter (PQ& pq, std::string val, int priority) {
    PQ prev = pq, curr;
    if (!pq || priority < pq->priority) curr = new PQnode{priority}, curr->next = pq, pq = curr;
    else {
        while (prev->next && prev->next->priority <= priority) prev = prev->next;
        if (prev->priority == priority) curr = prev;
        else curr = new PQnode{priority}, curr->next = prev->next, prev->next = curr;
    }
    Q_enter(curr->q, val);
}
std::string PQ_first (const PQ& pq) {
    assert(pq && "Error, priority queue is empty.");
    return pq->q.first->val;
}
void PQ_leave (PQ& pq) {
    assert(pq && "Error, priority queue is empty.");
    PQ t = pq;
    Q_leave(t->q);
    if (!t->q.last) pq = t->next, delete t;
}
int PQ_size (const PQ& pq) {
    return pq ? Q_size(pq->q) + PQ_size(pq->next) : 0;
}
int PQ_sizeByPriority (const PQ& pq, int priority) {
    PQ p = pq;
    while (p && p->priority < priority) p = p->next;
    return p && p->priority == priority ? Q_size(p->q) : 0;
}
int PQ_numPriorities (const PQ& pq) {
    return pq ? 1 + PQ_numPriorities(pq->next) : 0;
}
void PQ_nuke (PQ & pq) {
    while (pq) PQ_leave(pq);
}