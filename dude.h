#include <string>
#include <vector>
#include "float.h"

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
    }
}
