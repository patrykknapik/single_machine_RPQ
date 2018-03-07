//
// Created by Patryk Knapik on 06.03.2018.
//

#ifndef SINGLE_MACHINE_RPQ_TASK_H
#define SINGLE_MACHINE_RPQ_TASK_H

#include <iostream>

class task {
private:
    unsigned int r, p, q, ID;

public:
    task(unsigned int newID, unsigned int newR = 1, unsigned int newP = 1, unsigned int newQ = 1) : ID(newID), r(newR),
                                                                                                    p(newP), q(newQ) {}

    unsigned int getR() const{
        return r;
    }

    unsigned int getP() const{
        return p;
    }

    unsigned int getQ() const{
        return q;
    }

    unsigned int getID() const{
        return ID;
    }

    void setRPQ(unsigned int newR, unsigned int newP, unsigned int newQ) {
        r = newR;
        p = newP;
        q = newQ;
    }

    void setID(unsigned int newID) {
        ID = newID;
    };

    bool operator< (const task &task1) const{
        return ID<task1.getID();
    }

};

std::ostream& operator<< (std::ostream& stream, const task& Task);


#endif //SINGLE_MACHINE_RPQ_TASK_H
