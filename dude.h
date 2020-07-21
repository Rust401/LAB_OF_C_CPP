#ifndef DUDE_H
#define DUDE_H

#include <string>
#include <vector>
#include "para.h"

struct Dude
{
    //public
    uint16_t _index;
    std::string _type;
    double _thetaOne;
    double _thetaTwo;
    double _phi;
    double _tractionOne;
    double _tractionTwo;
    double _length;
    double _gravity;
    double _floatage;

    //constructor
    Dude(uint16_t index, std::string &type)
    {
        this->_index = _index;
        this->_type = type;
        this->_thetaOne = 0;
        this->_thetaTwo = 0;
        this->_phi = 0;
        this->_tractionOne = 0;
        this->_tractionTwo = 0;
        this->_gravity=0;
        this->_floatage=0;
        this->_length=0;
    }
    Dude(){
        this->_index=0;
        this->_type="default";
        this->_thetaOne = 0;
        this->_thetaTwo = 0;
        this->_phi = 0;
        this->_tractionOne = 0;
        this->_tractionTwo = 0;
        this->_gravity=0;
        this->_floatage=0;
        this->_length=0;
    }
};

#endif //DUDE_H