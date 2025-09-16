#include <stdio.h>
#include <math.h>
double f(double t, double x) {
    if (t == 0.0) {
        return 0.0;
    }
    return exp((x - 1) * log(t) - t);
}
double gamma(double x) {
    const double step = 1e-2;
    const double eps = 1e-10;
    double t = 0.0;
    double res = 0.0;
    double prev = f(t, x);
    t += step;
    while (1) {
        double cur = f(t, x);
        double area = (prev + cur) * step / 2.0;
        if (t > x - 1 && area < eps) {
            break;
        }
        res += area;
        prev = cur;
        t += step;
    }
    return res;
}
int main() {
    double x;
    scanf("%lf", &x);
    double res = gamma(x);
    if (fabs(res - round(res)) < 1e-5 && res < 1e10) {
        printf("%.1f\n", res);
    } else if (res > 1e10) {
        printf("%.5e\n", res);
    } else {
        printf("%.5f\n", res);
    }
    return 0;
}