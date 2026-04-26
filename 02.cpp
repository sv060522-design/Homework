#include <iostream>
#include <thread>
#include <chrono>

void run(int i, int n)
{
    std::cout << "Thread #" << i << " started." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    if (i < n)
    {
        std::thread t(run, i + 1, n);
        t.join();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::cout << "Thread #" << i << " finished." << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    if (n <= 0)
    {
        return 0;
    }

    std::thread t(run, 1, n);
    t.join();

    return 0;
}