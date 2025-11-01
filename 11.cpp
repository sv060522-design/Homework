#include <iostream>
#include <vector>

void doubling(std::vector<int>& v) {
    std::vector<int> temp = v;
    v.insert(v.end(), temp.begin(), temp.end());
}

int main() {
    std::vector<int> v {10, 20, 30};
    doubling(v);

    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    return 0;
}