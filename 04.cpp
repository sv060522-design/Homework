#include <iostream>
#include <map>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::map<int, int> m;
    
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        m[x]++;
    }
    
    std::vector<int> a, b;
    
    for (const auto& p : m) {
        a.push_back(p.first);
        b.push_back(p.second);
    }
    
    for (size_t i = 0; i < a.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << a[i];
    }
    std::cout << "\n";
    
    for (size_t i = 0; i < b.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << b[i];
    }
    
    return 0;
}