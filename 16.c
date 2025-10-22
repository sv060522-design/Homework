#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void draw_tree(Color* data, int width, int height, int x, int y, int length, double angle, int depth) {
    if (depth <= 0) return;
    int x1 = x + length * cos(angle);
    int y1 = y + length * sin(angle);
    Color black = {0, 0, 0};
    draw_line(data, width, height, x, y, x1, y1, black);
    int new_length = length * 0.7;
    draw_tree(data, width, height, x1, y1, new_length, angle - M_PI/9, depth - 1);
    draw_tree(data, width, height, x1, y1, new_length, angle + M_PI/9, depth - 1);
}
int main(int argc, char** argv) {
    int depth = 12;
    if (argc == 2) {
        depth = atoi(argv[1]);
    }
    int width = 800, height = 600;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            data[i + width * j] = (Color){255, 255, 255};
        }
    }
    int start_x = width / 2;
    int start_y = height - 50;
    int trunk_length = 120;
    draw_tree(data, width, height, start_x, start_y, trunk_length, -M_PI/2, depth);
    FILE* file = fopen("tree.ppm", "wb");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, file);
    fclose(file);
    free(data);
    return 0;
}