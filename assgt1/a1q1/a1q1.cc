#include <iostream>
#include <string>
int main() {
    int N;
    std::string line;
    std::cin >> N;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    getline(std::cin, line);
    while (getline(std::cin, line)) std::cout << line.substr(0, N) << '\n';
    return 0;
}