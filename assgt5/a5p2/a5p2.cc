#include <string>
#include <cassert>
#include "a5p2.h"
LexTree::LexTree() : isWord() {}
LexTree::~LexTree() {
    for (auto &p : children) delete p.second;
}
bool LexTree::isValid() const {
    for (auto& [c, node] : children) assert(c >= 'a' && c <= 'z' && (node->children.size() || node->isWord) && node->isValid());
    return true;
}
void LexTree::addWord (const std::string& s) {
    auto node = this;
    for (char c : s) {
        auto& next = node->children[c | 32];
        node = (next = next ? next : new LexTree);
    }
    node->isWord = true;
}
bool LexTree::hasWord(const std::string& s) const {
    auto node = this;
    for (char c : s) {
        if (!node->children.count(c |= 32)) return false;
        node = node->children.at(c);
    }
    return node->isWord;
}
std::string LexTree::toString(std::string prefix) const {
	std::string res;
    if (isWord) res += prefix + '\n';
    for (auto& [c, node] : children) res += node->toString(prefix + c);
	return res;
}
std::string LexTree::toString() const {
    return toString("");
}