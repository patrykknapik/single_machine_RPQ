//
// Created by Patryk Knapik on 06.03.2018.
//

#ifndef SINGLE_MACHINE_RPQ_TASK_H
#define SINGLE_MACHINE_RPQ_TASK_H

#include <iostream>

class task {
private:
    unsigned int r, p, q, startime;
    int ID;

public:
    task(int newID, unsigned int newR = 1, unsigned int newP = 1, unsigned int newQ = 1) : ID(newID), r(newR),
                                                                                           p(newP), q(newQ) {}

    unsigned int &getR() {
        return r;
    }

    unsigned int &getP() {
        return p;
    }

    unsigned int &getQ() {
        return q;
    }

    int &getID() {
        return ID;
    }

    unsigned int &getStartTime() {
        return startime;
    }


    void setRPQ(unsigned int newR, unsigned int newP, unsigned int newQ) {
        r = newR;
        p = newP;
        q = newQ;
    }

    void setID(int newID) {
        ID = newID;
    };

    bool operator<(task &task1) {
        return ID < task1.getID();
    }

};

std::ostream &operator<<(std::ostream &stream, task &Task);

inline bool sortRcomp(task *task1, task *task2) {
    return ((task1->getR())<(task2->getR()));
}


#endif //SINGLE_MACHINE_RPQ_TASK_H
