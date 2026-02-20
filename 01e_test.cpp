#include <iostream>
#include <dlfcn.h>
#include <thread>
#include <chrono>
#include <vector>

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(2));

    void* handle = dlopen("./libmiptlib.dll", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        return 1;
    }

    using add_func = double(*)(double, double);
    using power_func = double(*)(double, int);
    using circleArea_func = double(*)(double);
    using mean_func = double(*)(const std::vector<double>&);

    add_func add = (add_func)dlsym(handle, "_ZN7miptlib3addEdd");
    power_func power = (power_func)dlsym(handle, "_ZN7miptlib5powerEdi");
    circleArea_func circleArea = (circleArea_func)dlsym(handle, "_ZN7miptlib10circleAreaEd");
    mean_func mean = (mean_func)dlsym(handle, "_ZN7miptlib4meanERKSt6vectorIdSaIdEE");

    if (!add || !power || !circleArea || !mean) {
        std::cerr << "Cannot find symbols: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    std::cout << add(3, 4) << std::endl;
    std::cout << power(2, 5) << std::endl;
    std::cout << circleArea(5) << std::endl;

    std::vector<double> data = {1, 2, 3, 4, 5};
    std::cout << mean(data) << std::endl;

    dlclose(handle);
    return 0;
}