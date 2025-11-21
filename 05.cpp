#include <iostream>
#include <string>
#include <stdexcept>

int sumFromString(const std::string& str) {
    if (str.empty() || str[0] != '[' || str[str.size()-1] != ']') {
        throw std::invalid_argument("Invalid format");
    }

    int sum = 0;
    std::string num;
    bool inNumber = false;

    for (size_t i = 1; i < str.size() - 1; ++i) {
        char c = str[i];

        if (c >= '0' && c <= '9') {
            num += c;
            inNumber = true;
        } else if (c == ',') {
            if (inNumber) {
                sum += std::stoi(num);
                num.clear();
                inNumber = false;
            }
        } else if (c != ' ') {
            throw std::invalid_argument("Invalid character");
        }
    }

    if (inNumber) {
        sum += std::stoi(num);
    }

    return sum;
}

int main() {
    try {
        std::cout << sumFromString("[10, 20, 30, 40, 50]") << std::endl;
        std::cout << sumFromString("[4, 8, 15, 16, 23, 42]") << std::endl;
        std::cout << sumFromString("[20]") << std::endl;
        std::cout << sumFromString("[]") << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}