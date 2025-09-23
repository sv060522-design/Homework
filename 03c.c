#include <stdio.h>
#include <ctype.h>
int main() {
    char c;
    scanf("%c", &c);
    if (isalpha(c)) {
        printf("Letter\n");
    } else if (isdigit(c)) {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
    return 0;
}