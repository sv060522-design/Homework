#include <stdio.h>

int digit_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    int sums[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sums[i] = digit_sum(arr[i]);
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (sums[j] > sums[j+1]) {
                int temp_sum = sums[j];
                sums[j] = sums[j+1];
                sums[j+1] = temp_sum;

                int temp_num = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp_num;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}