#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book {
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;
int main() {
    Book** p = malloc(sizeof(Book*));
    *p = malloc(sizeof(Book));
    strcpy((*p)->title, "Don Quixote");
    (*p)->pages = 1000;
    (*p)->price = 750.0;
    printf("%s\n%d\n%.1f\n", (*p)->title, (*p)->pages, (*p)->price);
    free(*p);
    free(p);
    return 0;
}