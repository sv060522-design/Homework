#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 10;
    int b = 20;
    std::cout << a << " " << b << std::endl;

    swap(a, b);
    std::cout << a << " " << b << std::endl;
    return 0;
}