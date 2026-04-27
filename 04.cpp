#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>

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

SafeQueue<std::string> q;

void readFile()
{
    std::ifstream in("invisible_man.txt");

    if (!in.is_open())
    {
        q.push("");
        return;
    }

    std::string s;

    while (std::getline(in, s))
    {
        if (!s.empty())
        {
            q.push(s);
        }
    }

    q.push("");
}

void printText()
{
    while (true)
    {
        std::string s;

        if (q.pop(s))
        {
            if (s.empty())
            {
                break;
            }

            for (size_t i = 0; i < s.size(); i++)
            {
                s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
            }

            std::cout << s << std::endl;
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

int main()
{
    std::thread t1(readFile);
    std::thread t2(printText);

    t1.join();
    t2.join();

    return 0;
}