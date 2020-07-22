#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "indicator.h"


void Indicators::display() {
    std::cout<<"phiCylinder:  "<< this->_phiCylinder<<std::endl;
    std::cout<<"phiLastChain: "<< this->_phiLastChain<<std::endl;
    std::cout<<"height:       "<< this->_height<<std::endl;
    std::cout<<"distance:     "<< this->_distance<<std::endl;
    std::cout<<"depth:        "<< this->_depth<<std::endl;
}






