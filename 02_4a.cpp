#include <iostream>
#include <vector>

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

std::vector<Individual*> createIndividuals()
{
    std::vector<Individual*> v;

    v.push_back(new Alice);
    v.push_back(new Alice);
    v.push_back(new Alice);

    v.push_back(new Bob);
    v.push_back(new Bob);

    v.push_back(new Casper);
    v.push_back(new Casper);
    v.push_back(new Casper);
    v.push_back(new Casper);

    return v;
}

void letThemSpeak(const std::vector<Individual*>& v)
{
    for (Individual* p : v)
    {
        p->speak();
    }
}

void deleteIndividuals(std::vector<Individual*>& v)
{
    for (Individual* p : v)
    {
        delete p;
    }
    v.clear();
}

int identification(Individual* p)
{
    if (dynamic_cast<Casper*>(p) != nullptr)
    {
        return 2;
    }

    if (dynamic_cast<Bob*>(p) != nullptr)
    {
        return 1;
    }

    return 0;
}

int main()
{
    std::vector<Individual*> v = createIndividuals();

    letThemSpeak(v);

    for (Individual* p : v)
    {
        std::cout << identification(p) << std::endl;
    }

    deleteIndividuals(v);

    return 0;
}