#include "integer.hpp"
#include <iostream>

int main() {
    Integer a = 12345678;
    Integer b = "0";
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    Integer c = "999";
    Integer d = "1";
    Integer e = c + d;
    std::cout << "999 + 1 = " << e << std::endl;

    Integer f = "123";
    Integer g = "456";
    Integer h = f * g;
    std::cout << "123 * 456 = " << h << std::endl;

    std::cout << "Is 12345678 even? " << a.isEven() << std::endl;
    std::cout << "Is 999 even? " << Integer(999).isEven() << std::endl;

    Integer fib0 = 0;
    Integer fib1 = 1;
    for (int i = 2; i <= 100; ++i) {
        Integer temp = fib1;
        fib1 += fib0;
        fib0 = temp;
    }
    std::cout << "F(100) = " << fib1 << std::endl;

    Integer fact = 1;
    for (int i = 2; i <= 1000; ++i) {
        fact *= Integer(i);
    }
    std::cout << "1000! = " << fact << std::endl;
    
    return 0;
}