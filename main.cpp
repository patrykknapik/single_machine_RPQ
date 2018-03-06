#include <iostream>
#include <vector>
#include "machine.h"
#include "task.h"

int main() {
    machine myMachine(2,5);
    std::vector<task *> tasks;

    tasks.push_back(new task(2,3,4));

    std::cout << myMachine << "\n";



    return 0;
}