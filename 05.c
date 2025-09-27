#include <stdio.h>
#include <math.h>
int solve_quadratic(double a, double b, double c, double* px1, double* px2)
{
    double eps = 1e-10;
    double d = b*b - 4*a*c;
    if(fabs(a) < eps)
    {
        if(fabs(b) < eps)
            return 0;
        *px1 = -c / b;
        return 1;
    }
    if(d < -eps)
        return 0;
    if(fabs(d) < eps)
    {
        *px1 = -b / (2*a);
        return 1;
    }
    double sqrt_d = sqrt(d);
    *px1 = (-b - sqrt_d) / (2*a);
    *px2 = (-b + sqrt_d) / (2*a);
    return 2;
}
int main()
{
    double a, b, c, x1, x2;
    scanf("%lf %lf %lf", &a, &b, &c);
    int result = solve_quadratic(a, b, c, &x1, &x2);
    if(result == 0)
        printf("0\n");
    else if(result == 1)
        printf("1 %f\n", x1);
    else
        printf("2 %f %f\n", x1, x2);
    return 0;
}