#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

template <typename T>
class SafeQueue
{
private:
    std::queue<T> q;
    std::mutex m;

public:
    void push(const T& x)
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(x);
    }

    bool pop(T& x)
    {
        std::lock_guard<std::mutex> lock(m);

        if (q.empty())
        {
            return false;
        }

        x = q.front();
        q.pop();

        return true;
    }
};

void add(SafeQueue<int>& q, int left, int right)
{
    for (int i = left; i <= right; i++)
    {
        q.push(i);
    }
}

void get(SafeQueue<int>& q, int n, int& sum)
{
    int count = 0;

    while (count < n)
    {
        int x;

        if (q.pop(x))
        {
            sum += x;
            count++;
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

int main()
{
    SafeQueue<int> q;

    int sum1 = 0;
    int sum2 = 0;

    std::thread t1(add, std::ref(q), 1, 10);
    std::thread t2(add, std::ref(q), 11, 20);

    std::thread t3(get, std::ref(q), 10, std::ref(sum1));
    std::thread t4(get, std::ref(q), 10, std::ref(sum2));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Sum = " << sum1 + sum2 << std::endl;

    return 0;
}