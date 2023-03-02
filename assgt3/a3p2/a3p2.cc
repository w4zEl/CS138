#include "a3p2.h"
#include <string>
#include <cassert>
NodeChunk* createNewNodeChunk(const int chunkSize) {
    assert(chunkSize > 0);
    std::string* arr = new std::string[chunkSize];
    for (int i = 0; i < chunkSize; ++i) arr[i] = UNUSED_SLOT;
    return new NodeChunk{arr};
}
void initStack(const int chunkSize, Stack& s){
    assert(chunkSize > 0);
    s = {nullptr, -1, chunkSize};
}
bool isEmpty(const Stack& s) {
    return !s.firstChunk;
}
bool isValidStack(const Stack& s) {
    assert(s.chunkSize > 0 && s.topElt < s.chunkSize && (s.firstChunk ? s.topElt >= 0 : !~s.topElt));
    for (auto curr = s.firstChunk; curr; curr = curr->next)
        for (int i = 0; i < s.chunkSize; ++i)
            assert(curr == s.firstChunk && i > s.topElt ? curr->val[i] == UNUSED_SLOT : curr->val[i] != UNUSED_SLOT);
    return true;
}
void push(const std::string v, Stack& s) {
    auto curr = s.firstChunk;
    if (!curr || s.topElt + 1 == s.chunkSize) (curr = createNewNodeChunk(s.chunkSize))->next = s.firstChunk, s.firstChunk = curr, s.topElt = -1;
    curr->val[++s.topElt] = v;
}
void pop(Stack& s) {
    assert(!isEmpty(s));
    auto first = s.firstChunk;
    first->val[s.topElt] = UNUSED_SLOT;
    if (!s.topElt--) s.topElt = !!(s.firstChunk = first->next) * s.chunkSize - 1, delete[] first->val, delete first;
}
int size(const Stack& s) {
    int size = s.topElt + 1; 
    for (auto curr = s.firstChunk; curr && curr->next; curr = curr->next) size += s.chunkSize;
    return size;
}
void swap(Stack& s) {
    assert(size(s) > 1);
    s.firstChunk->val[s.topElt].swap(s.topElt ? s.firstChunk->val[s.topElt - 1] : s.firstChunk->next->val[s.chunkSize - 1]);
}
std::string toString(const Stack& s) {
    std::string str, sep;
    for (auto curr = s.firstChunk; curr; curr = curr->next) 
        for (int i = curr == s.firstChunk ? s.topElt : s.chunkSize - 1; ~i;)
            str += sep + curr->val[i--], sep = ", ";
    return '[' + str + ']';
}
std::string top(const Stack& s) {
    assert(!isEmpty(s));
    return s.firstChunk->val[s.topElt];
}
void nuke(Stack& s) {
    while (~s.topElt) pop(s);
}