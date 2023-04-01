#include "a5p2.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <numeric>
#include <cctype>
TEST(defaultCtorPub, defaultCtorShouldMakeEmptyLex) {
    LexTree* lt = new LexTree{};
    EXPECT_FALSE(lt->isWord);
    EXPECT_TRUE(lt->children.empty());
    delete lt;
}
TEST(isValidPub, emptyTreeShouldBeValid) {
    LexTree* lt = new LexTree{};
    EXPECT_TRUE(lt->isValid());
    delete lt;
}
TEST(isValidPub, checkAllLowerCase1) {
    LexTree* lt = new LexTree{};
    lt->children['T'] = new LexTree{}; 
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}
TEST(isValidPub, checkAllLowerCase2) {
    LexTree* lt = new LexTree{};
    lt->children['h'] = new LexTree{};
    lt->children['h']->children['E'] = new LexTree{};
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}
TEST(isValidPub, leafNodeShouldBeWords) {
    LexTree* lt = new LexTree{};
    lt->addWord("hi");
    lt->children['h']->children['i']->isWord = false;
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}
TEST(addWordPub, addAWordAndCheckNodes) {
    LexTree* lt = new LexTree{};
    lt->addWord("to");
    ASSERT_NE(lt->children.find('t'), lt->children.end());
    EXPECT_EQ(lt->children.size(), 1);
    ASSERT_NE(lt->children.at('t')->children.find('o'), lt->children.at('t')->children.end());
    EXPECT_EQ(lt->children.at('t')->children.size(), 1);
    ASSERT_EQ(lt->children.at('t')->children.at('o')->children.size(), 0);
    delete lt;
}
TEST(hasWordPub, addAWordAndCheckIt) {
    LexTree* lt = new LexTree{};
    lt->children.emplace('t', new LexTree{});
    lt->children.at('t')->children.emplace('o', new LexTree{});
    lt->children.at('t')->children.at('o')->isWord = true;
    ASSERT_TRUE(lt->hasWord("to"));
    ASSERT_FALSE(lt->hasWord("t"));
    ASSERT_FALSE(lt->hasWord("o"));
    ASSERT_FALSE(lt->hasWord(""));
    delete lt;
}
TEST(toStringPub, printEmptyLex) {
    LexTree* lt = new LexTree{};
    ASSERT_EQ(lt->toString(), "");
    delete lt;
}
TEST(toStringPub, addOneWordAndPrint) {
    LexTree* lt = new LexTree{};
    lt->children.emplace('m', new LexTree{});
    lt->children.at('m')->children.emplace('a', new LexTree{});
    lt->children.at('m')->children.at('a')->children.emplace('n', new LexTree{});
    lt->children.at('m')->children.at('a')->children.at('n')->isWord = true;
    ASSERT_EQ(lt->toString(), "man\n");
    delete lt;
}
TEST(toStringPub, addTwoWordsAndPrint) {
    LexTree* lt = new LexTree{};
    lt->children.emplace('s', new LexTree{});
    lt->children.at('s')->children.emplace('u', new LexTree{});
    lt->children.at('s')->children.at('u')->children.emplace('p', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.emplace('e', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.at('e')->children.emplace('r', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.at('e')->children.at('r')->isWord = true;
    lt->children.emplace('m', new LexTree{});
    lt->children.at('m')->children.emplace('a', new LexTree{});
    lt->children.at('m')->children.at('a')->children.emplace('n', new LexTree{});
    lt->children.at('m')->children.at('a')->children.at('n')->isWord = true;
    std::string expected_result = "man\n"
                                  "super\n";
    ASSERT_EQ(lt->toString(), expected_result);
    delete lt;
}
TEST(All, All) {
    const std::vector<std::string> words{"plant","momentous","mist","future","shallow","melodic","birth","ancient","certain","puncture","godly","chunky","skate","top","appliance","wobble","miscreant","dance","jump","tenuous","note","road","employ","passenger","interrupt","absent","lackadaisical","size","delight","flood","birds","adhesive","harmonious","ice","flippant","company","pig","heady","effect","reflect","sisters","copy","seashore","cent","highfalutin","unequaled","smart","FEEBLE","pets","didactic","drip","clip","known","wretched","liquid","incredible","juvenile","current","bitter","twist","tawdry","silent","sad","sNatch","fireman","money","dogs","worthless","mother","multiply","military","rustic","trucks","afraid","toy","connection","limping","sticky","difficult","paRALlel","picture","probable","voiceless","dirt","ignorant","behavior","literate","chemical","order","interesting","decay","wool","mourn","visiTOR","stamp","rare","roomy","dog","business","lovely"};
    LexTree tree;
    for (std::vector<std::string>::size_type i = 0; i < words.size(); ++i) {
        tree.addWord(words[i]);
        EXPECT_TRUE(tree.hasWord(words[i]));
        std::vector<std::string> partial(words.begin(), words.begin() + i + 1);
        for (auto& s: partial) std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return std::tolower(c);});
        EXPECT_TRUE(tree.hasWord(partial.back()));
        std::sort(partial.begin(), partial.end());
        std::string sortedStrs = std::accumulate(partial.begin(), partial.end(), std::string(), [](auto a, auto b){return a + b + '\n';});
        EXPECT_EQ(tree.toString(), sortedStrs);
    }
}