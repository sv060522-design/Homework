#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

uint64_t getMax(const std::vector<uint64_t>& v)
{
    uint64_t result = v.at(0);

    for (uint64_t x : v)
    {
        if (x > result)
        {
            result = x;
        }
    }

    return result;
}

uint64_t getMaxPar(int n, const std::vector<uint64_t>& v)
{
    if (n < 1)
    {
        n = 1;
    }

    if (static_cast<size_t>(n) > v.size())
    {
        n = static_cast<int>(v.size());
    }

    std::vector<std::thread> threads;
    std::vector<uint64_t> ans(n);

    size_t len = v.size() / n;
    size_t rem = v.size() % n;
    size_t left = 0;

    for (int i = 0; i < n; i++)
    {
        size_t right = left + len;

        if (static_cast<size_t>(i) < rem)
        {
            right++;
        }

        threads.emplace_back([&v, &ans, i, left, right]()
        {
            uint64_t result = v.at(left);

            for (size_t j = left + 1; j < right; j++)
            {
                if (v[j] > result)
                {
                    result = v[j];
                }
            }

            ans[i] = result;
        });

        left = right;
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    return getMax(ans);
}

uint64_t getMax(int n, const std::vector<uint64_t>& v)
{
    return getMaxPar(n, v);
}

int main()
{
    int n;
    std::cin >> n;

    std::cout << "Generating numbers!" << std::endl;

    size_t count = 500000000;
    std::vector<uint64_t> numbers(count);

    numbers[0] = 123456789;

    for (size_t i = 1; i < numbers.size(); i++)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }

    std::cout << "Numbers generated!" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    uint64_t m1 = getMax(numbers);

    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();

    uint64_t m2 = getMaxPar(n, numbers);

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Simple maximum = " << m1 << std::endl;
    std::cout << "Simple time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " milliseconds." << std::endl;

    std::cout << "Parallel maximum = " << m2 << std::endl;
    std::cout << "Parallel time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " milliseconds." << std::endl;

    return 0;
}