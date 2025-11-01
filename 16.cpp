#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::string>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << std::endl;
}  // Она здесь не используется, поэтому можно и удалить, но так как была в коде в задавнии, то пусть и здесь останется

std::vector<std::string> split(const std::string& data, char delimiter) {
    std::vector<std::string> parts;
    std::size_t start = 0;
    std::size_t end = data.find(delimiter);

    while (end != std::string::npos) {
        parts.push_back(data.substr(start, end - start));
        start = end + 1;
        end = data.find(delimiter, start);
    }

    parts.push_back(data.substr(start));
    return parts;
}

int main() {
    std::string data = "apple,banana,cherry,durian";
    char delimiter = ',';

    std::vector<std::string> parts = split(data, delimiter);
    for (std::size_t i = 0; i < parts.size(); ++i)
        std::cout << parts.at(i) << std::endl;

    return 0;
}