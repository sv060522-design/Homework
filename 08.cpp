#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <forward_list>

template <typename It, typename F>
It bestNeighbours(It start, It finish, F f)
{
    if (start == finish)
    {
        return finish;
    }

    It a = start;
    It b = start;
    ++b;

    if (b == finish)
    {
        return finish;
    }

    It ans = a;
    auto best = f(*a, *b);

    ++a;
    ++b;

    while (b != finish)
    {
        auto cur = f(*a, *b);

        if (cur > best)
        {
            best = cur;
            ans = a;
        }

        ++a;
        ++b;
    }

    return ans;
}

template <typename C>
void test(const C& a)
{
    auto it1 = bestNeighbours(a.begin(), a.end(), [](int x, int y)
    {
        return x + y;
    });

    auto it2 = bestNeighbours(a.begin(), a.end(), [](int x, int y)
    {
        return std::abs(x - y);
    });

    std::cout << "{";

    if (it1 != a.end())
    {
        std::cout << *it1;
    }

    std::cout << ", ";

    if (it2 != a.end())
    {
        std::cout << *it2;
    }

    std::cout << "}" << std::endl;
}

int main()
{
    std::vector<int> a{50, 10, 10, 20, 90, 30, 40, 60, 80, 20};
    std::list<int> b{50, 10, 10, 20, 90, 30, 40, 60, 80, 20};
    std::set<int> c{50, 10, 10, 20, 90, 30, 40, 60, 80, 20};
    std::forward_list<int> d{50, 10, 10, 20, 90, 30, 40, 60, 80, 20};

    test(a);
    test(b);
    test(c); // Тут будут ответы другие,т.к. set уже отсортирован по возрастанию. Типа во всех вывод {60, 20}, а для множества {80, 60}.
    test(d);

    return 0;
}