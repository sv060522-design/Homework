#include <algorithm>
#include <cctype>
#include <iostream>
#include <string_view>

bool isUpper(std::string_view s)
{
    return std::all_of(s.begin(), s.end(), [](unsigned char c)
    {
        return !std::isalpha(c) || std::isupper(c);
    });
}

int main()
{
    std::cout << std::boolalpha;

    std::cout << isUpper("Cats and Dogs!") << std::endl;
    std::cout << isUpper("CATS AND DOGS!") << std::endl;
    std::cout << isUpper("ABc123!#?") << std::endl;
    std::cout << isUpper("ABC123!#?") << std::endl;

    return 0;
}