#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <ppm image> <iterations>\n", argv[0]);
        exit(1);
    }
    int iterations = atoi(argv[2]);
    if (iterations <= 0) {
        printf("Iterations must be positive\n");
        exit(1);
    }
    FILE* inputfile = fopen(argv[1], "rb");
    if (inputfile == 0) {
        printf("Can't open the file: %s\n", argv[1]);
        exit(1);
    }
    int width, height;
    fscanf(inputfile, "P6\n%d %d\n255\n", &width, &height);
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    Color* temp = (Color*)malloc(sizeof(Color) * width * height);
    fread(data, sizeof(Color), width * height, inputfile);
    fclose(inputfile);
    for (int iter = 0; iter < iterations; iter++) {
        memcpy(temp, data, sizeof(Color) * width * height);
        for (int j = 1; j < height - 1; j++) {
            for (int i = 1; i < width - 1; i++) {
                int sum_r = 0, sum_g = 0, sum_b = 0;
                for (int p = -1; p <= 1; p++) {
                    for (int q = -1; q <= 1; q++) {
                        Color* pixel = &temp[(i + p) + (j + q) * width];
                        sum_r += pixel->r;
                        sum_g += pixel->g;
                        sum_b += pixel->b;
                    }
                }
                data[i + j * width].r = sum_r / 9;
                data[i + j * width].g = sum_g / 9;
                data[i + j * width].b = sum_b / 9;
            }
        }
    }
    FILE* outputfile = fopen("result.ppm", "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, outputfile);
    fclose(outputfile);
    free(data);
    free(temp);
    return 0;
}