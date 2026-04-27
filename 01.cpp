#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> a(n);

    std::copy_n(std::istream_iterator<int>(std::cin), n, a.begin());

    auto m = std::max_element(a.begin(), a.end());

    std::sort(a.begin(), m);
    std::sort(std::next(m), a.end(), std::greater<int>());

    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}