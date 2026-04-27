#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class ForwardList
{
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

    void print() const
    {
        std::cout << "{";
        Node* p = mpHead.get();

        while (p)
        {
            std::cout << p->value;

            if (p->next)
                std::cout << ", ";

            p = p->next.get();
        }

        std::cout << "}" << std::endl;
    }

    void push_front(T elem)
    {
        auto p = std::make_unique<Node>(std::move(elem));

        if (!mpHead)
        {
            mpTail = p.get();
            mpHead = std::move(p);
            return;
        }

        p->next = std::move(mpHead);
        mpHead = std::move(p);
    }

    void push_back(T elem)
    {
        auto p = std::make_unique<Node>(std::move(elem));
        Node* q = p.get();

        if (!mpHead)
        {
            mpHead = std::move(p);
            mpTail = q;
            return;
        }

        mpTail->next = std::move(p);
        mpTail = q;
    }

    std::unique_ptr<T> pop_front()
    {
        if (!mpHead)
            return nullptr;

        auto res = std::make_unique<T>(std::move(mpHead->value));

        mpHead = std::move(mpHead->next);

        if (!mpHead)
            mpTail = nullptr;

        return res;
    }

    std::unique_ptr<T> pop_back()
    {
        if (!mpHead)
            return nullptr;

        if (mpHead.get() == mpTail)
        {
            auto res = std::make_unique<T>(std::move(mpHead->value));
            mpHead.reset();
            mpTail = nullptr;
            return res;
        }

        Node* p = mpHead.get();

        while (p->next.get() != mpTail)
            p = p->next.get();

        auto res = std::make_unique<T>(std::move(mpTail->value));

        p->next.reset();
        mpTail = p;

        return res;
    }

    void clear()
    {
        while (mpHead)
            mpHead = std::move(mpHead->next);

        mpTail = nullptr;
    }

    template <typename F>
    void foreach(F f)
    {
        Node* p = mpHead.get();

        while (p)
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

    ForwardList copy() const
    {
        ForwardList res;

        Node* p = mpHead.get();

        while (p)
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

    a.push_back(10);
    a.push_back(20);
    a.push_front(5);
    a.push_back(30);

    a.print();

    auto x = a.pop_front();
    if (x)
        std::cout << *x << std::endl;

    a.print();

    auto y = a.pop_back();
    if (y)
        std::cout << *y << std::endl;

    a.print();

    a.foreach([](int& x)
    {
        x *= 2;
    });

    a.print();

    ForwardList<int> b = a.copy();
    b.push_back(100);

    a.print();
    b.print();

    ForwardList<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);

    a.swap(c);

    a.print();
    c.print();

    c.clear();
    c.print();
}