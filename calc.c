#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: Wrong number of arguments!\n");
        printf("Usage: %s <number> <operator> <number>\n", argv[0]);
        return 1;
    }
    char *endptr1, *endptr2;
    long num1 = strtol(argv[1], &endptr1, 10);
    long num2 = strtol(argv[3], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        printf("Error: Operands should be integers!\n");
        return 1;
    }
    char op = argv[2][0];
    if (argv[2][1] != '\0' || (op != '+' && op != '-' && op != '*' && op != '/' && op != '%')) {
        printf("Error: Invalid operator!\n");
        return 1;
    }
    if (op == '/' && num2 == 0) {
        printf("Error: Division by zero!\n");
        return 1;
    }
    if (op == '%' && num2 == 0) {
        printf("Error: Division by zero!\n");
        return 1;
    }
    long result;
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        case '%': result = num1 % num2; break;
        default: return 1;
    }
    printf("%ld\n", result);
    return 0;
}