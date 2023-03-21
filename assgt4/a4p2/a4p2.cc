#include <iostream>
#include <cassert>
#include "a4p2.h"
void BST_init(BST& root) {
    root = {};
}
bool BST_isEmpty(const BST& root) {
    return !root;
}
bool BST_has(const BST& root, std::string key) {
    return root && (root->key == key || (key < root->key ? BST_has(root->left, key) : BST_has(root->right, key)));
}
void BST_insert(BST& root, std::string key) {
    if (!root) root = new BST_Node{key};
    else if (key < root->key) BST_insert(root->left, key);
    else BST_insert(root->right, key);
}
void BST_print(const BST& root) {
    if (root) BST_print(root->left), std::cout << root->key << '\n', BST_print(root->right);
}
void BST_remove(BST& root, std::string key) {
    BST t = root;
    if (!root) std::cerr << "Error, couldn't find \"" << key << "\" in the BST\n", assert(0);
    if (key < root->key) BST_remove(root->left, key);
    else if (key > root->key) BST_remove(root->right, key);
    else if (!root->left) root = root->right, delete t;
    else if (!root->right) root = root->left, delete t;
    else {
        BST maxLeft = root->left;
        while (maxLeft->right) maxLeft = maxLeft->right;
        BST_remove(root->left, root->key = maxLeft->key);
    }
}
void BST_nuke(BST& root) {
    if (root) BST_nuke(root->left), BST_nuke(root->right), delete root, root = {};
}