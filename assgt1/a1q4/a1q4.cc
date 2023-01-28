#include <iostream>
#include <string>
#include <vector>
int main() {
    int N, len = 0;
    std::cin >> N;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    std::vector<std::string> line;
    for (std::string s; std::cin;) {
        std::cin >> s;
        if (len && (!std::cin || len + s.size() + line.size() > N)) {
            int delims = line.size() > 1 ? line.size() - 1 : 1, spaces = N - len, extra = spaces % delims;
            for (int i = 0; i < line.size(); i++) std::cout << line[i].append(spaces / delims * (i < delims) + (i < extra), ' ');
            std::cout << '\n';
            line.clear(), len = 0;
        }
        if (std::cin) line.push_back(s = s.substr(0, N)), len += s.size();
    }
    return 0;
}