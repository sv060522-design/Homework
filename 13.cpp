#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::string>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

std::vector<std::string> prefixes(const std::string& str) {
    std::vector<std::string> result;
    for (size_t i = 1; i <= str.size(); ++i) {
        result.push_back(str.substr(0, i));
    }
    return result;
}

int main() {
    std::vector<std::string> v = prefixes("Mouse");
    print(v);
    return 0;
}