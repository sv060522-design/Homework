#include <stdio.h>
#include <stdlib.h>
int main() {
    size_t* n = malloc(sizeof(size_t));
    *n = 123;
    printf("%zu\n", *n);
    free(n);
    return 0;
}
