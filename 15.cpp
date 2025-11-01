#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void print(const std::vector<int>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void print(const int* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

char& get(std::string& str, std::size_t index) {
    if (index >= str.size()) {
        std::cerr << "Index out of range" << std::endl;
        std::exit(1);
    }
    return str[index];
}

int& get(std::vector<int>& v, std::size_t index) {
    if (index >= v.size()) {
        std::cerr << "Index out of range" << std::endl;
        std::exit(1);
    }
    return v[index];
}

int& get(int* arr, std::size_t size, std::size_t index) {
    if (index >= size) {
        std::cerr << "Index out of range" << std::endl;
        std::exit(1);
    }
    return arr[index];
}

int main() {
    std::vector<int> v {10, 20, 30, 40, 50};
    get(v, 2) += 1;
    print(v);

    std::string s = "Cat";
    get(s, 0) = 'B';
    std::cout << s << std::endl;

    int a[5] = {10, 20, 30, 40, 50};
    get(a, 5, 2) += 1;
    print(a, 5);

    get(v, 10) = 0;
    return 0;
}