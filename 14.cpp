#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::size_t>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

std::vector<std::size_t> substringIndexes(const std::string& str, const std::string& substr) {
    std::vector<std::size_t> result;
    std::size_t pos = 0;
    
    while ((pos = str.find(substr, pos)) != std::string::npos) {
        result.push_back(pos);
        pos += 1;
    }
    
    return result;
}

int main() {
    std::vector<std::size_t> v1 = substringIndexes("cat and dog and cat", "cat");
    print(v1);

    std::vector<std::size_t> v2 = substringIndexes("look, cats were here", "cat");
    print(v2);

    std::vector<std::size_t> v3 = substringIndexes("catcatcatcatcatcat", "cat");
    print(v3);

    std::vector<std::size_t> v4 = substringIndexes("dog mouse elephant", "cat");
    print(v4);
    
    return 0;
}