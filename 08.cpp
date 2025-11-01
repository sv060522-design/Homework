#include <iostream>
#include <string>
#include <cctype>

void countLetters(const std::string& str, int& numLetters, int& numDigits) {
    numLetters = 0;
    numDigits = 0;
    
    for (char c : str) {
        if (std::isalpha(c)) {
            numLetters++;
        } else if (std::isdigit(c)) {
            numDigits++;
        }
    }
}

int main() {
    std::string test = "Hello123World456";
    int letters, digits;
    
    countLetters(test, letters, digits);
    std::cout << "Letters: " << letters << ", Digits: " << digits << std::endl;
    
    return 0;
}