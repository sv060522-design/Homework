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
    fseek(file, -3, SEEK_END);
    unsigned char bytes[3];
    int count = fread(bytes, 1, 3, file);
    for(int i = 0; i < count; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
    fclose(file);
    return 0;
}