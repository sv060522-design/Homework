#include <iostream>
#include <memory>
#include <utility>
#include <string>

template <typename T>
class ForwardList
{
private:
    struct Node
    {
        T value;
        std::unique_ptr<Node> next;

        Node(T x) : value(std::move(x)), next(nullptr)
        {
        }
    };

    std::unique_ptr<Node> mpHead;
    Node* mpTail;

public:
    ForwardList() : mpHead(nullptr), mpTail(nullptr)
    {
    }

    void print()
    {
        std::cout << "(";

        Node* p = mpHead.get();

        while (p != nullptr)
        {
            std::cout << p->value;

            if (p->next != nullptr)
            {
                std::cout << ", ";
            }

            p = p->next.get();
        }

        std::cout << ")" << std::endl;
    }

    void push_front(T elem)
    {
        auto p = std::make_unique<Node>(std::move(elem));

        if (mpHead == nullptr)
        {
            mpTail = p.get();
        }
        else
        {
            p->next = std::move(mpHead);
        }

        mpHead = std::move(p);
    }

    void push_back(T elem)
    {
        auto p = std::make_unique<Node>(std::move(elem));
        Node* q = p.get();

        if (mpHead == nullptr)
        {
            mpHead = std::move(p);
        }
        else
        {
            mpTail->next = std::move(p);
        }

        mpTail = q;
    }

    std::unique_ptr<T> pop_front()
    {
        if (mpHead == nullptr)
        {
            return nullptr;
        }

        auto p = std::move(mpHead);
        auto res = std::make_unique<T>(std::move(p->value));
        mpHead = std::move(p->next);

        if (mpHead == nullptr)
        {
            mpTail = nullptr;
        }

        return res;
    }

    std::unique_ptr<T> pop_back()
    {
        if (mpHead == nullptr)
        {
            return nullptr;
        }

        if (mpHead.get() == mpTail)
        {
            return pop_front();
        }

        Node* p = mpHead.get();

        while (p->next.get() != mpTail)
        {
            p = p->next.get();
        }

        auto res = std::make_unique<T>(std::move(mpTail->value));
        p->next.reset();
        mpTail = p;

        return res;
    }

    void clear()
    {
        while (mpHead != nullptr)
        {
            auto p = std::move(mpHead);
            mpHead = std::move(p->next);
        }

        mpTail = nullptr;
    }

    template <typename F>
    void foreach(F f)
    {
        Node* p = mpHead.get();

        while (p != nullptr)
        {
            f(p->value);
            p = p->next.get();
        }
    }

    void swap(ForwardList& fl)
    {
        std::swap(mpHead, fl.mpHead);
        std::swap(mpTail, fl.mpTail);
    }

    ForwardList copy()
    {
        ForwardList res;

        Node* p = mpHead.get();

        while (p != nullptr)
        {
            res.push_back(p->value);
            p = p->next.get();
        }

        return res;
    }
};

int main()
{
    ForwardList<int> a;

    a.print();

    a.push_back(10);
    a.push_back(20);
    a.push_front(5);
    a.print();

    auto x = a.pop_front();

    if (x != nullptr)
    {
        std::cout << *x << std::endl;
    }

    a.print();

    auto y = a.pop_back();

    if (y != nullptr)
    {
        std::cout << *y << std::endl;
    }

    a.print();

    a.foreach([](int& x)
    {
        x *= 2;
    });

    a.print();

    ForwardList<int> b;
    b.push_back(100);
    b.push_back(200);

    a.swap(b);

    a.print();
    b.print();

    ForwardList<int> c = a.copy();

    c.push_back(300);

    a.print();
    c.print();

    a.clear();
    a.print();

    ForwardList<std::string> s;

    std::string q = "Cat";

    s.push_back(q);
    s.push_back(std::string{"Dog"});
    s.push_front("Mouse");

    s.print();

    return 0;
}