#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: Wrong number of arguments!\n");
        printf("Usage: %s <input_file> <output_file> <lines>\n", argv[0]);
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error: File %s does not exist!\n", argv[1]);
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Error: Cannot create output file!\n");
        fclose(input);
        return 1;
    }
    char *lines_arg = argv[3];
    int start_line, end_line;
    char *colon = strchr(lines_arg, ':');
    if (colon == NULL) {
        char *endptr;
        start_line = strtol(lines_arg, &endptr, 10);
        if (*endptr != '\0' || start_line <= 0) {
            printf("Error: Wrong lines format!\n");
            fclose(input);
            fclose(output);
            return 1;
        }
        end_line = start_line + 1;
    } else {
        *colon = '\0';
        char *endptr1, *endptr2;
        start_line = strtol(lines_arg, &endptr1, 10);
        end_line = strtol(colon + 1, &endptr2, 10);
        if (*endptr1 != '\0' || *endptr2 != '\0' || start_line <= 0 || end_line <= 0 || start_line >= end_line) {
            printf("Error: Wrong lines format!\n");
            fclose(input);
            fclose(output);
            return 1;
        }
    }
    char buffer[1000];
    int current_line = 1;
    int lines_written = 0;
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        if (current_line >= start_line && current_line < end_line) {
            fputs(buffer, output);
            lines_written++;
        }
        current_line++;
        if (current_line > end_line) break;
    }
    if (lines_written == 0) {
        printf("Warning: No lines were extracted. Check if line numbers are within file bounds.\n");
    }
    fclose(input);
    fclose(output);
    return 0;
}