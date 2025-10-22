#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846
void save_numbers_text(const char* filename, double* array, int n) {
    FILE* file = fopen(filename, "w");
    if(!file) return;
    fprintf(file, "%d\n", n);
    for(int i=0; i<n; i++) {
        fprintf(file, "%.15f\n", array[i]);
    }
    fclose(file);
}
void save_numbers_binary(const char* filename, double* array, int n) {
    FILE* file = fopen(filename, "wb");
    if(!file) return;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(array, sizeof(double), n, file);
    fclose(file);
}
int main() {
    int n = 1000;
    double* array = (double*)malloc(n * sizeof(double));
    for(int i=0; i<n; i++) {
        array[i] = sin(M_PI * i / n);
    }
    save_numbers_text("numbers.txt", array, n);
    save_numbers_binary("numbers.bin", array, n);
    free(array);
    return 0;
}