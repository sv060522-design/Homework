#include <stdio.h>
#define MAX 100
void multiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void assign(int A[MAX][MAX], int B[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = B[i][j];
        }
    }
}
void power(int A[MAX][MAX], int C[MAX][MAX], int n, int k) {
    int vrem[MAX][MAX];
    int step2[MAX][MAX];
    assign(step2, A, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = (i == j) ? 1 : 0;
        }
    }
    while (k > 0) {
        if (k % 2 == 1) {
            multiply(C, step2, vrem, n);
            assign(C, vrem, n);
        }
        multiply(step2, step2, vrem, n);
        assign(step2, vrem, n);
        k /= 2;
    }
}
int main() {
    int n, k;
    scanf("%d", &n);
    int A[MAX][MAX], result[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    scanf("%d", &k);
    power(A, result, n, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}