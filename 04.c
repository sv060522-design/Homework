#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int max = INT_MIN;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        
        if (num > max) {
            max = num;
            count = 1;
        } else if (num == max) {
            count++;
        }
    }
    
    printf("%d %d", max, count);
    
    return 0;
}
