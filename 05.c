#include <stdio.h>
void print_binary(int n) {
    if (n == 0) {
        printf("0");
        return;
    }
    if (n > 1) {
        print_binary(n / 2);
    }
    printf("%d", n % 2);
}
int main() {
    int num;
    scanf("%d", &num);
    print_binary(num);
    printf("\n");
    return 0;
}