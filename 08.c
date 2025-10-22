#include <stdio.h>
#include <stdlib.h>
struct color
{
    unsigned char r, g, b;
};
typedef struct color Color;
int main()
{
    int width = 600, height = 400;
    Color* data = (Color*)malloc(sizeof(Color) * width * height);
    int center_x = width / 2;
    int center_y = height / 2;
    int radius = (3 * (height < width ? height : width)) / 10;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int dx = i - center_x;
            int dy = j - center_y;
            if (dx * dx + dy * dy <= radius * radius)
            {
                data[i + width * j].r = 190;
                data[i + width * j].g = 0;
                data[i + width * j].b = 41;
            }
            else
            {
                data[i + width * j].r = 255;
                data[i + width * j].g = 255;
                data[i + width * j].b = 255;
            }
        }
    }
    FILE* file = fopen("japan_flag.ppm", "wb");
    fprintf(file, "P6\n%i %i\n255\n", width, height);
    fwrite(data, sizeof(Color), width * height, file);
    fclose(file);
    free(data);
    return 0;
}
