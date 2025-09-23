#include <stdio.h>
int main() {
    char s1[100], s2[100];
    scanf("%s%s", s1, s2);
    int len1 = 0, len2 = 0;
    while (s1[len1] != '\0') len1++;
    while (s2[len2] != '\0') len2++;
    int i = 0;
    while (i < len1 || i < len2) {
        if (i < len1) printf("%c", s1[i]);
        if (i < len2) printf("%c", s2[i]);
        i++;
    }
    return 0;
}