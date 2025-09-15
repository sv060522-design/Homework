#include <stdio.h>
void reverse(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
int main() {
    // int arr[] = {10, 20, 30, 40, 50};
    int arr[] = {60, 20, 80, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    reverse(arr, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}