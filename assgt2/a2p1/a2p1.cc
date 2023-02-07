#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main() {
    int N, len = 0, k;
    std::string filename, justify = "rr", print = "f", s, search;
    std::cin >> N >> filename;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    std::ifstream fileIn(filename);
    if (!fileIn) return std::cerr << "Error, cannot open specified text file.\n", 1;
    std::vector<std::vector<std::string>> lines;
    for (std::vector<std::string> line; fileIn;) {
        if (fileIn >> s, len && (!fileIn || len + s.size() + line.size() > N)) lines.push_back(line), line.clear(), len = 0;
        if (fileIn) line.push_back(s = s.substr(0, N)), len += s.size();
    }
    while (std::cin >> s) {
        if (s == "rr" || s == "rl" || s == "c" || s == "j") justify = s;
        else if (s == "f" || s == "r") print = s;
        else if (s == "p" || s == "k" || s == "s") {
            s == "k" && std::cin >> k, s == "s" && std::cin >> search;
            for (int i = 0; i < lines.size(); ++i) {
                int idx = print == "f" ? i : lines.size() - 1 - i, len = 0;
                for (const auto& s : lines[idx]) len += s.size();
                int delims = lines[idx].size() > 1 ? lines[idx].size() - 1 : 1, spaces = N - len, outerSpaces = spaces - lines[idx].size() + 1, extra = spaces % delims;
                std::string line(justify == "rl" ? outerSpaces : justify == "c" ? outerSpaces + 1 >> 1 : 0, ' ');
                for (int j = 0; j < lines[idx].size(); j++) (line += lines[idx][j]).append(justify == "j" ? spaces / delims * (j < delims) + (j < extra) : j + 1 < lines[idx].size(), ' ');
                line.append(justify == "c" ? outerSpaces / 2 : justify == "rr" ? outerSpaces : 0, ' ');
                if (s == "p" || s == "k" && i == k || s == "s" && line.find(search) < line.size()) std::cout << line << '\n';
            }
        } else if (s == "q") break;
        else return std::cerr << "Error, command is illegal.\n", 1;
    }
    return 0;
}