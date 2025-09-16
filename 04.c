#include <stdio.h>
double pi(int n) {
    double sum = 0.0;
    int z = 1;
    for (int i = 1; i <= n; i++) {
        double res = z * 1.0 / (2 * i - 1);
        sum += res;
        z *= -1;
    }
    return 4 * sum;
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%.10f\n", pi(n));
    return 0;
}