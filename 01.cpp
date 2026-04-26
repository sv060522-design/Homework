#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void run(int i)
{
    std::cout << "Thread #" << i << " started." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(i));
    std::cout << "Thread #" << i << " finished." << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::thread> threads;

    for (int i = 1; i <= n; i++)
    {
        threads.emplace_back(run, i);
    }

    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }

    return 0;
}
// Чтобы был нормальный вывод нужны мьютексы, но поидее в этом семинаре мы их ещё не знаем, поэтому так.