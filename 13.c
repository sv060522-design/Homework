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
            int r_old = pixel->r;
            int g_old = pixel->g;
            int b_old = pixel->b;
            int r_new = 0.393 * r_old + 0.769 * g_old + 0.189 * b_old;
            int g_new = 0.349 * r_old + 0.686 * g_old + 0.168 * b_old;
            int b_new = 0.272 * r_old + 0.534 * g_old + 0.131 * b_old;
            pixel->r = (r_new > 255) ? 255 : r_new;
            pixel->g = (g_new > 255) ? 255 : g_new;
            pixel->b = (b_new > 255) ? 255 : b_new;
        }
    }
    FILE* outputfile = fopen("result.ppm", "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, outputfile);
    fclose(outputfile);
    free(data);
    return 0;
}