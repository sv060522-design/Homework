#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int sum = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            sum += sign * i * j;
        }
    }

    printf("%d", sum);

    return 0;
}
