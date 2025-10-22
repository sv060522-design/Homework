#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
void draw_circle(Color* data, int width, int height, int x0, int y0, int r, Color c) {
    for (int y = y0 - r; y <= y0 + r; y++) {
        for (int x = x0 - r; x <= x0 + r; x++) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                int dx = x - x0;
                int dy = y - y0;
                if (dx * dx + dy * dy <= r * r) {
                    data[x + y * width] = c;
                }
            }
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <a> <b>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    if (n <= 0 || a <= 0 || b <= 0 || a > b) {
        printf("Invalid parameters\n");
        return 1;
    }
    srand(time(NULL));
    int width = 800;
    int height = 600;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    for (int i = 0; i < width * height; i++) {
        data[i].r = 255;
        data[i].g = 255;
        data[i].b = 255;
    }
    for (int circle = 0; circle < n; circle++) {
        int x0 = rand() % width;
        int y0 = rand() % height;
        int r = a + rand() % (b - a + 1);
        Color c;
        c.r = rand() % 256;
        c.g = rand() % 256;
        c.b = rand() % 256;
        draw_circle(data, width, height, x0, y0, r, c);
    }
    FILE* file = fopen("circles.ppm", "wb");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, file);
    fclose(file);
    free(data);
    return 0;
}