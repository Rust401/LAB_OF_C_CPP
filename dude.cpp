#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "dude.h"

void Dude::display()
{
    std::cout<<std::endl;
    std::cout<<"index:         "<<this->_index<<std::endl;
    std::cout<<"type:          "<<this->_type<<std::endl;
    std::cout<<"thetaOne:      "<<this->_thetaOne<<std::endl;
    std::cout<<"thetaTwo:      "<<this->_thetaTwo<<std::endl;
    std::cout<<"phi:           "<<this->_phi<<std::endl;
    std::cout<<"tractionOne:   "<<this->_tractionOne<<std::endl;
    std::cout<<"tractionTwo:   "<<this->_tractionTwo<<std::endl;
    std::cout<<"length:        "<<this->_length<<std::endl;
    std::cout<<std::endl;
}