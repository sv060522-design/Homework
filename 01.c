#include <stdio.h>
#include <string.h>
int main() {
    unsigned char a[16] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0};
    for(int i=0;i<16;i++) printf("%02X ",a[i]);
    printf("\n");
    for(int i=0;i<16;i++) printf("%d ",a[i]);
    printf("\n");
    for(int i=0;i<16;i++) {
        printf("Index: %02d Hex: 0x%02X ASCII: ",i,a[i]);
        if(a[i]>=32&&a[i]<=126) printf("%c",a[i]);
        else printf(".");
        printf("\n");
    }
    a[5]=0xE5;
    memmove(a+3,a,7);
    memcpy(a,a+11,5);
    memset(a+5,0,6);
    return 0;
}