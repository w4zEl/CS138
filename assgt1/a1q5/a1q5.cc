#include <iostream>
#include <string>
#include <vector>
int main() {
    int N, len = 0;
    std::string c1, c2, s;
    std::cin >> N >> c1 >> c2;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    if (c1 != "rr" && c1 != "j" && c1 != "rl" && c1 != "c" || c2 != "f" && c2 != "r" && c2 != "g") return std::cerr << "Error, command is illegal.\n", 1;
    std::vector<std::string> lines, line;
    while (std::cin) {
        std::cin >> s;
        if (len && (!std::cin || len + s.size() + line.size() > N)) {
            int delims = line.size() > 1 ? line.size() - 1 : 1, spaces = N - len, outerSpaces = spaces - line.size() + 1, extra = spaces % delims;
            std::string curr(c1 == "rl" ? outerSpaces : c1 == "c" ? outerSpaces + 1 >> 1 : 0, ' ');
            for (int i = 0; i < line.size(); i++)
                (curr += line[i]).append(c1 == "j" ? spaces / delims * (i < delims) + (i < extra) : i + 1 < line.size(), ' ');
            curr.append(c1 == "c" ? outerSpaces / 2 : c1 == "rr" ? outerSpaces : 0, ' ');
            if (c2 == "f" || c2 == "g" && curr.find("fnord") < curr.size()) lines.push_back(curr);
            else if (c2 == "r") lines.insert(lines.begin(), curr);
            line.clear(), len = 0;
        }
        if (std::cin) line.push_back(s = s.substr(0, N)), len += s.size();
    }
    for (const auto& line : lines) std::cout << line << '\n';
    return 0;
}