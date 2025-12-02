#include <iostream>
#include <cstring>

template<typename T>
void swapEndianness(T& value)
{
    char* bytes = reinterpret_cast<char*>(&value);
    for (std::size_t i = 0; i < sizeof(T) / 2; ++i) {
        std::swap(bytes[i], bytes[sizeof(T) - 1 - i]);
    }
}

int main()
{
    std::cout << std::hex;

    int a = 0x1a2b3c4d;
    std::cout << a << std::endl;
    swapEndianness(a);
    std::cout << a << std::endl;
    swapEndianness(a);
    std::cout << a << std::endl;

    short b = 0x1a2b;
    std::cout << b << std::endl;
    swapEndianness(b);
    std::cout << b << std::endl;
}