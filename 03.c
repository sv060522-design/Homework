#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* concat(const char* a, const char* b) {
    char* result = malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return result;
}
int main() {
    char* s = concat("C", "++");
    printf("%s\n", s);
    free(s);
    return 0;
}
// Про вывод ничего не было сказано, поэтому решил вывести C++ чтобы проверить что работает.