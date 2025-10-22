#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct color {
    unsigned char r, g, b;
};
typedef struct color Color;
double f1(double x, double y) { return fabs(x * y); }
double f2(double x, double y) { return fabs(sin(10 * (x*x + y*y))); }
double f3(double x, double y) { return fabs(sin(5000 * (x*x + y*y))); }
double f4(double x, double y) { return fabs(cos(10*x) * sin(10*y)); }
double f5(double x, double y) { return 0.5 * fabs(sin(3/(0.1+fabs(x))) + sin(3/(0.1+fabs(y)))); }
void create_image(const char* filename, double (*func)(double, double), int k) {
    int width = 500, height = 500;
    Color* data = (Color*)malloc(width * height * sizeof(Color));
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double x = -1.0 + 2.0 * i / (width-1);
            double y = -1.0 + 2.0 * j / (height-1);
            double value = k * func(x, y);
            if (value > 255) value = 255;
            unsigned char c = (unsigned char)value;
            data[i + j * width] = (Color){c, c, c};
        }
    }
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, file);
    fclose(file);
    free(data);
}
int main() {
    int k = 255;
    create_image("function1.ppm", f1, k);
    create_image("function2.ppm", f2, k);
    create_image("function3.ppm", f3, k);
    create_image("function4.ppm", f4, k);
    create_image("function5.ppm", f5, k);
    return 0;
}