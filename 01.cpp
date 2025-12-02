#include <iostream>

template<typename T>
T cube(T value) {
    return value * value * value;
}

int main() {
    auto a = cube(5);
    std::cout << a << " " << sizeof(a) << std::endl;

    auto b = cube(5.0);
    std::cout << b << " " << sizeof(b) << std::endl;

    char x = 5;
    auto c = cube(x);
    std::cout << static_cast<int>(c) << " " << sizeof(c) << std::endl;

    return 0;
} // Вообще во второй в задании написано, что должно выводиться 125.0 8, но выводится просто 125 8, так как по умолчанию
// числа формата double без десятичной части выводятся без нуля после точки. Для вывода именно 125.0, а не 125 нужно
// использовать std::fixed. Поэтому что есть, оставлю так.
