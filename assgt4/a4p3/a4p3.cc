#include <string>
#include <cassert>
#include "a4p3.h"
void SBL_init(SBL& sbl) {
    sbl = {};
}
int SBL_size(const SBL& sbl){
    return sbl.numElts;
}
static void BST_insert(BST& root, BST& node) {
    if (!root) root = node;
    else if (node->name < root->name) BST_insert(root->left, node);
    else BST_insert(root->right, node);
}
static void BST_remove(BST& root, BST& node) {
    if (node->name < root->name) BST_remove(root->left, node);
    else if (root != node) BST_remove(root->right, node);
    else if (!root->left) root = root->right;
    else if (!root->right) root = root->left;
    else {
        BST par = root, maxLeft = root->left;
        while (maxLeft->right) par = maxLeft, maxLeft = maxLeft->right;
        if (par != root) par->right = maxLeft->left, maxLeft->left = node->left;
        maxLeft->right = node->right;
        root = maxLeft;
    }
}
void SBL_arrive(SBL& sbl, std::string name) {
    BST node = new SBLnode{name};
    BST_insert(sbl.root, node);
    sbl.q.last = (sbl.q.last ? sbl.q.last->next : sbl.q.first) = node;
    ++sbl.numElts;
}
void SBL_leave(SBL& sbl){ 
    assert(sbl.root && "Error, SBL is empty.");
    auto f = sbl.q.first;
    sbl.q.first = f->next;
    BST_remove(sbl.root, f);
    delete f;
    if (!--sbl.numElts) sbl.q.last = {};
}
std::string SBL_first(const SBL& sbl) { 
    assert(sbl.root && "Error, SBL is empty.");
    return sbl.q.first->name;
}
bool SBL_has(const SBL& sbl, std::string name) {
    for (auto n = sbl.q.first; n; n = n->next) if (n->name == name) return true;
    return false;
}
std::string SBL_toArrivalOrderString(const SBL& sbl) {
    std::string res, sep;
    for (auto n = sbl.q.first; n; n = n->next) res += sep + n->name, sep = ", ";
    return '[' + res + ']';
}
static void BST_toString(const BST& root, std::string& buf) {
    if (root) BST_toString(root->left, buf), buf += (buf.size() ? ", " : "") + root->name, BST_toString(root->right, buf);
}
std::string SBL_toLexicographicalOrderString(const SBL& sbl) {
    std::string res;
    BST_toString(sbl.root, res);
    return '[' + res + ']';
}
void SBL_nuke(SBL& sbl) {
    while (sbl.root) SBL_leave(sbl);
}