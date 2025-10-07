#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char** p = malloc(sizeof(char*));
    *p = malloc(14);
    strcpy(*p, "Cats and Dogs");
    printf("%s\n", *p);
    free(*p);
    free(p);
    return 0;
}