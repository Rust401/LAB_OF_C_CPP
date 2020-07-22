#ifndef INDICATOR_H
#define INDICATOR_H


#include <string>
#include <vector>
#include "para.h"

struct Indicators
{
    //public
    double _phiCylinder;
    double _phiLastChain;
    double _height;
    double _distance;
    double _depth;
    //double _hammerMass;

    Indicators(){
        this-> _phiCylinder=0;
        this-> _phiLastChain=0;
        this-> _height=0;
        this-> _distance=0;
        this-> _depth=0;
        //this-> _hammerMass=0;
    }

    void display();
    bool validate();
};

#endif //INDICATOR_H