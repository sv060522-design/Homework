#include <stdio.h>
#include <stdlib.h>
void print(int* a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");
}
int less(int a, int b) {
    return a - b;
}
int greater(int a, int b) {
    return b - a;
}
int last_digit_less(int a, int b) {
    return (a % 10) - (b % 10);
}

void sort(int* a, size_t n, int (*comparator)(int, int))
{
    for (size_t j = 0; j < n; ++j)
    {
        size_t min_index = j;
        for (size_t i = j + 1; i < n; ++i)
        {
            if (comparator(a[i], a[min_index]) < 0)
                min_index = i;
        }
        int temp = a[j];
        a[j] = a[min_index];
        a[min_index] = temp;
    }
}
int main()
{
    int a[] = {32, 63, 29, 54, 81};
    sort(a, 5, less);
    print(a, 5);
    sort(a, 5, greater);
    print(a, 5);
    sort(a, 5, last_digit_less);
    print(a, 5);
    return 0;
}