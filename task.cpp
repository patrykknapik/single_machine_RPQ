//
// Created by Patryk Knapik on 06.03.2018.
//

#include "task.h"

std::ostream& operator<< (std::ostream& stream, const task& Task){
    stream << "Task ID: " << Task.getID() << "\n";
    stream << "RPQ: " << Task.getR() << "R, " << Task.getP() << "P, " << Task.getQ() <<"Q";
    return stream;
}