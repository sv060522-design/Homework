#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

template <typename RandIt, typename Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp)
{
    size_t count = finish - start;

    if (count <= 1)
    {
        return;
    }

    if (n < 1)
    {
        n = 1;
    }

    if (static_cast<size_t>(n) > count)
    {
        n = static_cast<int>(count);
    }

    std::vector<RandIt> pos(n + 1);
    std::vector<std::thread> threads;

    size_t len = count / n;
    size_t rem = count % n;
    size_t left = 0;

    for (int i = 0; i < n; i++)
    {
        pos[i] = start + left;

        left += len;

        if (static_cast<size_t>(i) < rem)
        {
            left++;
        }
    }

    pos[n] = finish;

    for (int i = 0; i < n; i++)
    {
        RandIt a = pos[i];
        RandIt b = pos[i + 1];

        threads.emplace_back([a, b, comp]()
        {
            std::sort(a, b, comp);
        });
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    for (int step = 1; step < n; step *= 2)
    {
        threads.clear();

        for (int i = 0; i < n; i += 2 * step)
        {
            int mid = std::min(i + step, n);
            int right = std::min(i + 2 * step, n);

            if (mid < right)
            {
                RandIt a = pos[i];
                RandIt b = pos[mid];
                RandIt c = pos[right];

                threads.emplace_back([a, b, c, comp]()
                {
                    std::inplace_merge(a, b, c, comp);
                });
            }
        }

        for (size_t i = 0; i < threads.size(); i++)
        {
            threads[i].join();
        }
    }
}

int main()
{
    int n;
    std::cin >> n;

    std::cout << "Generating numbers!" << std::endl;

    size_t count = 5000000;
    std::vector<uint64_t> a(count);

    a[0] = 123456789;

    for (size_t i = 1; i < a.size(); i++)
    {
        a[i] = a[i - 1] * i + 1;
    }

    std::vector<uint64_t> b = a;

    std::cout << "Numbers generated!" << std::endl;

    auto comp = [](uint64_t x, uint64_t y)
    {
        return x > y;
    };

    auto start1 = std::chrono::high_resolution_clock::now();

    std::sort(a.begin(), a.end(), comp);

    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();

    parallelSort(n, b.begin(), b.end(), comp);

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Simple time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " milliseconds." << std::endl;
    std::cout << "Parallel time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " milliseconds." << std::endl;

    if (a == b)
    {
        std::cout << "Results are equal." << std::endl;
    }
    else
    {
        std::cout << "Results are different." << std::endl;
    }

    return 0;
}