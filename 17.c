#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
void apply_sepia(Color* data, int width, int height) {
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
}
void apply_blur(Color* data, int width, int height, int iterations) {
    Color* temp = (Color*)malloc(sizeof(Color) * width * height);
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
    free(temp);
}
void apply_brighter(Color* data, int width, int height, int brightness) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color* pixel = &data[i + width * j];
            int red = pixel->r + brightness;
            int green = pixel->g + brightness;
            int blue = pixel->b + brightness;
            pixel->r = (red > 255) ? 255 : (red < 0) ? 0 : red;
            pixel->g = (green > 255) ? 255 : (green < 0) ? 0 : green;
            pixel->b = (blue > 255) ? 255 : (blue < 0) ? 0 : blue;
        }
    }
}
void apply_bw(Color* data, int width, int height) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color* pixel = &data[i + width * j];
            unsigned char gray = 0.299 * pixel->r + 0.587 * pixel->g + 0.114 * pixel->b;
            pixel->r = gray;
            pixel->g = gray;
            pixel->b = gray;
        }
    }
}
void apply_changecolors(Color* data, int width, int height) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color* pixel = &data[i + width * j];
            unsigned char temp = pixel->r;
            pixel->r = pixel->b;
            pixel->b = temp;
        }
    }
}
void apply_mirror(Color* data, int width, int height) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width / 2; i++) {
            Color temp = data[i + width * j];
            data[i + width * j] = data[(width - 1 - i) + width * j];
            data[(width - 1 - i) + width * j] = temp;
        }
    }
}
int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage:\n");
        printf("  mge --sepia input.ppm output.ppm\n");
        printf("  mge --blur iterations input.ppm output.ppm\n");
        printf("  mge --brighter brightness input.ppm output.ppm\n");
        printf("  mge --bw input.ppm output.ppm\n");
        printf("  mge --changecolors input.ppm output.ppm\n");
        printf("  mge --mirror input.ppm output.ppm\n");
        return 1;
    }
    char* input_filename;
    char* output_filename;
    int effect_param = 0;
    if (strcmp(argv[1], "--sepia") == 0 && argc == 4) {
        input_filename = argv[2];
        output_filename = argv[3];
    } else if (strcmp(argv[1], "--blur") == 0 && argc == 5) {
        effect_param = atoi(argv[2]);
        input_filename = argv[3];
        output_filename = argv[4];
    } else if (strcmp(argv[1], "--brighter") == 0 && argc == 5) {
        effect_param = atoi(argv[2]);
        input_filename = argv[3];
        output_filename = argv[4];
    } else if (strcmp(argv[1], "--bw") == 0 && argc == 4) {
        input_filename = argv[2];
        output_filename = argv[3];
    } else if (strcmp(argv[1], "--changecolors") == 0 && argc == 4) {
        input_filename = argv[2];
        output_filename = argv[3];
    } else if (strcmp(argv[1], "--mirror") == 0 && argc == 4) {
        input_filename = argv[2];
        output_filename = argv[3];
    } else {
        printf("Invalid arguments\n");
        return 1;
    }
    FILE* inputfile = fopen(input_filename, "rb");
    if (!inputfile) {
        printf("Can't open input file: %s\n", input_filename);
        return 1;
    }
    int width, height;
    fscanf(inputfile, "P6\n%d %d\n255\n", &width, &height);
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    fread(data, sizeof(Color), width * height, inputfile);
    fclose(inputfile);
    if (strcmp(argv[1], "--sepia") == 0) {
        apply_sepia(data, width, height);
    } else if (strcmp(argv[1], "--blur") == 0) {
        apply_blur(data, width, height, effect_param);
    } else if (strcmp(argv[1], "--brighter") == 0) {
        apply_brighter(data, width, height, effect_param);
    } else if (strcmp(argv[1], "--bw") == 0) {
        apply_bw(data, width, height);
    } else if (strcmp(argv[1], "--changecolors") == 0) {
        apply_changecolors(data, width, height);
    } else if (strcmp(argv[1], "--mirror") == 0) {
        apply_mirror(data, width, height);
    }
    FILE* outputfile = fopen(output_filename, "wb");
    fprintf(outputfile, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, outputfile);
    fclose(outputfile);
    free(data);
    return 0;
}