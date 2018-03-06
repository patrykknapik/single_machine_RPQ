//
// Created by Patryk Knapik on 06.03.2018.
//

#ifndef SINGLE_MACHINE_RPQ_MACHINE_H
#define SINGLE_MACHINE_RPQ_MACHINE_H

#include <iostream>

class machine {
private:
    unsigned int speed, ID;

public:

    machine(unsigned int newID, unsigned int newSpeed = 1) : ID(newID), speed(newSpeed) {};

    unsigned int getSpeed() const{
        return speed;
    }

    unsigned int getID() const{
        return ID;
    }

    void setSpeed(unsigned int newSpeed) {
        speed = newSpeed;
    };

    void setID(unsigned int newID) {
        ID = newID;
    };
};

std::ostream& operator<< (std::ostream& stream, const machine& Machine);


#endif //SINGLE_MACHINE_RPQ_MACHINE_H
