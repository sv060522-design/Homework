// Называется так, так как main.c нужен для многих задач и неудобно переписывать и сохранять его каждый раз.
#include <stdio.h>
int main() {
#ifdef COUNT
    #if COUNT > 100
        printf("Count is too large!\n");
    #else
        #ifdef REVERSE
            for (int i = COUNT; i >= 1; i--) {
                printf("%d ", i);
            }
        #else
            for (int i = 1; i <= COUNT; i++) {
                printf("%d ", i);
            }
        #endif
        printf("\n");
    #endif
#else
    printf("No count!\n");
#endif
    return 0;
}