#include <stdio.h>
int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int sum_of_digits_rec(int n) {
    if (n < 10) {
        return n;
    }
    return n % 10 + sum_of_digits_rec(n / 10);
}

int main() {
    int num;
    scanf("%d", &num);
    printf("%d\n", sum_of_digits(num));
    printf("%d\n", sum_of_digits_rec(num));

    return 0;
}