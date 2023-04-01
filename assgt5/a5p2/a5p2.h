#include <string>
#include <map>
#include "gtest/gtest.h"
class LexTree {
    public:
        LexTree();
        virtual ~LexTree();
        void addWord (const std::string& s);
        bool hasWord (const std::string& s) const;
        std::string toString() const;
    private:
        bool isWord;
        std::map<char, LexTree*> children;
        bool isValid () const;
        std::string toString(std::string prefix) const;
    FRIEND_TEST(defaultCtorPub, defaultCtorShouldMakeEmptyLex);
    FRIEND_TEST(isValidPub, emptyTreeShouldBeValid);
    FRIEND_TEST(isValidPub, checkAllLowerCase1);
    FRIEND_TEST(isValidPub, checkAllLowerCase2);
    FRIEND_TEST(isValidPub, leafNodeShouldBeWords);
    FRIEND_TEST(addWordPub, addAWordAndCheckNodes);
    FRIEND_TEST(hasWordPub, addAWordAndCheckIt);
    FRIEND_TEST(toStringPub, addOneWordAndPrint);
    FRIEND_TEST(toStringPub, addTwoWordsAndPrint);
};
