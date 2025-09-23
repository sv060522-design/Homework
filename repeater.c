#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: Wrong number of arguments!\n");
        printf("Usage: %s <number> <operator> <number>\n", argv[0]);
        return 1;
    }
    char *word = argv[1];
    int count = atoi(argv[2]);
    for (int i = 0; i < count; i++) {
        printf("%s", word);
        if (i < count - 1) printf(" ");
    }
    printf("\n");
    return 0;
}