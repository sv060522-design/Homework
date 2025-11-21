#include <iostream>
#include <string>
#include <vector>

int main() {
    int* pInt = new int(123);
    std::cout << *pInt << std::endl;
    delete pInt;

    std::string* pString = new std::string("Cats and Dogs");
    std::cout << *pString << std::endl;
    delete pString;

    int* pArray = new int[5]{10, 20, 30, 40, 50};
    for (int i = 0; i < 5; ++i) {
        std::cout << pArray[i] << " ";
    }
    std::cout << std::endl;
    delete[] pArray;

    std::vector<int>* pVector = new std::vector<int>{10, 20, 30, 40, 50};
    for (int value : *pVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    delete pVector;

    std::string* pStrArray = new std::string[3]{"Cat", "Dog", "Mouse"};
    for (int i = 0; i < 3; ++i) {
        std::cout << pStrArray[i] << " ";
    }
    std::cout << std::endl;
    delete[] pStrArray;

    return 0;
}