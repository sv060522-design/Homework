#include <stdio.h>
#include <math.h>
#define EPSILON 1e-5
int main() {
    double x1, y1, r1, x2, y2, r2;
    scanf("%lf %lf %lf", &x1, &y1, &r1);
    scanf("%lf %lf %lf", &x2, &y2, &r2);
    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx*dx + dy*dy);
    double sumr = r1 + r2;
    double diffr = fabs(r1 - r2);
    if (d < EPSILON) {
        if (fabs(r1 - r2) < EPSILON) {
            printf("Intersect\n");
        } else {
            printf("Do not intersect\n");
        }
    } else {
        if (fabs(d - sumr) < EPSILON || fabs(d - diffr) < EPSILON) {
            printf("Touch\n");
        } else if (d < sumr && d > diffr) {
            printf("Intersect\n");
        } else {
            printf("Do not intersect\n");
        }
    }
    return 0;
}