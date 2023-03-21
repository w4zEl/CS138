#include <string>
typedef struct BST_Node {
    std::string key;
    BST_Node *left, *right;
} *BST;
void BST_init (BST& root);
bool BST_isEmpty (const BST& root);
bool BST_has (const BST& root, std::string key);
void BST_insert (BST& root, std::string key);
void BST_print (const BST& root);
void BST_remove (BST& root, std::string key);
void BST_nuke (BST & root);