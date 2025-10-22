#include <stdio.h>
#include <string.h>
int main() {
    int a[4] = {1819043144, 1461726319, 1684828783, 2593};
    printf("(a)\n");
    char* str_a = (char*)a;
    for(int i=0; i<16; i++) {
        if(str_a[i] != 0) printf("%c", str_a[i]);
    }
    printf("(b)\n");
    union {
        int nums[4];
        char chars[16];
    } u;
    for(int i=0; i<4; i++) {
        u.nums[i] = a[i];
    }
    for(int i=0; i<16; i++) {
        if(u.chars[i] != 0) printf("%c", u.chars[i]);
    }
    printf("(c)\n");
    char str_c[16];
    memcpy(str_c, a, 16);
    for(int i=0; i<16; i++) {
        if(str_c[i] != 0) printf("%c", str_c[i]);
    }
    return 0;
}