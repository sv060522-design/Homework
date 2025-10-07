#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book {
    char* title;
    int pages;
    float price;
};
typedef struct book Book;
int main() {
    Book* b = malloc(sizeof(Book));
    b->title = malloc(12);
    strcpy(b->title, "Don Quixote");
    b->pages = 1000;
    b->price = 750.0;
    printf("%s\n%d\n%.1f\n", b->title, b->pages, b->price);
    free(b->title);
    free(b);
    return 0;
}