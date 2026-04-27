#include <algorithm>
#include <cctype>
#include <iostream>
#include <string_view>

bool first(char c)
{
    unsigned char x = c;
    return std::isalpha(x) || x == '_';
}

bool other(char c)
{
    unsigned char x = c;
    return std::isalnum(x) || x == '_';
}

bool isIdentifier(std::string_view s)
{
    return !s.empty() && first(s[0]) && std::all_of(s.begin() + 1, s.end(), other);
}

int main()
{
    std::cout << std::boolalpha;

    std::cout << isIdentifier("a") << std::endl;
    std::cout << isIdentifier("isIdentifier") << std::endl;
    std::cout << isIdentifier("_name123") << std::endl;
    std::cout << isIdentifier("hello world") << std::endl;
    std::cout << isIdentifier("123name") << std::endl;
    std::cout << isIdentifier("my-name") << std::endl;
    std::cout << isIdentifier("int") << std::endl;

    return 0;
}