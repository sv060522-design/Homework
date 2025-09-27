#include <stdio.h>
int exchange(int* pa, int b)
{
    int old = *pa;
    *pa = b;
    return old;
}
int main()
{
    int a = 10;
    printf("%i\n", exchange(&a, 20));
    printf("%i\n", a);
    return 0;
}