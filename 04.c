#include <stdio.h>
int is_little_endian() {
    int x = 1;
    return *(char*)&x;
}
int main() {
    if(is_little_endian()) {
        printf("Little Endian system\n");
    } else {
        printf("Big Endian system\n");
    }
    return 0;
}