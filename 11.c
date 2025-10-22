#include <stdio.h>
#include <stdlib.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <ppm image>\n", argv[0]);
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
    fread(data, sizeof(Color), width * height, inputfile);
    fclose(inputfile);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color* pixel = &data[i + width * j];
            unsigned char gray = 0.299 * pixel->r + 0.587 * pixel->g + 0.114 * pixel->b;
            pixel->r = gray;
            pixel->g = gray;
            pixel->b = gray;
        }
    }
    FILE* outputfile = fopen("result.ppm", "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, outputfile);
    fclose(outputfile);
    free(data);
    return 0;
}