#include <stdio.h>
void mult2_a(int* p, size_t n)
{
    for(size_t i=0; i<n; i++)
    {
        *(p + i) *= 2;
    }
}
void mult2_b(int* p, size_t n)
{
    for(size_t i=0; i<n; i++)
    {
        p[i] *= 2;
    }
}
int main()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    size_t n = 5;
    mult2_a(arr1, n);
    for(size_t i=0; i<n; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    mult2_b(arr2, n);
    for(size_t i=0; i<n; i++)
        printf("%d ", arr2[i]);
    printf("\n");
    return 0;
}