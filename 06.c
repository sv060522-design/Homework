#include <stdio.h>
int is_palindrom(char s[]) {
    int len = 0;
    while (s[len] != '\0') len++;
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - 1 - i]) return 0;
    }
    return 1;
}
int main() {
    char s[100];
    scanf("%s", s);
    if (is_palindrom(s)) printf("Yes\n");
    else printf("No\n");
    return 0;
}