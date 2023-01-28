#include <iostream>
#include <string>
int main() {
    int N, curr = -1;
    std::cin >> N;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    for (std::string s; std::cin >> s;) {
        s = s.substr(0, N);
        if (~curr) curr + s.size() + 1 > N ? curr = -1, std::cout << '\n' : std::cout << ' ';
        std::cout << s;
        curr += s.size() + 1;
    }
    std::cout << '\n';
    return 0;
}