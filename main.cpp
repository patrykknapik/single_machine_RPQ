#include <iostream>
#include <vector>
#include "machine.h"
#include "task.h"

unsigned long int factorial(unsigned long int i){
    unsigned long int f = 1;
    while (i != 1){
        f *= i;
        --i;
    }
    return f;
}

int main() {
    machine myMachine(1,5);
    std::vector<task *> tasks;
    unsigned long int tasksPermutations = 0;


    tasks.push_back(new task(1,5,6,2));
    tasks.push_back(new task(2,7,3,67));
    tasks.push_back(new task(3,3,5,63));
    //tasks.push_back(new task(4,2,6,86));

    std::cout << "Tasks parameters:\n";
    for(task * Task : tasks){
        std::cout << *Task << "\n";
    }

    std::cout << "\nMachine parameters:\n";
    std::cout << myMachine << "\n";

    tasksPermutations = factorial(tasks.size());
    std::cout << "\nPermutations(" << tasksPermutations << "):\n";

    for(; tasksPermutations != 0; --tasksPermutations){
        std::next_permutation(tasks.begin(),tasks.end());
        for(task * Task : tasks){
            std::cout << Task->getID() << ' ';
        }
        std::cout << '\n';
        //TODO: brute force algorithm
    }



    return 0;
}