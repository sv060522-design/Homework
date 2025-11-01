#include <iostream>

void cube(int& x) {
    x = x * x * x;
}

int main() {
    int a = 5;
    cube(a);
    std::cout << a << std::endl;
    return 0;
}