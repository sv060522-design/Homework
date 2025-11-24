#include <iostream>

class RestrictWrapper {
    int& value;
    const int minValue;
    const int maxValue;
    int getCounter = 0;
    int setCounter = 0;

public:
    RestrictWrapper(int& val, int min, int max)
        : value(val), minValue(min), maxValue(max) {}

    int get() {
        getCounter++;
        return value;
    }

    void set(int newValue) {
        setCounter++;
        if (newValue < minValue) {
            value = minValue;
        } else if (newValue > maxValue) {
            value = maxValue;
        } else {
            value = newValue;
        }
    }

    int getCount() const {
        return getCounter;
    }

    int setCount() const {
        return setCounter;
    }
};

int main() {
    int x = 100;
    RestrictWrapper v(x, 0, 300);
    std::cout << v.get() << std::endl;
    v.set(-200);
    std::cout << v.get() << std::endl;
    v.set(300);
    v.set(400);
    v.set(500);
    std::cout << v.get() << std::endl;

    std::cout << v.getCount() << std::endl;
    std::cout << v.setCount() << std::endl;

    return 0;
}