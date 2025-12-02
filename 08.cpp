#include <iostream>
#include <cassert>
#include <string>
#include <optional>
#include <exception>
#include <new>
using namespace std::string_literals;

///////////////////////////////////////////////////////////////////////

class BadOptionalAccess : public std::exception {
public:
    const char* what() const noexcept override {
        return "Bad optional access";
    }
};

template<typename T>
class Optional {
private:
    union Storage {
        char empty;
        T value;
        
        Storage() : empty(0) {}
        ~Storage() {}
    };
    
    Storage storage;
    bool hasValueFlag;

public:
    Optional() : hasValueFlag(false) {}
    
    Optional(const T& val) : hasValueFlag(true) {
        new (&storage.value) T(val);
    }
    
    Optional(const Optional& other) : hasValueFlag(other.hasValueFlag) {
        if (hasValueFlag) {
            new (&storage.value) T(other.storage.value);
        }
    }
    
    template<typename U>
    Optional(const Optional<U>& other) : hasValueFlag(other.has_value()) {
        if (hasValueFlag) {
            new (&storage.value) T(*other);
        }
    }
    
    Optional& operator=(const Optional& other) {
        if (this != &other) {
            if (hasValueFlag) {
                if (other.hasValueFlag) {
                    storage.value = other.storage.value;
                } else {
                    storage.value.~T();
                    hasValueFlag = false;
                }
            } else {
                if (other.hasValueFlag) {
                    new (&storage.value) T(other.storage.value);
                    hasValueFlag = true;
                }
            }
        }
        return *this;
    }
    
    template<typename U>
    Optional& operator=(const Optional<U>& other) {
        if (hasValueFlag) {
            if (other.has_value()) {
                storage.value = *other;
            } else {
                storage.value.~T();
                hasValueFlag = false;
            }
        } else {
            if (other.has_value()) {
                new (&storage.value) T(*other);
                hasValueFlag = true;
            }
        }
        return *this;
    }
    
    bool has_value() const {
        return hasValueFlag;
    }
    
    T& operator*() {
        return storage.value;
    }
    
    const T& operator*() const {
        return storage.value;
    }
    
    T& value() {
        if (!hasValueFlag) {
            throw BadOptionalAccess();
        }
        return storage.value;
    }
    
    const T& value() const {
        if (!hasValueFlag) {
            throw BadOptionalAccess();
        }
        return storage.value;
    }
    
    explicit operator bool() const {
        return hasValueFlag;
    }
    
    void reset() {
        if (hasValueFlag) {
            storage.value.~T();
            hasValueFlag = false;
        }
    }
    
    T value_or(const T& default_val) const {
        if (hasValueFlag) {
            return storage.value;
        }
        return default_val;
    }
    
    ~Optional() {
        if (hasValueFlag) {
            storage.value.~T();
        }
    }
};

/////////////////////////////////////////////////////////////////


template<typename T>
using OptType = Optional<T>;
using OptExceptionType = BadOptionalAccess;


void testDefaultConstructor() 
{
    OptType<int> o;
    assert(!o.has_value());
    assert(!static_cast<bool>(o));
}

void testValueConstructor() 
{
    OptType<int> o(100);
    assert(o.has_value());
    assert(*o == 100);
    assert(o.value() == 100);
}

void testCopyConstructor() 
{
    OptType<int> o1(100);
    OptType<int> o2 = o1;

    assert(o2.has_value());
    assert(o2.value() == 100);
}

void testCopyConstructorEmpty() 
{
    OptType<int> o1;
    OptType<int> o2(o1);
    assert(!o2.has_value());
}

void testTemplateCopyConstructor() 
{
    OptType<int> oi(100);
    OptType<double> od(oi);

    assert(od.has_value());
    assert(*od == 100.0);
}

void testAssignment() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    o2 = o1;
    assert(o2.has_value());
    assert(*o2 == 100);
}

void testTemplateAssignment() 
{
    OptType<int> oi(100);
    OptType<double> od;

    od = oi;
    assert(od.has_value());
    assert(*od == 100.0);
}

void testSelfAssignment() 
{
    OptType<int> o(100);
    o = o; 
    assert(o.has_value());
    assert(o.value() == 100);
}

void testValueConstructorString() 
{
    OptType<std::string> o("Axolotl");
    assert(o.has_value());
    assert(*o == "Axolotl");
    assert(o.value() == "Axolotl");
}

void testCopyConstructorString() 
{
    OptType<std::string> o1("Axolotl");
    OptType<std::string> o2 = o1;

    assert(o2.has_value());
    assert(o2.value() == "Axolotl");
}

void testCopyConstructorEmptyString() 
{
    OptType<std::string> o1;
    OptType<std::string> o2(o1);
    assert(!o2.has_value());
}

void testAssignmentString() 
{
    OptType<std::string> o1("Axolotl");
    OptType<std::string> o2;

    o2 = o1;
    assert(o2.has_value());
    assert(*o2 == "Axolotl");
}

void testReset() 
{
    OptType<int> o(100);
    assert(o.has_value());

    o.reset();
    assert(!o.has_value());
}

void testValueOr() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    assert(o1.value_or(200) == 100);
    assert(o2.value_or(200) == 200);
}

void testBoolCast() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    if (!o1)
    {
        assert(false);
    }

    if (o2)
    {
        assert(false);
    }
}

void testThrowOnValue() 
{
    OptType<int> o;

    try 
    {
        o.value();
        assert(false);
    } 
    catch (const OptExceptionType&) {} 
    catch (...) {assert(false);}
}

void testConstOptTypeAccess() 
{
    const OptType<int> o1(100);
    assert(o1.has_value());
    assert(*o1 == 100);
    assert(o1.value() == 100);
    assert(o1.value_or(200) == 100);

    const OptType<int> o2;
    assert(!o2.has_value());
    assert(o2.value_or(200) == 200);

    try 
    {
        o2.value();
        assert(false);
    } 
    catch (const OptExceptionType&) {}
    catch (...) {assert(false);}
}

void testAlignment() 
{
    assert(alignof(int) == alignof(OptType<int>));
    assert(alignof(std::string) == alignof(OptType<std::string>));
}

struct NoDefault 
{
    int x;
    NoDefault(int v) : x(v) {}
    NoDefault() = delete;
};

void testNoDefaultConstructor() 
{
    OptType<NoDefault> o(NoDefault(100));
    assert(o.has_value());
    assert(o.value().x == 100);
}

struct Object 
{
    static int count;
    Object()
    {
        count += 1;
    }

    Object(const Object& other)
    {
        count += 1;
    }

    ~Object()
    {
        count -= 1;
    }
};

int Object::count {0};

void testCreationDestruction1() 
{
    Object::count = 0;

    OptType<Object> o;
    assert(Object::count == 0);
}

void testCreationDestruction2()
{
    Object::count = 0;

    OptType<Object> o(Object{});
    assert(Object::count == 1);

    o.reset();
    assert(Object::count == 0);
}

void testCreationDestruction3()
{
    Object::count = 0;

    OptType<Object> o(Object{});
    o = OptType<Object>{};
    assert(Object::count == 0);
}

void testCreationDestruction4()
{
    OptType<Object> o1(Object{});
    OptType<Object> o2 = o1;

    assert(Object::count == 2);
}

void testCreationDestruction5()
{
    OptType<Object> o(Object{});
    int before = Object::count;
    o = o;
    assert(Object::count == before);
}

int main()
{
    try
    {
        testDefaultConstructor();
        testValueConstructor();
        testCopyConstructor();
        testCopyConstructorEmpty();
        testTemplateCopyConstructor();
        testAssignment();
        testTemplateAssignment();
        testSelfAssignment();

        testValueConstructorString();
        testCopyConstructorString();
        testCopyConstructorEmptyString();
        testAssignmentString();

        testReset();
        testValueOr();
        testBoolCast();
        testThrowOnValue();
        testConstOptTypeAccess();
        testAlignment();
        testNoDefaultConstructor();
        testCreationDestruction1();
        testCreationDestruction2();
        testCreationDestruction3();
        testCreationDestruction4();
        testCreationDestruction5();
    }
    catch (...)
    {
        std::cerr << "Exception was thrown" << std::endl;
        std::exit(1);
    }

    std::cout << "Success. All tests are passed!" << std::endl;
}