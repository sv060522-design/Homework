#include <stdio.h>
unsigned long long int arrang(int n, int k) {
    if (k > n) return 0;
    if (k == 0) return 1;
    unsigned long long int res = 1;
    for (int i = 0; i < k; i++) {
        res *= (n - i);
    }
    return res;
}
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%llu\n", arrang(n, k));
    return 0;
}