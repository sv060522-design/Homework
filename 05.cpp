#include <iostream>
#include <string>

struct Book {
    std::string title;
    int pages;
    float price;
};

bool isExpensive(const Book& book) {
    return book.price > 1000;
}

int main() {
    Book book1 = {"C++ Programming", 500, 999.99f};
    Book book2 = {"Advanced C++", 800, 1500.50f};
    
    std::cout << std::boolalpha;
    std::cout << "Book1: " << isExpensive(book1) << std::endl;
    std::cout << "Book2: " << isExpensive(book2) << std::endl;
    
    return 0;
}