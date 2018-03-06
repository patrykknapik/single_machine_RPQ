//
// Created by Patryk Knapik on 06.03.2018.
//

#include "machine.h"

std::ostream& operator<< (std::ostream& stream, const machine& Machine){
    stream << "Machine ID: " << Machine.getID() << "\n";
    stream << "Speed: " << Machine.getSpeed();
    return stream;
}