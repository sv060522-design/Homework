#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;
    
    std::multiset<int> s;
    
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        s.insert(x);
    }
    
    for (int x : s) {
        std::cout << x << " ";
    }
    
    return 0;
}