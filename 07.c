#include<stdio.h>
int count_even(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}
int main() {
    // int arr[] = {1, 2, 3, 4, 5};
    // int arr[] = {10, 20, 30, 40};
    int arr[] = {10, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int res = count_even(arr, size);
    printf("%d", res);


}