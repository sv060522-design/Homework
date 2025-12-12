#include <iostream>
#include <set>


int main() {
    int n, k;
    std::cin >> n >> k;
    
    std::set<int> s;
    std::multiset<int> m;
    
    s.insert(0);
    s.insert(n);
    m.insert(n);
    
    for (int i = 0; i < k; ++i) {
        int x;
        std::cin >> x;
        
        auto a = s.lower_bound(x);
        auto b = a;
        --b;
        
        int l = *b;
        int r = *a;
        
        m.erase(m.find(r - l));
        m.insert(x - l);
        m.insert(r - x);
        
        s.insert(x);
        
        std::cout << *m.rbegin() << " ";
    }
    
    return 0;
}