#include <iostream>
#include <string>

template<typename T>
T triple(const T& x)
{
    return 3 * x;
}

template<>
std::string triple<std::string>(const std::string& x)
{
    std::string result;
    for (int i = 0; i < 3; ++i) {
        result += x;
    }
    return result;
}

int main()
{
    int a = 10;
    std::cout << triple(a) << std::endl;

    std::string b = "Cat";
    std::cout << triple(b) << std::endl;
}
// Если одновременно реализованы и перегрузка, и специализация, то компилятор выберет перегрузку потому-что она
// обрабатывается на этапе разрешения перегрузок, который происходит раньше, чем выбор специализации шаблона.
