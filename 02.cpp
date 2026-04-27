#include <iostream>
#include <chrono>
#include <vector>
#include <future>

using std::cout;
using std::cin;
using std::endl;
using std::size_t;

uint64_t getMax(const std::vector<uint64_t>& v)
{
    uint64_t res = v[0];

    for (size_t i = 1; i < v.size(); ++i)
    {
        if (v[i] > res)
        {
            res = v[i];
        }
    }

    return res;
}

uint64_t getMax(int n, const std::vector<uint64_t>& v)
{
    if (v.empty())
    {
        return 0;
    }

    if (n < 1)
    {
        n = 1;
    }

    if (n > static_cast<int>(v.size()))
    {
        n = static_cast<int>(v.size());
    }

    std::vector<std::future<uint64_t>> f;
    size_t len = v.size() / n;

    for (int i = 0; i < n; ++i)
    {
        size_t l = i * len;
        size_t r;

        if (i == n - 1)
        {
            r = v.size();
        }
        else
        {
            r = (i + 1) * len;
        }

        f.push_back(std::async(std::launch::async, [&v, l, r]()
        {
            uint64_t res = v[l];

            for (size_t j = l + 1; j < r; ++j)
            {
                if (v[j] > res)
                {
                    res = v[j];
                }
            }

            return res;
        }));
    }

    uint64_t res = f[0].get();

    for (size_t i = 1; i < f.size(); ++i)
    {
        uint64_t x = f[i].get();

        if (x > res)
        {
            res = x;
        }
    }

    return res;
}

int main()
{
    int n;
    cin >> n;

    cout << "Generating numbers!" << endl;

    std::vector<uint64_t> numbers(5e8);
    numbers[0] = 123456789;

    for (size_t i = 1; i < numbers.size(); ++i)
    {
        numbers[i] = numbers[i - 1] * i + 1;
    }

    cout << "Numbers generated!" << endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    uint64_t m1 = getMax(numbers);

    auto end1 = std::chrono::high_resolution_clock::now();

    cout << "One thread maximum = " << m1 << endl;
    cout << "One thread time = "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()
         << " milliseconds." << endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    uint64_t m2 = getMax(n, numbers);

    auto end2 = std::chrono::high_resolution_clock::now();

    cout << "Async maximum = " << m2 << endl;
    cout << "Async time = "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()
         << " milliseconds." << endl;
}