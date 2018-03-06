#include <iostream>
#include "machine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    machine maszynka;
    std::cout << maszynka.getSpeed() << "\n";
    return 0;
}