//
// Created by Patryk Knapik on 06.03.2018.
//

#ifndef SINGLE_MACHINE_RPQ_MACHINE_H
#define SINGLE_MACHINE_RPQ_MACHINE_H


class machine {
private:
    unsigned int speed;

public:

    machine() : speed(1){};

    unsigned int getSpeed(){
        return speed;
    }

    void setSpeed(unsigned int newSpeed){
        speed = newSpeed;
    };

};



#endif //SINGLE_MACHINE_RPQ_MACHINE_H
