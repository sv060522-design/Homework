#include <iostream>
#include <string>
#include <vector>
#include <utility>

class CategorySeparator
{
private:
    std::vector<std::string> l;
    std::vector<std::string> r;

    void print(const std::vector<std::string>& v) const
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

public:
    void push(const std::string& s)
    {
        l.push_back(s);
    }

    void push(std::string&& s)
    {
        r.push_back(std::move(s));
    }

    void printLvalues() const
    {
        print(l);
    }

    void printRvalues() const
    {
        print(r);
    }
};

int main()
{
    CategorySeparator cs;

    std::string a {"Cat"};
    std::string b {"Dog"};

    cs.push(a);
    cs.push(std::string{"Mouse"});
    cs.push(a + b);
    cs.push(b);
    cs.push(std::move(b));

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    cs.printLvalues();
    cs.printRvalues();

    return 0;
}