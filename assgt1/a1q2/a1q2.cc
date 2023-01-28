#include <iostream>
#include <string>
#include <vector>
int main() {
    int N;
    char command;
    std::cin >> N >> command;
    if (N < 1) return std::cerr << "Error, line length must be positive.\n", 1;
    if (command != 'f' && command != 'r' && command != 'g') return std::cerr << "Error, command is illegal.\n", 1;
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> lines;
    while (getline(std::cin, line)) {
        std::string part = line.substr(0, N);
        if (command == 'f' || command == 'g' && line.find("fnord") < line.size()) lines.push_back(part);
        else if (command == 'r') lines.insert(lines.begin(), part);
    }
    for (const auto& line : lines) std::cout << line << '\n';
    return 0;
}