#include <iostream>
#include <vector>
#include <sys/time.h>
#include <fstream>
#include <queue>
#include <list>
#include "task.h"

#define TASK_COUNT 8
#define MIN_TIME 1
#define MAX_TIME 20
//#define SHOW_PERMUTATIONS
#define GENERATE_PLOT
//#define GENRATE_TEST_DATA

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i--;
    }
    return f;
}

void schrageNlogN(std::vector<task *> &unorderedTasks);

void schrageN2(std::vector<task *> &unorderedTasks);

void generatePlot(std::string &fileName, std::vector<task *> &tasks);

int main() {
    timeval time_stamp_start, time_stamp_stop;
    double elapsed_time, bruteForceTime, sortRTime, schrageNlogNTime, schrageN2Time;
    std::vector<task *> tasks;
    std::vector<task *> queuedTasks;
    unsigned long int tasksPermutations = 0;
    unsigned int Cmax = 0, t = 0, Cmin = std::numeric_limits<unsigned int>::max(), schrageNlogN_Cmax, schrageN2_Cmax, bruteForce_Cmax, sortR_Cmax;
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
#ifdef SHOW_PERMUTATIONS
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
#endif

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
    bruteForce_Cmax = Cmin;

#ifdef GENERATE_PLOT
    std::string fileName("brute_force.svg");
    generatePlot(fileName, tasks);

#endif

    //sortR:
    Cmax = t = 0;
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
    sortR_Cmax = Cmax;

#ifdef GENERATE_PLOT
    fileName = "sortR.svg";
    generatePlot(fileName, tasks);

#endif

    //schrage NlogN:
    Cmax = t = 0;
    std::cout << "Schrage NlogN algorithm:\n";
    std::cout << "\nSugested tasks queue: ";
    gettimeofday(&time_stamp_start, NULL);
    schrageNlogN(tasks);
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
    schrageNlogNTime = elapsed_time;
    schrageNlogN_Cmax = Cmax;

#ifdef GENERATE_PLOT
    fileName = "schrageNlogN.svg";
    generatePlot(fileName, tasks);

#endif

    //schrage N2:
    Cmax = t = 0;
    std::cout << "Schrage N2 algorithm:\n";
    std::cout << "\nSugested tasks queue: ";
    gettimeofday(&time_stamp_start, NULL);
    schrageN2(tasks);
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
    schrageN2Time = elapsed_time;
    schrageN2_Cmax = Cmax;

#ifdef GENERATE_PLOT
    fileName = "schrageN2.svg";
    generatePlot(fileName, tasks);

#endif

#ifdef GENRATE_TEST_DATA
        std::ofstream file;
        file.open("test_data.log",std::ofstream::app);
        file << "|" << TASK_COUNT << "|" << sortRTime << " ms|"<< sortR_Cmax;
        file<< "|" << bruteForceTime <<" ms|"<< bruteForce_Cmax;
        file<< "|" << schrageNlogNTime <<" ms|"<< schrageNlogN_Cmax;
        file<< "|" << schrageN2Time <<" ms|"<< schrageN2_Cmax << "|\n";
        file.close();
#endif

    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
}

void schrageNlogN(std::vector<task *> &Tasks) {
    auto compQ = [](const task *first, const task *second) {
        return first->getQ() < second->getQ();
    };

    std::priority_queue<task *, std::vector<task *>, decltype(compQ)> readyToOrder(compQ);
    std::vector<task *> orderedTasks, unorderedTasks = Tasks;

    unsigned t = 0;
    std::sort(unorderedTasks.begin(), unorderedTasks.end(), sortRcomp);

    t = unorderedTasks.at(0)->getR();

    while ((!unorderedTasks.empty()) || (!readyToOrder.empty())) {

        while (!unorderedTasks.empty() && unorderedTasks.at(0)->getR() <= t) {
            readyToOrder.push(unorderedTasks.at(0));
            unorderedTasks.erase(unorderedTasks.begin());
        }

        if (readyToOrder.empty()) {
            t = unorderedTasks.at(0)->getR();
        } else {
            orderedTasks.push_back(readyToOrder.top());
            readyToOrder.pop();
            t += orderedTasks.back()->getP();
        }
    }

    Tasks = orderedTasks;
}

void schrageN2(std::vector<task *> &Tasks) {
    std::vector<task *> readyToOrder;
    std::vector<task *> orderedTasks, unorderedTasks = Tasks;
    unsigned i = 0, min = std::numeric_limits<unsigned int>::max(), tmpMin;

    unsigned t = 0;
    std::sort(unorderedTasks.begin(), unorderedTasks.end(), sortRcomp);

    t = unorderedTasks.at(0)->getR();

    while ((!unorderedTasks.empty()) || (!readyToOrder.empty())) {

        while (!unorderedTasks.empty() && unorderedTasks.at(0)->getR() <= t) {
            readyToOrder.push_back(unorderedTasks.at(0));
            unorderedTasks.erase(unorderedTasks.begin());
        }

        if (readyToOrder.empty()) {
            t = unorderedTasks.at(0)->getR();
        } else {
            std::sort(readyToOrder.begin(), readyToOrder.end(),
                      [](const task *first, const task *second) { return first->getQ() > second->getQ(); });

            orderedTasks.push_back(readyToOrder.at(0));
            readyToOrder.erase(readyToOrder.begin());
            t += orderedTasks.back()->getP();
        }
    }

    Tasks = orderedTasks;
}

void generatePlot(std::string &fileName, std::vector<task *> &tasks) {
    std::ofstream file;
    unsigned int Cmax = 0, t = 0, Rtime = 0, Ptime = 0;
    std::vector<std::string> colors;
    colors.push_back("0xFF0000");
    colors.push_back("0xFFE400");
    colors.push_back("0x71FF00");
    colors.push_back("0x00FFE1");
    colors.push_back("0x0096FF");
    colors.push_back("0x000FFF");
    colors.push_back("0xBB00FF");
    colors.push_back("0xFF00BC");
    colors.push_back("0xFFAC00");
    colors.push_back("0x000000");

    auto colorIter = colors.begin();

    file.open("tmp.gpl");
    file << "set terminal svg size 1000,750\n";
    file << "set output '" << fileName << "'\n";
    file << "$DATA << EOD\n";

    for (auto Task : tasks) {

        Ptime = std::max(Task->getR(), Ptime);
        file << Ptime << " -2 ";
        Rtime = Ptime - Task->getR();
        Ptime += Task->getP();
        file << Task->getP() << " 0 " << (*colorIter) << ' ' << Task->getID() << '\n';

        file << Rtime << " -1 ";
        file << Task->getR() << " 0 " << (*colorIter) << ' ' << Task->getID() << '\n';

        file << Ptime << " -3 ";
        file << Task->getQ() << " 0 " << (*colorIter) << ' ' << Task->getID() << '\n';

        t = std::max(Task->getR(), t) + Task->getP();
        Cmax = std::max(Cmax, (t + Task->getQ()));

        if (++colorIter == colors.end())
            colorIter = colors.begin();
    }
    file << "EOD\n";
    file << "unset key\n";
    file << "set xlabel \"time (total makespan: " << Cmax << ")\"\n";
    file << "set yrange [-4:0]\n";
    file << "set ytics (\"\" 0,\"R\" -1, \"P\" -2, \"Q\" -3, \"\" -4)\n";
    file << "plot $DATA using 1:2:3:4:5 with vectors lw 3 lc rgb variable, $DATA using 1:2:6 with labels offset 1,1\n";
    file << "reset\n";
    file.close();
    system("gnuplot tmp.gpl");
}

