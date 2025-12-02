#include <iostream>
#include <vector>
#include <utility>

template<typename T>
std::pair<T, T> minmax(const std::vector<T>& v)
{
    T min_val = v[0];
    T max_val = v[0];
    
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] < min_val) {
            min_val = v[i];
        }
        if (max_val < v[i]) {
            max_val = v[i];
        }
    }
    
    return std::make_pair(min_val, max_val);
}

int main()
{
    std::vector<int> a {60, 10, 40, 80, 30};
    auto am = minmax(a);
    std::cout << am.first << " " << am.second << std::endl;

    std::vector<std::string> b {"Cat", "Dog", "Mouse", "Camel", "Wolf"};
    auto bm = minmax(b);
    std::cout << bm.first << " " << bm.second << std::endl;

    std::vector<std::pair<int, int>> c {{10, 90}, {30, 10}, {20, 40}, {10, 50}};
    auto cm = minmax(c);
    std::cout << cm.first.first << " " << cm.first.second << std::endl;
    std::cout << cm.second.first << " " << cm.second.second << std::endl;
}