#include <stdio.h>
#define MAX 100
void multiply(float A[MAX][MAX], float B[MAX][MAX], float C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
int main() {
    float A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n1, n2;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            scanf("%f", &A[i][j]);
        }
    }
    scanf("%d", &n2);
    if (n1 != n2) {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            scanf("%f", &B[i][j]);
        }
    }
    multiply(A, B, C, n1);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            printf("%.0f ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}