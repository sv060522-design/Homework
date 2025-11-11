#include "integer.hpp"
#include <algorithm>

void Integer::removeLeadingZeros() {
    while (data.size() > 1 && data.back() == 0) {
        data.pop_back();
    }
}

Integer::Integer() : data(1, 0) {}

Integer::Integer(int a) {
    if (a < 0) a = 0;
    
    if (a == 0) {
        data.push_back(0);
        return;
    }
    
    while (a != 0) {
        data.push_back(a % base);
        a /= base;
    }
}

Integer::Integer(const std::string& str) {
    if (str.empty()) {
        data.push_back(0);
        return;
    }
    
    std::size_t start = 0;
    while (start < str.length() && str[start] == '0') {
        start++;
    }
    
    if (start == str.length()) {
        data.push_back(0);
        return;
    }
    
    std::string clean_str = str.substr(start);
    std::size_t len = clean_str.length();
    
    for (std::size_t i = 0; i < (len + 1) / 2; ++i) {
        int digit_index = len - 1 - i * 2;
        int digit1 = 0, digit2 = 0;
        
        if (digit_index >= 0)
            digit1 = clean_str[digit_index] - '0';
        if (digit_index - 1 >= 0)
            digit2 = clean_str[digit_index - 1] - '0';
            
        data.push_back(digit2 * 10 + digit1);
    }
    removeLeadingZeros();
}

Integer::Integer(const char* str) : Integer(std::string(str)) {}

Integer Integer::operator+(const Integer& other) const {
    Integer result = *this;
    result += other;
    return result;
}

Integer& Integer::operator+=(const Integer& other) {
    std::size_t max_size = std::max(data.size(), other.data.size());
    data.resize(max_size, 0);
    
    int carry = 0;
    for (std::size_t i = 0; i < max_size || carry; ++i) {
        if (i == data.size()) {
            data.push_back(0);
        }
        
        int current = data[i];
        int other_val = (i < other.data.size()) ? other.data[i] : 0;
        int sum = current + other_val + carry;
        
        data[i] = sum % base;
        carry = sum / base;
    }
    
    removeLeadingZeros();
    return *this;
}

Integer Integer::operator*(const Integer& other) const {
    if (*this == Integer(0) || other == Integer(0)) {
        return Integer(0);
    }
    
    Integer result;
    result.data.resize(data.size() + other.data.size() + 1, 0);
    
    for (std::size_t i = 0; i < data.size(); ++i) {
        int carry = 0;
        for (std::size_t j = 0; j < other.data.size() || carry; ++j) {
            long long product = (long long)data[i] * 
                              ((j < other.data.size()) ? other.data[j] : 0) + 
                              result.data[i + j] + carry;
            result.data[i + j] = product % base;
            carry = product / base;
        }
    }
    
    result.removeLeadingZeros();
    return result;
}

Integer& Integer::operator*=(const Integer& other) {
    *this = *this * other;
    return *this;
}

bool Integer::operator==(const Integer& other) const {
    return data == other.data;
}

bool Integer::operator!=(const Integer& other) const {
    return !(*this == other);
}

bool Integer::isEven() const {
    return (data[0] % 2) == 0;
}

std::ostream& operator<<(std::ostream& stream, const Integer& num) {
    if (num.data.empty()) {
        stream << "0";
        return stream;
    }
    
    stream << static_cast<int>(num.data.back());
    for (std::size_t i = 0; i < num.data.size() - 1; ++i) {
        stream << std::setfill('0') << std::setw(2) 
               << static_cast<int>(num.data[num.data.size() - 2 - i]);
    }
    return stream;
}