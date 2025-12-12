#include <iostream>
#include <list>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::list<int> a;
    for (int i = 1; i <= n; ++i) {
        a.push_back(i);
    }

    auto b = a.begin();
    while (a.size() > 1) {
        for (int i = 1; i < m; ++i) {
            ++b;
            if (b == a.end()) {
                b = a.begin();
            }
        }
        std::cout << *b << " ";
        auto c = b;
        ++c;
        if (c == a.end()) {
            c = a.begin();
        }
        a.erase(b);
        b = c;
    }

    std::cout << "\n" << a.front() << "\n";

    return 0;
}