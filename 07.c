#include <stdio.h>
void encrypt(char* str, int k) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            int index = str[i] - 'A';
            index = (index + k) % 26;
            if (index < 0) index += 26;
            str[i] = 'A' + index;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            int index = str[i] - 'a';
            index = (index + k) % 26;
            if (index < 0) index += 26;
            str[i] = 'a' + index;
        }
    }
}
int main() {
    int k;
    char str[1000];
    scanf("%d", &k);
    getchar();
    fgets(str, sizeof(str), stdin);
    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') len++;
    str[len] = '\0';
    encrypt(str, k);
    printf("%s\n", str);
    return 0;
}