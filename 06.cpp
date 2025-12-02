#include <iostream>

template<typename T, int MOD>
class Modular {
private:
    T value;

public:
    Modular(T val = 0) : value(val % MOD) {
        if (value < 0) value += MOD;
    }

    Modular(const Modular& other) : value(other.value) {}

    Modular& operator=(const Modular& other) {
        value = other.value;
        return *this;
    }

    Modular operator+(const Modular& other) const {
        return Modular((value + other.value) % MOD);
    }

    Modular operator+(T other) const {
        return Modular((value + other) % MOD);
    }

    Modular operator-(const Modular& other) const {
        return Modular((value - other.value + MOD) % MOD);
    }

    Modular operator-(T other) const {
        return Modular((value - other + MOD) % MOD);
    }

    Modular operator*(const Modular& other) const {
        return Modular((value * other.value) % MOD);
    }

    Modular operator*(T other) const {
        return Modular((value * other) % MOD);
    }

    Modular operator-() const {
        return Modular((-value + MOD) % MOD);
    }

    template<typename U, int MOD2>
    Modular(const Modular<U, MOD2>& other) : value(other.getValue() % MOD) {
        if (value < 0) value += MOD;
    }

    friend std::ostream& operator<<(std::ostream& os, const Modular& m) {
        os << m.value;
        return os;
    }

    T getValue() const {
        return value;
    }
};

int main()
{
    Modular<int, 7> a(10);
    std::cout << a << std::endl;
    a = (a + 8) * 4;
    std::cout << a << std::endl;

    Modular<int, 7> b(a);
    b = b + 2;
    a = a - b;
    std::cout << a << std::endl;

    Modular<short, 3> c(a);
    std::cout << c << std::endl;
}