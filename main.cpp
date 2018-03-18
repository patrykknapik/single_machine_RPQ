#include <iostream>
#include <vector>
#include <sys/time.h>
#include <fstream>
#include "task.h"

#define TASK_COUNT 13
#define MIN_TIME 1
#define MAX_TIME 20
#define SHOW_PERMUTATIONS false
#define GENRATE_TEST_DATA true

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i;
        --i;
    }
    return f;
}

int main() {
    timeval time_stamp_start, time_stamp_stop;
    double elapsed_time, bruteForceTime, sortRTime;
    std::vector<task *> tasks;
    std::vector<task *> queuedTasks;
    unsigned long int tasksPermutations = 0;
    unsigned int Cmax = 0, t = 0, Cmin = std::numeric_limits<unsigned int>::max();
    std::srand(std::time(nullptr));

    for (unsigned i = 1; i <= TASK_COUNT; ++i) {
        tasks.push_back(new task(i, (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME));
    }

    std::cout << "Tasks parameters:\n";
    for (task *Task : tasks) {
        std::cout << *Task << "\n";
    }

    //brute force:
    std::cout << "\n\nBrute force algorithm:\n";
    if(SHOW_PERMUTATIONS) {
        tasksPermutations = factorial(tasks.size());
        std::cout << "\nPermutations(" << tasksPermutations << "):\n";

        for (; tasksPermutations != 0; --tasksPermutations) {
            std::next_permutation(tasks.begin(), tasks.end());

            for (task *Task : tasks) {
                std::cout << Task->getID() << ' ';
                t = std::max(Task->getR(), t) + Task->getP();
                Cmax = std::max(Cmax, (t + Task->getQ()));
            }
            std::cout << "; C = " << Cmax << '\n';

            if (Cmax < Cmin) {
                Cmin = Cmax;
                queuedTasks = tasks;
            }

            Cmax = 0;
            t = 0;
        }
    }

    gettimeofday(&time_stamp_start, NULL);
    tasksPermutations = factorial(tasks.size());
    for (; tasksPermutations != 0; --tasksPermutations) {
        std::next_permutation(tasks.begin(), tasks.end());

        for (task *Task : tasks) {
            t = std::max(Task->getR(), t) + Task->getP();
            Cmax = std::max(Cmax, (t + Task->getQ()));
        }

        if (Cmax < Cmin) {
            Cmin = Cmax;
            queuedTasks = tasks;
        }

        Cmax = 0;
        t = 0;
    }
    gettimeofday(&time_stamp_stop, NULL);

    std::cout << "\n\nSugested tasks queue: ";
    for (task *Task : queuedTasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << Cmin << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";
    bruteForceTime = elapsed_time;

    //sortR:
    std::cout << "SortR algorithm:\n";
    std::cout << "\nSugested tasks queue: ";
    gettimeofday(&time_stamp_start, NULL);
    std::sort(tasks.begin(),tasks.end(),sortRcomp);
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
        t = std::max(Task->getR(), t) + Task->getP();
        Cmax = std::max(Cmax, (t + Task->getQ()));
    }
    std::cout << "; C = " << Cmax << '\n';
    gettimeofday(&time_stamp_stop, NULL);

    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";
    sortRTime = elapsed_time;

    if(GENRATE_TEST_DATA){
        std::ofstream file;
        file.open("test_data.log",std::ofstream::app);
        file << "|" << TASK_COUNT << "|" << sortRTime << " ms|"<< Cmax;
        file<< "|" << bruteForceTime <<" ms|"<< Cmin << "|\n";
        file.close();
    }

    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
}