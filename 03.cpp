#include <iostream>
#include <thread>
#include <mutex>

template <typename T>
class SafeQueue
{
private:
    struct Node
    {
        T value;
        Node* next;

        Node()
        {
            next = nullptr;
        }

        Node(const T& x)
        {
            value = x;
            next = nullptr;
        }
    };

    Node* first;
    Node* last;
    std::mutex first_m;
    std::mutex last_m;

public:
    SafeQueue()
    {
        first = new Node;
        last = first;
    }

    ~SafeQueue()
    {
        while (first != nullptr)
        {
            Node* p = first;
            first = first->next;
            delete p;
        }
    }

    SafeQueue(const SafeQueue&) = delete;

    SafeQueue& operator=(const SafeQueue&) = delete;

    void push(const T& x)
    {
        Node* p = new Node(x);

        std::lock_guard<std::mutex> lock(last_m);

        last->next = p;
        last = p;
    }

    bool pop(T& x)
    {
        std::lock_guard<std::mutex> lock_first(first_m);

        {
            std::lock_guard<std::mutex> lock_last(last_m);

            if (first == last)
            {
                return false;
            }
        }

        Node* p = first;
        Node* q = first->next;

        x = q->value;
        first = q;

        delete p;

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

    int x;

    if (!q.pop(x))
    {
        std::cout << "Queue is empty." << std::endl;
    }

    return 0;
}