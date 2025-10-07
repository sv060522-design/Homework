#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** get_test_strings() {
    char** arr = malloc(4 * sizeof(char*));
    arr[0] = malloc(4);
    strcpy(arr[0], "Cat");
    arr[1] = malloc(6);
    strcpy(arr[1], "Mouse");
    arr[2] = malloc(9);
    strcpy(arr[2], "Elephant");
    arr[3] = NULL;
    return arr;
}
void print_strings(const char** string_array) {
    for(int i = 0; string_array[i] != NULL; i++) {
        printf("%s\n", string_array[i]);
    }
}
size_t* get_sizes(const char** string_array) {
    int count = 0;
    while(string_array[count] != NULL) count++;
    size_t* sizes = malloc(count * sizeof(size_t));
    for(int i = 0; i < count; i++) {
        sizes[i] = strlen(string_array[i]);
    }
    return sizes;
}
char** load_lines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(!file) return NULL;
    int line_count = 0;
    int ch;
    while((ch = fgetc(file)) != EOF) {
        if(ch == '\n') line_count++;
    }
    line_count++;
    char** lines = malloc((line_count + 1) * sizeof(char*));
    int* line_lengths = malloc(line_count * sizeof(int));
    fseek(file, 0, SEEK_SET);
    for(int i = 0; i < line_count; i++) {
        int length = 0;
        while((ch = fgetc(file)) != EOF && ch != '\n') {
            length++;
        }
        line_lengths[i] = length;
        if(ch == EOF) break;
    }
    fseek(file, 0, SEEK_SET);
    for(int i = 0; i < line_count; i++) {
        lines[i] = malloc((line_lengths[i] + 1) * sizeof(char));
        for(int j = 0; j < line_lengths[i]; j++) {
            ch = fgetc(file);
            lines[i][j] = (char)ch;
        }
        lines[i][line_lengths[i]] = '\0';
        ch = fgetc(file);
        if(ch != '\n' && ch != EOF) {
            ungetc(ch, file);
        }
        if(ch == EOF && i < line_count - 1) {
            line_count = i + 1;
            break;
        }
    }
    lines[line_count] = NULL;
    free(line_lengths);
    fclose(file);
    return lines;
}
void destroy_strings(char*** p_string_array) {
    if(!p_string_array || !*p_string_array) return;
    for(int i = 0; (*p_string_array)[i] != NULL; i++) {
        free((*p_string_array)[i]);
    }
    free(*p_string_array);
    *p_string_array = NULL;
}
void sort_strings(char** words) {
    int count = 0;
    while(words[count] != NULL) count++;
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(strcmp(words[j], words[j + 1]) > 0) {
                char* temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}
int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Error: Invalid number of arguments\n");
        return 1;
    }
    char** lines = load_lines(argv[1]);
    if(!lines) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    sort_strings(lines);
    FILE* output = fopen(argv[2], "w");
    if(!output) {
        printf("Error: Cannot create file %s\n", argv[2]);
        destroy_strings(&lines);
        return 1;
    }
    for(int i = 0; lines[i] != NULL; i++) {
        fprintf(output, "%s\n", lines[i]);
    }
    fclose(output);
    destroy_strings(&lines);
    printf("File sorted successfully!\n");
    return 0;
}
// При сортировке заметил что вначале будут пустые строчки из файла, потом те , что были в кавычках и только
// потом все остальные. Но это сортировка в соответствии с strcmp, поэтому что есть.