#include <stdio.h>
long long int fact(int n) {
    long long int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}
int main() {
    int k;
    scanf("%i", &k);
    printf("%lli\n", fact(k));
}