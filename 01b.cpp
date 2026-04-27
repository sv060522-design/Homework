#include <iostream>
#include <memory>

struct Cat
{
    Cat()
    {
        std::cout << "Constructor" << std::endl;
    }

    ~Cat()
    {
        std::cout << "Destructor" << std::endl;
    }
};

int main()
{
    std::unique_ptr<Cat> p = std::make_unique<Cat>();
    std::unique_ptr<Cat> q = std::move(p);
}