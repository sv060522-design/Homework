#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>

template <typename RandIt>
RandIt getMax(RandIt start, RandIt finish)
{
    RandIt ans = start;

    for (RandIt it = start; it != finish; ++it)
    {
        if (*it > *ans)
        {
            ans = it;
        }
    }

    return ans;
}

template <typename RandIt>
RandIt getMax(int n, RandIt start, RandIt finish)
{
    size_t count = finish - start;

    if (count == 0)
    {
        return finish;
    }

    if (n < 1)
    {
        n = 1;
    }

    if (static_cast<size_t>(n) > count)
    {
        n = static_cast<int>(count);
    }

    std::vector<std::thread> threads;
    std::vector<RandIt> ans(n);

    size_t len = count / n;
    size_t rem = count % n;
    size_t left = 0;

    for (int i = 0; i < n; i++)
    {
        size_t right = left + len;

        if (static_cast<size_t>(i) < rem)
        {
            right++;
        }

        RandIt a = start + left;
        RandIt b = start + right;

        threads.emplace_back([a, b, &ans, i]()
        {
            ans[i] = getMax(a, b);
        });

        left = right;
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    RandIt res = ans[0];

    for (int i = 1; i < n; i++)
    {
        if (*ans[i] > *res)
        {
            res = ans[i];
        }
    }

    return res;
}

int main()
{
    int n;
    std::cin >> n;

    std::cout << "Generating numbers!" << std::endl;

    size_t count = 10000000;
    std::deque<uint64_t> numbers(count);

    numbers[0] = 123456789;

    for (size_t i = 1; i < numbers.size(); i++)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }

    std::cout << "Numbers generated!" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    auto it1 = getMax(numbers.begin(), numbers.end());

    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();

    auto it2 = getMax(n, numbers.begin(), numbers.end());

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Simple maximum = " << *it1 << std::endl;
    std::cout << "Simple time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " milliseconds." << std::endl;

    std::cout << "Parallel maximum = " << *it2 << std::endl;
    std::cout << "Parallel time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " milliseconds." << std::endl;

    std::deque<double> d {1.2, 5.1, 8.2, 1.0, 0.2, 5.0, 7.8};

    auto it3 = getMax(3, d.begin(), d.end());

    std::cout << "Deque double maximum = " << *it3 << std::endl;

    return 0;
}