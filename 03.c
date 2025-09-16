#include <stdio.h>
float yearfrac(int year, int day) {
    int days = (year % 4 == 0) ? 366 : 365;
    return (float)day / days;
}
int main() {
    int year, day;
    scanf("%d %d", &year, &day);
    printf("%.5f\n", yearfrac(year, day));
    return 0;
}