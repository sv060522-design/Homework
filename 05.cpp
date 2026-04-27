#include <algorithm>
#include <iostream>
#include <string>

void moveSpaces(std::string& s)
{
    std::stable_partition(s.begin(), s.end(), [](char c) {
        return c != ' ';
    });
}

int main()
{
    std::string a = "cats and dogs";
    std::string b = " cats  and  dogs"; // Тут добавил пробелы, а то в задании они одинаковые, а выводы разные, что очень странно, скорее всего в задании опечатка.

    moveSpaces(a);
    moveSpaces(b);

    std::cout << '"' << a << '"' << std::endl;
    std::cout << '"' << b << '"' << std::endl;

    return 0;
}