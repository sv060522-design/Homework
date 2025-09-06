#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0 || j > 0) {
                printf(" ");
            }
            printf("%d", arr[j]);
        }
    }

    return 0;
}
