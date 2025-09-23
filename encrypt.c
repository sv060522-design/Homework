#include <stdio.h>
#include <stdlib.h>
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
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_file> <key>\n", argv[0]);
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    int k = atoi(argv[3]);
    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return 1;
    }
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        encrypt(buffer, k);
        fputs(buffer, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}