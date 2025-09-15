#include <stdio.h>
void bob(int n);
void alice(int n) {
    n = n * 3 + 1;
    printf("%-8s%d\n", "Alice:", n);
    bob(n);
}
void bob(int n) {
    while (n % 2 == 0) {
        n = n / 2;
        printf("%-8s%d\n", "Bob:", n);
        if (n == 1) return;
    }
    if (n != 1) alice(n);
}
int main() {
    int n;
    scanf("%d", &n);
    if (n % 2 == 1) alice(n);
    else bob(n);
    return 0;
}