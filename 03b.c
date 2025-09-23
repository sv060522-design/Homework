#include <stdio.h>
int main() {
    char c;
    scanf("%c", &c);
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    int is_letter = 0, is_digit = 0;
    for (int i = 0; letters[i] != '\0'; i++) {
        if (c == letters[i]) {
            is_letter = 1;
            break;
        }
    }
    for (int i = 0; digits[i] != '\0'; i++) {
        if (c == digits[i]) {
            is_digit = 1;
            break;
        }
    }
    if (is_letter) {
        printf("Letter\n");
    } else if (is_digit) {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
    return 0;
}
