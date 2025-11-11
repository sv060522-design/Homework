#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Number 
{
private:
    static const int base = 100;
    char* data;
    std::size_t size;
    std::size_t capacity;

    void resize(std::size_t new_capacity);
    void removeLeadingZeros();

public:
    Number();
    Number(int a);
    Number(const std::string& str);
    Number(const char* str);
    Number(const Number& other);
    Number(Number&& other) noexcept;
    ~Number();

    Number& operator=(const Number& other);
    Number& operator=(Number&& other) noexcept;

    Number operator+(const Number& other) const;
    Number& operator+=(const Number& other);

    Number operator*(const Number& other) const;
    Number& operator*=(const Number& other);

    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;
    
    bool isEven() const;
    
    friend std::ostream& operator<<(std::ostream& stream, const Number& num);
};