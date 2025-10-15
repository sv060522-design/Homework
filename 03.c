// Называется так, так как main.c нужен для многих задач и неудобно переписывать и сохранять его каждый раз.
#include <stdio.h>
int main() {
#ifdef DOG
    printf("Dog!\n");
#else
    printf("No dog!\n");
#endif
    return 0;
}