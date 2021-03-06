#include <iostream>
#include <vector>
#include <sys/time.h>
#include <fstream>
#include <queue>
#include <list>
#include "task.h"

#define TASK_COUNT 5
#define MIN_TIME 1
#define MAX_TIME 30
#define SHOW_PERMUTATIONS
//#define GENERATE_PLOT
//#define GENRATE_TEST_DATA
#define USE_BRUTE_FORCE

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i--;
    }
    return f;
}

void schrageNlogN(std::vector<task *> &unorderedTasks);

void schrageN2(std::vector<task *> &unorderedTasks);

void schragePMTN(std::vector<task *> &Tasks);

unsigned carlier(std::vector<task *> &Tasks, unsigned &UB);

void getABC(int &a, int &b, int &c, std::vector<task *> &Tasks, std::vector<int> pi, std::vector<int> cpi);

unsigned getCmax(std::vector<task *> Tasks);

void generatePlot(std::string &fileName, std::vector<task *> &tasks);

int schrage(std::vector<task *> Tasks, std::vector<int> &pi, std::vector<int> &c);

int main() {
    timeval time_stamp_start, time_stamp_stop;
    double elapsed_time, bruteForceTime, sortRTime, schrageNlogNTime, schrageN2Time, calierTime;
    std::vector<task *> tasks;
    std::vector<task *> queuedTasks;
    unsigned long int tasksPermutations = 0;
    unsigned int Cmax = 0, t = 0, Cmin = std::numeric_limits<unsigned int>::max(), schrageNlogN_Cmax, schrageN2_Cmax, bruteForce_Cmax, sortR_Cmax, calier_Cmax;
    std::srand(std::time(nullptr));

    for (unsigned i = 0; i <= TASK_COUNT; ++i) {
        tasks.push_back(new task(i, (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME));
    }

    std::cout << "Tasks parameters:\n";
    for (task *Task : tasks) {
        std::cout << *Task << "\n";
    }


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

#ifdef USE_BRUTE_FORCE
    //brute force:
    std::cout << "\n\nBrute force algorithm:\n";
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

#endif

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
    //schrageNlogN(tasks);
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
    //schrageN2(tasks);
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
    std::sort(tasks.begin(), tasks.end(), [](task *a, task *b) -> bool { return a->getID() < b->getID(); });
    std::cout << "Tasks order reset before SchragePMTN: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }
    schragePMTN(tasks);
    std::cout << "\nSchragePMTN cmax = " << getCmax(tasks) << ".\n";
    std::cout << "Task order: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << '\n';

//    //Calier:
//    Cmax = t = 0;
//    std::cout << "Calier algorithm:\n";
//    std::cout << "SchragePMTN cmax = " << schragePMTN(tasks) << ".\n";
//    std::cout << "\nSugested tasks queue: ";
//    gettimeofday(&time_stamp_start, NULL);
//    unsigned UB = getCmax(tasks);
//    //carlier(tasks, UB);
//    for (task *Task : tasks) {
//        std::cout << Task->getID() << ' ';
//        t = std::max(Task->getR(), t) + Task->getP();
//        Cmax = std::max(Cmax, (t + Task->getQ()));
//    }
//    std::cout << "; C = " << Cmax << '\n';
//    gettimeofday(&time_stamp_stop, NULL);
//
//    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
//    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
//    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";
//    calierTime = elapsed_time;
//    calier_Cmax = Cmax;

#ifdef GENERATE_PLOT
    fileName = "carlier.svg";
    generatePlot(fileName, tasks);

#endif

#ifdef GENRATE_TEST_DATA
#ifdef USE_BRUTE_FORCE
    std::ofstream file;
    file.open("test_data.log",std::ofstream::app);
    file << "|" << TASK_COUNT << "|" << sortRTime << "|"<< sortR_Cmax;
    file<< "|" << bruteForceTime <<"|"<< bruteForce_Cmax;
    file<< "|" << schrageNlogNTime <<"|"<< schrageNlogN_Cmax;
    file<< "|" << schrageN2Time <<"|"<< schrageN2_Cmax << "|\n";
    file.close();
#else
std::ofstream file;
    file.open("test_data.log",std::ofstream::app);
    file << "|" << TASK_COUNT << "|" << sortRTime << "|"<< sortR_Cmax;
    file<< "| | ";
    file<< "|" << schrageNlogNTime <<"|"<< schrageNlogN_Cmax;
    file<< "|" << schrageN2Time <<"|"<< schrageN2_Cmax << "|\n";
    file.close();
#endif
#endif

    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
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
                      [](task *first, task *second) { return first->getQ() > second->getQ(); });

            orderedTasks.push_back(readyToOrder.at(0));
            readyToOrder.erase(readyToOrder.begin());
            t += orderedTasks.back()->getP();
        }
    }

    Tasks = orderedTasks;
}

void schrageNlogN(std::vector<task *> &Tasks) {
    auto compQ = [](task *first, task *second) {
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

void schragePMTN(std::vector<task *> &Tasks) {

    std::sort(Tasks.begin(), Tasks.end(), sortRcomp);
    auto unorderedTasks = Tasks;
    std::vector<task *> orderedTasks;
    task *interruptedTask = nullptr;
    auto compQ = [](task *a, task *b) {
        return a->getQ() < b->getQ();
    };
    std::priority_queue<task *, std::vector<task *>, decltype(compQ)> readyToOrder(compQ);
    for (int time = unorderedTasks.at(0)->getR(); (!readyToOrder.empty() || !unorderedTasks.empty()); ++time) {
        while (!unorderedTasks.empty() && unorderedTasks.at(0)->getR() <= time) {
            readyToOrder.push(unorderedTasks.at(0));
            unorderedTasks.erase(unorderedTasks.begin(), unorderedTasks.begin() + 1);
        }
        if (!readyToOrder.empty()) {
            if (orderedTasks.empty() || time >= orderedTasks.back()->getStartTime() + orderedTasks.back()->getP()) {
                orderedTasks.push_back(readyToOrder.top());
                readyToOrder.pop();
                orderedTasks.back()->getStartTime() = time;
            }
            if (!readyToOrder.empty() && !orderedTasks.empty() &&
                orderedTasks.back()->getQ() < readyToOrder.top()->getQ()) { //przerwanie
                int dur = orderedTasks.back()->getP();
                orderedTasks.back()->getP() = readyToOrder.top()->getR() - orderedTasks.back()->getStartTime();

                interruptedTask = new task(-1, orderedTasks.back()->getR(), dur - orderedTasks.back()->getP(),
                                           orderedTasks.back()->getQ());
                readyToOrder.push(interruptedTask);
            }
        }
    }
    Tasks = orderedTasks;
}

unsigned carlier(std::vector<task *> &Tasks, unsigned &UB) {
////cpi - czasy zakonczen
//    std::vector<int> pi_opt,pi, cpi;
//    // 1. Podstawienie U = schrage(n,R,P,Q,pi)
//    int U = schrage(Tasks,pi,cpi);
//    // 2. Jezeli U<UB to UB=U, π*=π,
//    if( U < UB ){
//        UB = U;
//        pi_opt = pi;
//    }
//    //for(unsigned int i = 0; i < pi_opt.size();i++)
//    //    cout << pi_opt[i] << ": "<<Tasks[pi_opt[i]].r<< " "<<Tasks[pi_opt[i]].p<<" "<< Tasks[pi_opt[i]].q<<" / " << cpi[i] << endl;
//    // 3. Blok (a,b) i zadanie referencyjne c
//    int a,b,c;
//    getABC(a,b,c,Tasks,pi,cpi);
//    //cout << "a: "<< a <<" b: "<< b << " c: "<< c <<endl;
//    // 4. Jezeli c nie istnieje to powrót
//    if( c < 0 ) return UB;
//    // 5. Wyznacz r', q', p'
//    int r_prim=std::numeric_limits<unsigned int>::max(), q_prim=-1, p_prim=0;
//    for(int j=c+1;j<=b;j++){
//        r_prim = std::min(r_prim, (int)Tasks[pi[j]]->getR());
//        q_prim = std::max(q_prim, (int)Tasks[pi[j]]->getQ());
//        p_prim += Tasks[pi[j]]->getP();
//    }
//    // 6. Podstaw r_old
//    int r_old = Tasks[pi[c]]->getR();
//    Tasks[pi[c]]->getR() = std::max((int)Tasks[pi[c]]->getR(), r_prim+p_prim);
//    // 7. LB
//    int LB = schragePMTN(Tasks);
//    // 8. Rekurencyjny Calier
//    if(LB<UB)
//        carlier(Tasks,UB);
//    Tasks[pi[c]]->getR() = r_old;
//    // 11. Podstaw q_old
//    int q_old = Tasks[pi[c]]->getQ();
//    Tasks[pi[c]]->getQ() = std::max((int)Tasks[pi[c]]->getQ(), q_prim+p_prim);
//    LB = schragePMTN(Tasks);
//    if(LB<UB)
//        carlier(Tasks,UB);
//    Tasks[pi[c]]->getQ() = q_old;
//    return UB;
//    //return INT_MAX;
    return 0;

}

void getABC(int &a, int &b, int &c, std::vector<task *> &Tasks, std::vector<int> pi, std::vector<int> cpi) {
    a = -1;
    b = -1;
    c = -1;
    //wyłuskanie Cmaxa
    int Cmax = 0;
    for (unsigned int i = 0; i < cpi.size(); i++)
        Cmax = (cpi[i] + Tasks[pi[i]]->getQ() > Cmax) ? cpi[i] + Tasks[pi[i]]->getQ() : Cmax;
    //    wyznaczanie b
    for (unsigned int j = 0; j < pi.size(); j++)
        if (Cmax == cpi[j] + Tasks[pi[j]]->getQ())
            b = j;
    //    wyznaczanie a
    for (int j = pi.size() - 1; j >= 0; j--) {
        int sum = 0;
        for (int s = j; s <= b; s++)
            sum += Tasks[pi[s]]->getP();
        if (Cmax == Tasks[pi[j]]->getR() + sum + Tasks[pi[b]]->getQ())
            a = j;
    }
    //    wyznaczanie c
    for (int j = a; j <= b && j != -1; j++)
        if (Tasks[pi[j]]->getQ() < Tasks[pi[b]]->getQ())
            c = j;
}

int schrage(std::vector<task *> Tasks, std::vector<int> &pi, std::vector<int> &c) {
    //wypelnienie kolejki zadan r
    auto compQ = [](task *first, task *second) {
        return first->getQ() < second->getQ();
    };

    auto compR = [](task *first, task *second) {
        return first->getR() < second->getR();
    };

    std::priority_queue<task *, std::vector<task *>, decltype(compQ)> tasks_q(compQ);
    std::priority_queue<task *, std::vector<task *>, decltype(compR)> tasks_r(compR);

    for (unsigned int i = 0; i < Tasks.size(); i++)
        tasks_r.push(Tasks[i]);
    //maksymalny czas wykonania
    int Cmax = 0;
    //czas bieżący
    int time = 0;
    //zadanie obecnie znajdujace sie na maszynie
    task *l = new task(-1, 0, 0, std::numeric_limits<unsigned int>::max());
    //zadanie ktore w kazdym kroku jest dodawane do zadan gotowych do realizacji
    task *e;
    //Dopóki nie zrealizowano wszystkich zadań
    while (!tasks_q.empty() || !tasks_r.empty()) {
        //Dodawanie zadań do kolejki zadan gotowych dopoki sa zadania nieuszeregowane
        while (!tasks_r.empty() && (tasks_r.top()->getR() <= time)) {
            //zdjecie zadania z kolejki zadan nieuszeregowanych
            e = tasks_r.top();
            tasks_r.pop();
            //dodanie zadania do kolejki zadan gotowych
            tasks_q.push(e);
        }
        //Gdy nie ma zadan gotowych nastepuje przejscie do pierwszego dostepnego zadania
        if (tasks_q.empty()) {
            time = tasks_r.top()->getR();
        } else {
            //zdjecie zadania z listy zadan gotowych i polozenie go na maszyne
            l = tasks_q.top();
            tasks_q.pop();
            //printf("%d: %d %d %d\n",l.pi,l.r,l.p,l.q);
            //l = e;
            //przesuniecie w czasie i aktualizacja Cmax
            time += l->getP();
            pi.push_back(l->getID());
            c.push_back(time);
            Cmax = std::max(Cmax, (int) (time + l->getQ()));
        }
    }
    return Cmax;
}


unsigned getCmax(std::vector<task *> Tasks) {
    unsigned t = 0, Cmax = 0;
    for (task *Task : Tasks) {
        t = std::max(Task->getR(), t) + Task->getP();
        Cmax = std::max(Cmax, (t + Task->getQ()));
    }
    return Cmax;
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

