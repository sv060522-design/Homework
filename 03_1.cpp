#include "number.hpp"
#include <iostream>

int main() {
    Number a = 12345678;
    Number b = "0";
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    Number c = "999";
    Number d = "1";
    Number e = c + d;
    std::cout << "999 + 1 = " << e << std::endl;

    Number f = "123";
    Number g = "456";
    Number h = f * g;
    std::cout << "123 * 456 = " << h << std::endl;

    std::cout << "Is 12345678 even? " << a.isEven() << std::endl;
    std::cout << "Is 999 even? " << Number(999).isEven() << std::endl;

    Number fib0 = 0;
    Number fib1 = 1;
    for (int i = 2; i <= 1000; ++i) {
        Number temp = fib1;
        fib1 += fib0;
        fib0 = temp;
    }
    std::cout << "F(1000) = " << fib1 << std::endl;

    Number fact = 1;
    for (int i = 2; i <= 1000; ++i) {
        fact *= Number(i);
    }
    std::cout << "1000! = " << fact << std::endl;

    return 0;
}