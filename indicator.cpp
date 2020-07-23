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
    std::cout<<std::endl;
}


void Indicators::init() {
    this-> _phiCylinder=0;
    this-> _phiLastChain=0;
    this-> _height=0;
    this-> _distance=0;
    this-> _depth=0;
}

bool Indicators::validate(){
    if(
        ((PHI/2-this->_phiCylinder*PHI/180)<=MAX_PHI_CYLINDER)
        &&
        (this->_phiLastChain*PHI/180<=MAX_PHI_LASTCHAIN)
    ){
        return true;
    }
    return false;
}





