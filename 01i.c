#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book {
    char title[50];
    int pages;
    float price;
};
typedef struct book Book;
struct library {
    Book* books;
    int number_of_books;
};
typedef struct library Library;
void library_create(Library* l, int n) {
    l->books = malloc(n * sizeof(Book));
    l->number_of_books = n;
}
void library_set(Library l, int i, char* t, int p, float pr) {
    strcpy(l.books[i].title, t);
    l.books[i].pages = p;
    l.books[i].price = pr;
}
Book* library_get(Library l, int i) {
    return &l.books[i];
}
void library_print(Library l) {
    for(int i = 0; i < l.number_of_books; i++) {
        printf("%s\n%d\n%.1f\n", l.books[i].title, l.books[i].pages, l.books[i].price);
    }
}
void library_destroy(Library* l) {
    free(l->books);
    l->books = NULL;
    l->number_of_books = 0;
}
void print_book(Book* b) {
    printf("%s\n%d\n%.1f\n", b->title, b->pages, b->price);
}
int main() {
    Library a;
    library_create(&a, 3);
    library_set(a, 0, "Don Quixote", 1000, 750.0);
    library_set(a, 1, "Oblomov", 400, 250.0);
    library_set(a, 2, "The Odyssey", 500, 500.0);
    library_print(a);
    print_book(library_get(a, 1));
    library_destroy(&a);
    return 0;
}