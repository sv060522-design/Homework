#include <iostream>
#include <vector>
#include <memory>

class Individual
{
public:
    virtual void speak() const = 0;
    virtual ~Individual() = default;
};

class Alice : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Alice" << std::endl;
    }
};

class Bob : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Bob" << std::endl;
    }
};

class Casper : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Casper" << std::endl;
    }
};

std::vector<std::unique_ptr<Individual>> createIndividuals()
{
    std::vector<std::unique_ptr<Individual>> v;

    v.push_back(std::make_unique<Alice>());
    v.push_back(std::make_unique<Alice>());
    v.push_back(std::make_unique<Alice>());

    v.push_back(std::make_unique<Bob>());
    v.push_back(std::make_unique<Bob>());

    v.push_back(std::make_unique<Casper>());
    v.push_back(std::make_unique<Casper>());
    v.push_back(std::make_unique<Casper>());
    v.push_back(std::make_unique<Casper>());

    return v;
}

void letThemSpeak(const std::vector<std::unique_ptr<Individual>>& v)
{
    for (const std::unique_ptr<Individual>& p : v)
    {
        p->speak();
    }
}

int main()
{
    std::vector<std::unique_ptr<Individual>> v = createIndividuals();

    letThemSpeak(v);

    return 0;
}