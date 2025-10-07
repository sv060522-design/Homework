#include <stdio.h>
int adder(int x) {
    static int sum = 0;
    sum += x;
    return sum;
}
int main()
{
    printf("%i\n", adder(10));
    printf("%i\n", adder(15));
    printf("%i\n", adder(70));
    return 0;
}
