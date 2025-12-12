#include <iostream>
#include <vector>
#include <list>
#include <string>

template <typename Container>
auto f(const Container& a) -> std::vector<std::pair<typename Container::value_type, typename Container::value_type>> {
    using T = typename Container::value_type;
    std::vector<std::pair<T, T>> r;

    auto i = a.begin();
    while (i != a.end()) {
        T x = *i;
        ++i;

        T y = T{};
        if (i != a.end()) {
            y = *i;
            ++i;
        }
        
        r.push_back({x, y});
    }
    
    return r;
}

int main() {
    std::vector<int> v1 = {10, 20, 30, 40, 50};
    auto r1 = f(v1);
    for (const auto& p : r1) {
        std::cout << "{" << p.first << ", " << p.second << "} ";
    }
    std::cout << "\n";
    
    std::list<std::string> l1 = {"cat", "dog", "mouse", "lion"};
    auto r2 = f(l1);
    for (const auto& p : r2) {
        std::cout << "{" << p.first << ", " << p.second << "} ";
    }
    std::cout << "\n";
    
    std::string s1 = "Hello";
    auto r3 = f(s1);
    for (const auto& p : r3) {
        std::cout << "{" << p.first << ", " << p.second << "} ";
    }
    std::cout << "\n";
    
    return 0;
}