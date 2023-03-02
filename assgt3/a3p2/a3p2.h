#include <string>
inline constexpr auto UNUSED_SLOT = "__UNUSED_SLOT__";
struct NodeChunk {
    std::string* val;
    NodeChunk* next;
};
struct Stack {
    NodeChunk* firstChunk;
    int topElt, chunkSize;
};
bool isValidStack(const Stack& s);
NodeChunk* createNewNodeChunk(const int chunkSize);
void initStack(const int chunkSize, Stack& s);
bool isEmpty(const Stack& s);
void push(const std::string v, Stack& s);
void pop(Stack& s);
void swap(Stack& s);
int size(const Stack& s);
std::string top(const Stack& s);
std::string toString(const Stack& s);
void nuke(Stack& s);