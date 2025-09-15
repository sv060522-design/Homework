#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("%d -> %3d -> %3d\n", i, i*i, i*i*i);
    }

    return 0;
}
