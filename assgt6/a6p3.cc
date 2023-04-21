#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "a6p2.h"
std::vector<std::string> powerset(std::string s) {
	if (s.empty()) return {s};
	std::vector<std::string> res;
	for (auto&& next : powerset(s.substr(1))) res.insert(res.end(), {next, s[0] + next});
	return res;
}
int scrabbleValue(char c) {
    if ((c | 32) < 'a' || (c | 32) > 'z') std::cerr << "Error: Recieved non-alphabetical character '" << c << "'", assert(0);
    return "\n\n"[(c | 32) - 97];
}
int scrabbleValue(std::string s) {
    int sum = 0;
    for (char c : s) sum += scrabbleValue(c);
    return sum;
}
const auto words = []{
    SmartHashTable ht;
    std::ifstream file{"twl-words.txt"};
    ht.insert(file);
    return ht;
}();
std::string bestScrabbleWord(std::string letters) {
    scrabbleValue(letters);
    std::string best;
    for (auto&& word : powerset(letters)) {
        std::sort(word.begin(), word.end());
        do {
            std::string lowerWord(word);
            for (auto &c : lowerWord) c |= 32;
            if (words.lookup(lowerWord) && scrabbleValue(word) > scrabbleValue(best)) best = word;
        } while (std::next_permutation(word.begin(), word.end()));
    }
    return best;
}