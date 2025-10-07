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
    Book* a = malloc(3 * sizeof(Book));
    strcpy(a[0].title, "Don Quixote");
    a[0].pages = 1000;
    a[0].price = 750.0;
    strcpy(a[1].title, "Oblomov");
    a[1].pages = 400;
    a[1].price = 250.0;
    strcpy(a[2].title, "The Odyssey");
    a[2].pages = 500;
    a[2].price = 500.0;
    for(int i = 0; i < 3; i++) {
        printf("%s\n%d\n%.1f\n", a[i].title, a[i].pages, a[i].price);
    }
    free(a);
    return 0;
}