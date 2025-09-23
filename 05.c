#include <stdio.h>
int main() {
    char c;
    int sum = 0;
    while (scanf("%c", &c) == 1 && c != '\n') {
        if (c >= '0' && c <= '9') {
            sum += c - '0';
        }
    }
    printf("%d\n", sum);
    return 0;
}