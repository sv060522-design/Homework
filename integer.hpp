#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Integer 
{
private:
    static const int base = 100;
    std::vector<char> data;

    void removeLeadingZeros();

public:
    Integer();
    Integer(int a);
    Integer(const std::string& str);
    Integer(const char* str);
    Integer(const Integer& other) = default;
    Integer(Integer&& other) = default;
    
    Integer& operator=(const Integer& other) = default;
    Integer& operator=(Integer&& other) = default;
    
    Integer operator+(const Integer& other) const;
    Integer& operator+=(const Integer& other);
    
    Integer operator*(const Integer& other) const;
    Integer& operator*=(const Integer& other);
    
    bool operator==(const Integer& other) const;
    bool operator!=(const Integer& other) const;
    
    bool isEven() const;
    
    friend std::ostream& operator<<(std::ostream& stream, const Integer& num);
};