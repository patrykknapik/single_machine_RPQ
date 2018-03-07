#include <iostream>
#include <vector>
#include "machine.h"
#include "task.h"

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i;
        --i;
    }
    return f;
}

int main() {
    std::vector<task *> tasks;
    std::vector<task *> queuedTasks;
    unsigned long int tasksPermutations = 0;
    unsigned int Cmax = 0, t = 0, Cmin = std::numeric_limits<unsigned int>::max();

    tasks.push_back(new task(1, 7, 3, 5));
    tasks.push_back(new task(2, 1, 8, 2));
    tasks.push_back(new task(3, 3, 5, 5));
    tasks.push_back(new task(4, 2, 6, 1));

    std::cout << "Tasks parameters:\n";
    for (task *Task : tasks) {
        std::cout << *Task << "\n";
    }

    tasksPermutations = factorial(tasks.size());
    std::cout << "\nPermutations(" << tasksPermutations << "):\n";

    for (; tasksPermutations != 0; --tasksPermutations) {
        std::next_permutation(tasks.begin(), tasks.end());

        for (task *Task : tasks) {
            std::cout << Task->getID() << ' ';
            t = std::max(Task->getR(), t) + Task->getP();
            Cmax = std::max(Cmax, (t + Task->getQ()));
        }
        std::cout << "; Cmax = " << Cmax << '\n';

        if (Cmax < Cmin) {
            Cmin = Cmax;
            queuedTasks = tasks;
        }

        Cmax = 0;
        t = 0;
    }

    std::cout << "\n\nSugested tasks queue: ";
    for (task *Task : queuedTasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << Cmin << '\n';

    return 0;
}