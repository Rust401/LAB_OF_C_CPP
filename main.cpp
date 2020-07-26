#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "core.h"
#include "dude.h"
#include "indicator.h"

// give a immersion depth and get the shape of the whole system
void seachTheDepth(
    double depth,
    std::vector<Dude>& dudes,
    Indicators& indicator,
    double hammerMass
){
    OneTry(dudes,depth,hammerMass);
    oneValidation(dudes,indicator);
}

// give the targetHeight and the bias, get the suitable immersion depth
void binarySearchImmersionDepth(
    double targetHeight,
    double bias,
    double left,
    double right,
    double hammerMass,
    Indicators& indicator
){
    double leftHeight=targetHeight*(1-bias);
    double rightHeight=targetHeight*(1+bias);
    
    std::vector<Dude> dudes;


    // 1) binary search
    while(indicator._height<leftHeight||indicator._height>rightHeight){
        double mid=left+(right-left)/2;
        seachTheDepth(mid,dudes,indicator,hammerMass);
        if(indicator._height>=rightHeight){
            right=mid;
        }else if(indicator._height<=leftHeight){
            left=mid;
        }
    }

    // 2) output the status of the tube
    /* for(int i=2;i<=5;++i){
        dudes[i].display();
    } */

    // 3) save the shape of the chain
    /* auto points=getChainShape(dudes);
    saveTheChainShapeToFile(points); */

    return ;
}

// check the status, judge valid or not
bool isOK(Indicators& indicator){
    if(
        ((PHI/2-indicator._phiCylinder*PHI/180)<=MAX_PHI_CYLINDER)
        &&
        (indicator._phiLastChain*PHI/180<=MAX_PHI_LASTCHAIN)
    ){
        return true;
    }
    return false;
}

// get the minimum mass of the hammer ball
// calculate the region of the hammer mass first
double binarySearchHammerMass(
    double leftMass,
    double rightMass,
    double hammerMassBias,
    Indicators& indicator
){
    if((rightMass-leftMass)<=DEFUALT_HAMMER_MASS_BIAS){
        binarySearchImmersionDepth(18.0f,DEFUALT_BIAS,0.5,1.8,leftMass,indicator);
        return leftMass;
    }
    double midMass;
    while((rightMass-leftMass)>=hammerMassBias){
        midMass=leftMass+(rightMass-leftMass)/2;

        indicator.init();
        binarySearchImmersionDepth(18.0f,DEFUALT_BIAS,0.5,1.8,midMass,indicator);
        //indicator.display();
        if(indicator.validate()){
            rightMass=midMass;
        }else{
            leftMass=midMass;
        }
    }
    return midMass;
}



int main()
{

    /* Indicators currentIndicator;
    double minMass=binarySearchHammerMass(1200,6000,DEFUALT_HAMMER_MASS_BIAS,currentIndicator);
    std::cout<<"the minimum hammer mass: "<<minMass<<std::endl;
    currentIndicator.display(); */

    Indicators indi;
    binarySearchImmersionDepth(SEA_DEPTH,DEFUALT_BIAS,0.2f,10.0,3000,indi); //dudes is here
    indi.display();


    /* //unit test
    std::vector<Dude> dudes;
    Indicators indi;
    OneTry(dudes,0.7,1200);
    for(int i=0;i<dudes.size();++i){
        dudes[i].display();
    }
    oneValidation(dudes,indi);
    indi.display(); */


    return 0;
}