#include <stdio.h>
#include <stddef.h>
struct cat {
    char x;
    char y;
};
struct dog {
    char x;
    size_t y;
};
struct mouse {
    char x;
    char y;
    size_t z;
};
struct rat {
    char x;
    size_t y;
    char z;
};
struct fox {
    char x;
    struct mouse y;
};
int main() {
    printf("1. char: size = %zu, alignment = %zu\n", sizeof(char), _Alignof(char));
    printf("2. int: size = %zu, alignment = %zu\n", sizeof(int), _Alignof(int));
    printf("3. size_t: size = %zu, alignment = %zu\n", sizeof(size_t), _Alignof(size_t));
    printf("4. int[10]: size = %zu, alignment = %zu\n", sizeof(int[10]), _Alignof(int[10]));
    printf("5. int*: size = %zu, alignment = %zu\n", sizeof(int*), _Alignof(int*));
    printf("6. struct cat: size = %zu, alignment = %zu\n", sizeof(struct cat), _Alignof(struct cat));
    printf("7. struct dog: size = %zu, alignment = %zu\n", sizeof(struct dog), _Alignof(struct dog));
    printf("8. struct mouse: size = %zu, alignment = %zu\n", sizeof(struct mouse), _Alignof(struct mouse));
    printf("9. struct rat: size = %zu, alignment = %zu\n", sizeof(struct rat), _Alignof(struct rat));
    printf("10. struct fox: size = %zu, alignment = %zu\n", sizeof(struct fox), _Alignof(struct fox));
    return 0;
}