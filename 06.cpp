#include <iostream>
#include <thread>
#include <vector>
#include <string>

using namespace std::string_literals;

void func(const std::string& a, int b)
{
    std::cout << a << " " << b << std::endl;
}

template <typename F, typename... Args>
void iterate(int n, F f, Args... args)
{
    std::vector<std::thread> threads;

    for (int i = 0; i < n; i++)
    {
        threads.emplace_back(f, args...);
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }
}

int main()
{
    iterate(5, func, "Hello"s, 12345);

    return 0;
}