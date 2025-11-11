#include <iostream>
#include "vector2f.hpp"
using std::cout, std::endl;

int main()
{
    Vector2f a = {1.0, 2.0};
    Vector2f b = {4.0, -1.0};
    cout << "a = " << a << endl << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "-a = " << -a << endl;
    cout << "Scalar product of a and b = " << a * b << endl;
    a /= 5;
    cout << "a after a /= 5; " << a << endl;
    a += b;
    cout << "a after a += b; " << a << endl;
}