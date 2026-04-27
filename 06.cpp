#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>

template <typename It>
auto maxElement(It start, It finish) -> decltype(*start)
{
    It ans = start;

    for (It it = start; it != finish; ++it)
    {
        if (*ans < *it)
        {
            ans = it;
        }
    }

    return *ans;
}

int main()
{
    std::vector<int> a{10, 20, 5, 40, 30};
    std::list<int> b{7, 3, 15, 2, 11};
    std::set<int> c{9, 1, 25, 4, 16};
    std::vector<std::string> d{"cat", "dog", "mouse", "elephant"};

    std::cout << maxElement(a.begin(), a.end()) << std::endl;
    std::cout << maxElement(b.begin(), b.end()) << std::endl;
    std::cout << maxElement(c.begin(), c.end()) << std::endl;
    std::cout << maxElement(d.begin(), d.end()) << std::endl;

    return 0;
}