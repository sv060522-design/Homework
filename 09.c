#include <stdio.h>

int main() {
    int a[1000];
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
            a[j] = a[i];
            j++;
        }
    }
    n = j;
    
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
