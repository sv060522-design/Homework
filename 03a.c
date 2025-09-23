#include <stdio.h>
int main() {
    char c;
    scanf("%c", &c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        printf("Letter\n");
    } else if (c >= '0' && c <= '9') {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
    return 0;
}