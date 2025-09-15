#include <stdio.h>
int trib(int n) {
    if (n == 0 || n == 1) return 0;
    if (n == 2) return 1;

    int a = 0, b = 0, c = 1;
    for (int i = 3; i <= n; i++) {
        int next = a + b + c;
        a = b;
        b = c;
        c = next;
    }
    return c;
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", trib(n));
    return 0;
}