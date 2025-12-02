#include <iostream>
#include <vector>
#include <string>
#include <array>

template<typename Container1, typename Container2>
bool hasMoreElements(const Container1& c1, const Container2& c2)
{
    return c1.size() > c2.size();
}

int main()
{
    std::vector<int> a {10, 20, 30, 40, 50};
    std::string b = "Cat";
    std::string c = "Elephant";
    std::array<int, 3> d {10, 20, 30};
    std::cout << hasMoreElements(a, b) << std::endl;
    std::cout << hasMoreElements(a, c) << std::endl;
    std::cout << hasMoreElements(a, d) << std::endl;
}