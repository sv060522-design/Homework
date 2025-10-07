#include <stdio.h>
#include <math.h>
size_t count_if(int* arr, size_t n, int (*predicate)(int)) {
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        if (predicate(arr[i])) {
            count++;
        }
    }
    return count;
}
int is_negative(int x) {
    return x < 0;
}
int is_even(int x) {
    return x % 2 == 0;
}
int is_square(int x) {
    if (x < 0) return 0;
    int root = (int)sqrt(x);
    return root * root == x;
}
int main()
{
    int a[] = {89, 81, 28, 52, 44, 16, -64, 49, 52, -79};
    printf("%zu\n", count_if(a, 10, is_negative));
    printf("%zu\n", count_if(a, 10, is_even));
    printf("%zu\n", count_if(a, 10, is_square));
    return 0;
}