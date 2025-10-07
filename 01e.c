#include <stdio.h>
#include <stdlib.h>
struct book {
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;
int main() {
    Book b;
    Book** p = malloc(sizeof(Book*));
    *p = &b;
    printf("%p\n", *p);
    free(p);
    return 0;
}
// Здесь я не до конца понял, что печатать. Но вроде сказано что печатать именно объекты созданные в куче. Поэтому
// печатаю указатель так как сама структура не в куче, а в стеке.