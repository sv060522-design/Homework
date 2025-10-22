#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
void draw_line(Color* data, int width, int height, int x0, int y0, int x1, int y1, Color c) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int ysign = y1 > y0 ? 1 : -1;
    int xsign = x1 > x0 ? 1 : -1;
    int error = (dx > dy ? dx : -dy)/2;
    if (dx >= dy) {
        int y = y0;
        for (int x = x0; x != x1; x += xsign) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                data[x + width * y] = c;
            }
            error += dy;
            if (error >= dx) {
                y += ysign;
                error -= dx;
            }
        }
    } else {
        int x = x0;
        for (int y = y0; y != y1; y += ysign) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                data[x + width * y] = c;
            }
            error += dx;
            if (error >= dy) {
                x += xsign;
                error -= dy;
            }
        }
    }
}
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <number_of_lines>\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Number of lines must be positive\n");
        exit(1);
    }
    srand(time(NULL));
    int width = 800, height = 600;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            data[i + width * j] = (Color){0, 0, 0};
        }
    }
    for (int i = 0; i < n; i++) {
        int x0 = rand() % width;
        int y0 = rand() % height;
        int x1 = rand() % width;
        int y1 = rand() % height;
        Color c = {
            (unsigned char)(rand() % 256),
            (unsigned char)(rand() % 256),
            (unsigned char)(rand() % 256)
        };
        draw_line(data, width, height, x0, y0, x1, y1, c);
    }
    FILE* file = fopen("randlines.ppm", "wb");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, file);
    fclose(file);
    free(data);
    return 0;
}