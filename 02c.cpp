#include <iostream>
#include <string>

template<typename T>
T triple(const T& x)
{
    return 3 * x;
}

std::string triple(const std::string& x)
{
    std::string result;
    for (int i = 0; i < 3; ++i) {
        result += x;
    }
    return result;
}

int main()
{
    int a = 10;
    std::cout << triple(a) << std::endl;

    std::string b = "Cat";
    std::cout << triple(b) << std::endl;
}