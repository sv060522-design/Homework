#include <stdio.h>
#include <stdlib.h>
float* get_geometric_progression(float a, float r, int n) {
    float* arr = malloc(n * sizeof(float));
    float current = a;
    for(int i = 0; i < n; i++) {
        arr[i] = current;
        current *= r;
    }
    return arr;
}
int main() {
    float* progr = get_geometric_progression(3.0, 3.0, 10);
    for(int i = 0; i < 10; i++) {
        printf("%.0f\n", progr[i]);
    }
    free(progr);
    return 0;
}