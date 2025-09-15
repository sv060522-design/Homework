#include <stdio.h>
int is_even(int x) {
    if (x % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    printf("%i\n", is_even(90));
    printf("%i\n", is_even(91));
}