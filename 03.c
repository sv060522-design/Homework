#include <stdio.h>
void print_even(int a, int b) {
    for (int i = a; i <= b; i++) {
        if (i % 2 == 0) {
            printf("%d ", i);
        }
    }
}
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    print_even(a, b);
}
