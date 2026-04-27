#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

template <typename It>
void swapNeighbours(It start, It finish)
{
    while (start != finish)
    {
        It a = start;
        ++start;

        if (start == finish)
        {
            break;
        }

        std::swap(*a, *start);
        ++start;
    }
}

template <typename C>
void print(const C& a)
{
    std::cout << "{";

    bool f = true;

    for (auto x : a)
    {
        if (!f)
        {
            std::cout << ", ";
        }

        std::cout << x;
        f = false;
    }

    std::cout << "}" << std::endl;
}

int main()
{
    std::vector<int> a{10, 20, 30, 40, 50};
    std::list<int> b{1, 2, 3, 4};
    std::forward_list<int> c{5, 6, 7, 8, 9};

    swapNeighbours(a.begin(), a.end());
    swapNeighbours(b.begin(), b.end());
    swapNeighbours(c.begin(), c.end());

    print(a);
    print(b);
    print(c);

    return 0;
}