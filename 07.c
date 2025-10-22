#include <stdio.h>
int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "rb");
    if(!file) {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    printf("File size: %ld bytes\n", size);
    return 0;
}