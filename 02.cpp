#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void rev(std::vector<std::string>& a)
{
    std::reverse(a.begin(), a.end());

    std::for_each(a.begin(), a.end(), [](std::string& s)
    {
        std::reverse(s.begin(), s.end());
    });
}

void print(const std::vector<std::string>& a)
{
    bool f = true;

    std::cout << "{";

    std::for_each(a.begin(), a.end(), [&](const std::string& s)
    {
        if (!f)
        {
            std::cout << ", ";
        }

        std::cout << "\"" << s << "\"";
        f = false;
    });

    std::cout << "}";
}

int main()
{
    std::vector<std::string> a{"cat", "dog", "mouse", "elephant"};
    std::vector<std::string> b{"a", "bc"};

    rev(a);
    print(a);
    std::cout << std::endl;

    rev(b);
    print(b);
    std::cout << std::endl;

    return 0;
}