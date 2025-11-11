#include "number.hpp"
#include <algorithm>
#include <cstring>

void Number::resize(std::size_t new_capacity) {
    char* new_data = new char[new_capacity]();
    std::size_t min_size = std::min(size, new_capacity);
    for (std::size_t i = 0; i < min_size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    size = min_size;
}

void Number::removeLeadingZeros() {
    while (size > 1 && data[size - 1] == 0) {
        --size;
    }
}

Number::Number() : data(new char[1]()), size(1), capacity(1) {}

Number::Number(int a) {
    if (a < 0) a = 0;

    int temp = a;
    capacity = 0;
    while (temp != 0) {
        temp /= base;
        capacity += 1;
    }

    if (capacity == 0) capacity = 1;

    data = new char[capacity]();
    for (int i = 0; i < capacity; ++i) {
        data[i] = a % base;
        a /= base;
    }
    size = capacity;
}

Number::Number(const std::string& str) {
    if (str.empty()) {
        data = new char[1]();
        size = 1;
        capacity = 1;
        return;
    }

    std::size_t start = 0;
    while (start < str.length() && str[start] == '0') {
        start++;
    }

    if (start == str.length()) {
        data = new char[1]();
        size = 1;
        capacity = 1;
        return;
    }

    std::string clean_str = str.substr(start);
    std::size_t len = clean_str.length();
    capacity = (len + 1) / 2;
    data = new char[capacity]();
    size = capacity;

    for (std::size_t i = 0; i < capacity; ++i) {
        int digit_index = len - 1 - i * 2;
        int digit1 = 0, digit2 = 0;

        if (digit_index >= 0)
            digit1 = clean_str[digit_index] - '0';
        if (digit_index - 1 >= 0)
            digit2 = clean_str[digit_index - 1] - '0';

        data[i] = digit2 * 10 + digit1;
    }
    removeLeadingZeros();
}

Number::Number(const char* str) : Number(std::string(str)) {}

Number::Number(const Number& other)
    : data(new char[other.capacity]), size(other.size), capacity(other.capacity) {
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Number::Number(Number&& other) noexcept
    : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

Number::~Number() {
    delete[] data;
}

Number& Number::operator=(const Number& other) {
    if (this == &other) return *this;

    delete[] data;
    capacity = other.capacity;
    size = other.size;
    data = new char[capacity];
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

Number& Number::operator=(Number&& other) noexcept {
    if (this == &other) return *this;

    delete[] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

Number Number::operator+(const Number& other) const {
    Number result = *this;
    result += other;
    return result;
}

Number& Number::operator+=(const Number& other) {
    std::size_t max_size = std::max(size, other.size);
    if (capacity < max_size + 1) {
        resize(max_size + 1);
    }

    int carry = 0;
    for (std::size_t i = 0; i < max_size || carry; ++i) {
        if (i >= size) {
            data[i] = 0;
            size = i + 1;
        }

        int current = data[i];
        int other_val = (i < other.size) ? other.data[i] : 0;
        int sum = current + other_val + carry;

        data[i] = sum % base;
        carry = sum / base;
    }

    removeLeadingZeros();
    return *this;
}

Number Number::operator*(const Number& other) const {
    if (*this == Number(0) || other == Number(0)) {
        return Number(0);
    }

    Number result;
    std::size_t new_size = size + other.size + 1;
    result.resize(new_size);
    result.size = result.capacity;

    for (std::size_t i = 0; i < size; ++i) {
        int carry = 0;
        for (std::size_t j = 0; j < other.size || carry; ++j) {
            if (i + j >= result.size) {
                result.resize(i + j + 1);
                result.size = result.capacity;
            }

            long long product = (long long)data[i] *
                              ((j < other.size) ? other.data[j] : 0) +
                              result.data[i + j] + carry;
            result.data[i + j] = product % base;
            carry = product / base;
        }
    }

    result.removeLeadingZeros();
    return result;
}

Number& Number::operator*=(const Number& other) {
    *this = *this * other;
    return *this;
}

bool Number::operator==(const Number& other) const {
    if (size != other.size) return false;
    for (std::size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool Number::operator!=(const Number& other) const {
    return !(*this == other);
}

bool Number::isEven() const {
    return (data[0] % 2) == 0;
}

std::ostream& operator<<(std::ostream& stream, const Number& num) {
    if (num.size == 0) {
        stream << "0";
        return stream;
    }

    stream << static_cast<int>(num.data[num.size - 1]);
    for (std::size_t i = 0; i < num.size - 1; ++i) {
        stream << std::setfill('0') << std::setw(2) 
               << static_cast<int>(num.data[num.size - 2 - i]);
    }
    return stream;
}