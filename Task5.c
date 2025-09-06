#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int current = n;
    int length = 1;
    int max = n;
    
    printf("%d", current);
    
    while (current != 1) {
        if (current % 2 == 1) {
            current = 3 * current + 1;
        } else {
            current = current / 2;
        }
        
        printf(" %d", current);
        length++;
        
        if (current > max) {
            max = current;
        }
    }
    
    printf("\nLength = %d, Max = %d", length, max);
    
    return 0;
}