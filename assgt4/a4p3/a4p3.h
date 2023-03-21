#include <string>
struct SBLnode {
    std::string name;
    SBLnode *next, *left, *right;
};
typedef SBLnode Q_Node;
typedef SBLnode BST_Node;
typedef SBLnode* BST;
struct Queue {
    SBLnode *first, *last;
};
struct SBL {
    Queue q;
    BST root; 
    int numElts;
};
void SBL_init (SBL& sbl);
int SBL_size (const SBL& sbl);
void SBL_arrive (SBL& sbl, std::string name);
void SBL_leave (SBL& sbl);
std::string SBL_first (const SBL& sbl);
bool SBL_has (const SBL& sbl, std::string name);
std::string SBL_toArrivalOrderString (const SBL& sbl);
std::string SBL_toLexicographicalOrderString (const SBL& sbl);
void SBL_nuke (SBL& sbl);