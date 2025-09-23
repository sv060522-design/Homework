#include <stdio.h>
void safe_strcpy(char dest[], size_t size, const char src[]) {
    size_t i;
    for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}
int main() {
    char a[10] = "Mouse";
    char b[50] = "LargeElephant";
    safe_strcpy(a, 10, b);
    printf("%s\n", a);
    return 0;
}
