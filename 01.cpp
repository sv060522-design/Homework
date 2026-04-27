#include <atomic>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

struct hp_item
{
    std::atomic<std::thread::id> id;
    std::atomic<void*> p;
};

const int hp_n = 200;
hp_item hp_a[hp_n];

class hp_owner
{
    hp_item* r;

public:
    hp_owner()
    {
        r = nullptr;

        for (int i = 0; i < hp_n; ++i)
        {
            std::thread::id x;
            if (hp_a[i].id.compare_exchange_strong(x, std::this_thread::get_id()))
            {
                r = hp_a + i;
                break;
            }
        }

        if (r == nullptr)
            std::abort();
    }

    hp_owner(const hp_owner&) = delete;
    hp_owner& operator=(const hp_owner&) = delete;

    std::atomic<void*>& get()
    {
        return r->p;
    }

    ~hp_owner()
    {
        r->p.store(nullptr);
        r->id.store(std::thread::id());
    }
};

std::atomic<void*>& get_hp(int i)
{
    thread_local hp_owner a;
    thread_local hp_owner b;

    if (i == 0)
        return a.get();

    return b.get();
}

bool has_hp(void* p)
{
    for (int i = 0; i < hp_n; ++i)
    {
        if (hp_a[i].p.load() == p)
            return true;
    }

    return false;
}

template <typename T>
class queue_list
{
    struct node
    {
        std::shared_ptr<T> data;
        std::atomic<node*> next;

        node()
        {
            next.store(nullptr);
        }

        node(T x)
        {
            data = std::make_shared<T>(x);
            next.store(nullptr);
        }
    };

    struct del_node
    {
        node* p;
        del_node* next;
    };

    std::atomic<node*> head;
    std::atomic<node*> tail;
    std::atomic<int> cnt;
    std::atomic<del_node*> del;

    void add(del_node* a)
    {
        if (a == nullptr)
            return;

        del_node* b = a;

        while (b->next != nullptr)
            b = b->next;

        b->next = del.load();

        while (!del.compare_exchange_weak(b->next, a))
        {
        }
    }

    void add(node* p)
    {
        if (p != nullptr)
            add(new del_node{p, nullptr});
    }

    void clear(del_node* a)
    {
        while (a != nullptr)
        {
            del_node* b = a->next;
            delete a->p;
            delete a;
            a = b;
        }
    }

    void enter()
    {
        cnt.fetch_add(1);
    }

    void leave(node* p)
    {
        if (cnt.load() == 1)
        {
            del_node* a = del.exchange(nullptr);

            if (cnt.fetch_sub(1) == 1)
                clear(a);
            else
                add(a);

            delete p;
        }
        else
        {
            add(p);
            cnt.fetch_sub(1);
        }
    }

public:
    queue_list()
    {
        node* a = new node;
        head.store(a);
        tail.store(a);
        cnt.store(0);
        del.store(nullptr);
    }

    queue_list(const queue_list&) = delete;
    queue_list& operator=(const queue_list&) = delete;

    ~queue_list()
    {
        while (pop())
        {
        }

        delete head.load();
        clear(del.exchange(nullptr));
    }

    void push(T x)
    {
        node* c = new node(x);
        enter();

        while (true)
        {
            node* a = tail.load();
            node* b = a->next.load();

            if (a == tail.load())
            {
                if (b == nullptr)
                {
                    if (a->next.compare_exchange_weak(b, c))
                    {
                        tail.compare_exchange_weak(a, c);
                        leave(nullptr);
                        return;
                    }
                }
                else
                {
                    tail.compare_exchange_weak(a, b);
                }
            }
        }
    }

    std::shared_ptr<T> pop()
    {
        enter();

        while (true)
        {
            node* a = head.load();
            node* b = tail.load();
            node* c = a->next.load();

            if (a == head.load())
            {
                if (c == nullptr)
                {
                    leave(nullptr);
                    return std::shared_ptr<T>();
                }

                if (a == b)
                {
                    tail.compare_exchange_weak(b, c);
                }
                else
                {
                    if (head.compare_exchange_weak(a, c))
                    {
                        std::shared_ptr<T> res = c->data;
                        leave(a);
                        return res;
                    }
                }
            }
        }
    }
};

template <typename T>
class queue_hp
{
    struct node
    {
        std::shared_ptr<T> data;
        std::atomic<node*> next;

        node()
        {
            next.store(nullptr);
        }

        node(T x)
        {
            data = std::make_shared<T>(x);
            next.store(nullptr);
        }
    };

    struct del_node
    {
        node* p;
        del_node* next;
    };

    std::atomic<node*> head;
    std::atomic<node*> tail;
    std::atomic<del_node*> del;

    void add(del_node* a)
    {
        if (a == nullptr)
            return;

        del_node* b = a;

        while (b->next != nullptr)
            b = b->next;

        b->next = del.load();

        while (!del.compare_exchange_weak(b->next, a))
        {
        }
    }

    void clear(del_node* a)
    {
        while (a != nullptr)
        {
            del_node* b = a->next;
            delete a->p;
            delete a;
            a = b;
        }
    }

    void scan()
    {
        del_node* a = del.exchange(nullptr);
        del_node* save = nullptr;

        while (a != nullptr)
        {
            del_node* b = a->next;

            if (has_hp(a->p))
            {
                a->next = save;
                save = a;
            }
            else
            {
                delete a->p;
                delete a;
            }

            a = b;
        }

        add(save);
    }

    void retire(node* p)
    {
        if (p == nullptr)
            return;

        if (has_hp(p))
            add(new del_node{p, nullptr});
        else
            delete p;

        scan();
    }

public:
    queue_hp()
    {
        node* a = new node;
        head.store(a);
        tail.store(a);
        del.store(nullptr);
    }

    queue_hp(const queue_hp&) = delete;
    queue_hp& operator=(const queue_hp&) = delete;

    ~queue_hp()
    {
        while (pop())
        {
        }

        delete head.load();
        clear(del.exchange(nullptr));
    }

    void push(T x)
    {
        node* c = new node(x);

        while (true)
        {
            node* a;

            do
            {
                a = tail.load();
                get_hp(0).store(a);
            }
            while (tail.load() != a);

            node* b = a->next.load();

            if (a == tail.load())
            {
                if (b == nullptr)
                {
                    if (a->next.compare_exchange_weak(b, c))
                    {
                        tail.compare_exchange_weak(a, c);
                        get_hp(0).store(nullptr);
                        scan();
                        return;
                    }
                }
                else
                {
                    tail.compare_exchange_weak(a, b);
                }
            }
        }
    }

    std::shared_ptr<T> pop()
    {
        while (true)
        {
            node* a;

            do
            {
                a = head.load();
                get_hp(0).store(a);
            }
            while (head.load() != a);

            node* b = tail.load();
            node* c = a->next.load();

            if (a != head.load())
                continue;

            if (c == nullptr)
            {
                get_hp(0).store(nullptr);
                get_hp(1).store(nullptr);
                scan();
                return std::shared_ptr<T>();
            }

            get_hp(1).store(c);

            if (a != head.load() || a->next.load() != c)
                continue;

            if (a == b)
            {
                tail.compare_exchange_weak(b, c);
            }
            else
            {
                std::shared_ptr<T> res = c->data;

                if (head.compare_exchange_weak(a, c))
                {
                    get_hp(0).store(nullptr);
                    get_hp(1).store(nullptr);
                    retire(a);
                    return res;
                }
            }
        }
    }
};

template <typename Q>
void test(const char* name)
{
    Q q;

    const int k = 4;
    const int n = 5000;
    const int total = k * n;

    std::atomic<int> cnt(0);
    std::atomic<long long> sum(0);

    std::vector<std::thread> v;

    for (int i = 0; i < k; ++i)
    {
        v.emplace_back([&q, i, n]()
        {
            for (int j = 1; j <= n; ++j)
                q.push(i * n + j);
        });
    }

    for (int i = 0; i < k; ++i)
    {
        v.emplace_back([&q, &cnt, &sum, total]()
        {
            while (cnt.load() < total)
            {
                std::shared_ptr<int> x = q.pop();

                if (x)
                {
                    sum.fetch_add(*x);
                    cnt.fetch_add(1);
                }
                else
                {
                    std::this_thread::yield();
                }
            }
        });
    }

    for (std::thread& t : v)
        t.join();

    long long need = 1LL * total * (total + 1) / 2;

    std::cout << name << std::endl;
    std::cout << "count = " << cnt.load() << std::endl;
    std::cout << "sum = " << sum.load() << std::endl;
    std::cout << "expected = " << need << std::endl;
    std::cout << std::endl;
}

int main()
{
    test<queue_list<int>>("queue with deleted nodes list");
    test<queue_hp<int>>("queue with hazard pointers");
}