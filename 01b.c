#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char* s = malloc(9);
    strcpy(s, "Elephant");
    printf("%s\n", s);
    free(s);
    return 0;
}
