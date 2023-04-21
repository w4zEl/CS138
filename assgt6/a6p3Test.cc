#include "gtest/gtest.h"
#include "a6p3.h"
TEST(scrabbleValueCharPub, testAFewChars) {
    EXPECT_EQ(scrabbleValue('a'), 1);
    EXPECT_EQ(scrabbleValue('b'), 3);
    EXPECT_EQ(scrabbleValue('c'), 3);
}
TEST(scrabbleValueCharPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(scrabbleValue('1'), "Error: Recieved non-alphabetical character '1'");
}
TEST(scrabbleValueStringPub, testEmptyStringHasValueZero) {
    EXPECT_EQ(scrabbleValue(""), 0);
}
TEST(scrabbleValueStringPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(scrabbleValue("2"), "Error: Recieved non-alphabetical character '2'");
}
TEST(bestScrabbleWordPub, bestWordThatCanBeMadeFromNothingIsNothing) {
    EXPECT_EQ(bestScrabbleWord(""), "");
}
TEST(bestScrabbleWordPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(bestScrabbleWord("3"), "Error: Recieved non-alphabetical character '3'");
}
TEST(scrabbleValue, AllAlphabet) {
    EXPECT_EQ(scrabbleValue("abcdefghijKlmnOpqrstuvwxyz"), 87);
}
TEST(bestScrabbleWord, words) {
    EXPECT_EQ(bestScrabbleWord("scrub"), "curbs");
    EXPECT_EQ(bestScrabbleWord("sabaCuad"), "abaCus");
    EXPECT_EQ(bestScrabbleWord("asCbuaza"), "zas");
}