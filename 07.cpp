#include <iostream>
#include <string>
#include <cstdlib>

template<typename T>
class Manager {
private:
    T* object;

public:
    Manager() : object(nullptr) {}

    void allocate() {
        object = static_cast<T*>(std::malloc(sizeof(T)));
    }

    void construct(const T& t) {
        new (object) T(t);
    }

    void destruct() {
        object->~T();
    }

    void deallocate() {
        std::free(object);
        object = nullptr;
    }

    T& get() {
        return *object;
    }
};

using namespace std::string_literals;

int main()
{
    Manager<std::string> a;
    a.allocate();
    a.construct("Cats and dogs"s);
    a.get() += " and elephant";
    std::cout << a.get() << std::endl;
    a.destruct();
    a.construct("Sapere Aude"s);
    std::cout << a.get() << std::endl;
    a.destruct();
    a.deallocate();
}