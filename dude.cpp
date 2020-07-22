#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "dude.h"
#include "para.h"

void Dude::display()
{
    std::cout<<std::endl;
    std::cout<<"index:         "<<this->_index<<std::endl;
    std::cout<<"type:          "<<this->_type<<std::endl;
    std::cout<<"thetaOne:      "<<this->_thetaOne*180/PHI<<std::endl;
    std::cout<<"thetaTwo:      "<<this->_thetaTwo*180/PHI<<std::endl;
    std::cout<<"phi:           "<<this->_phi*180/PHI<<std::endl;
    std::cout<<"tractionOne:   "<<this->_tractionOne<<std::endl;
    std::cout<<"tractionTwo:   "<<this->_tractionTwo<<std::endl;
    std::cout<<"length:        "<<this->_length<<std::endl;
    std::cout<<std::endl;
}