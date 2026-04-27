#include <iostream>
#include <string>
#include <vector>
#include <utility>

class StringStack
{
private:
    std::vector<std::string> v;

public:
    void push(std::string s)
    {
        v.push_back(std::move(s));
    }

    void print() const
    {
        std::cout << "(";

        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i];

            if (i + 1 < v.size())
            {
                std::cout << ", ";
            }
        }

        std::cout << ")" << std::endl;
    }

    std::string pop()
    {
        std::string s = std::move(v.back());
        v.pop_back();
        return s;
    }
};

int main()
{
    StringStack ss;
    std::string a {"Cat"};

    ss.push(a);
    ss.push(std::string{"Mouse"});
    ss.print();

    std::cout << a << std::endl;

    ss.push(std::move(a));
    ss.print();

    std::cout << a << std::endl;

    std::cout << ss.pop() << std::endl;
    ss.print();

    std::cout << ss.pop() << std::endl;
    std::cout << ss.pop() << std::endl;
    ss.print();

    return 0;
}