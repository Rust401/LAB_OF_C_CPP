#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "core.h"
#include "dude.h"
#include "indicator.h"

void seachTheDepth(double depth,std::vector<Dude>& dudes,Indicators& indicator){
    OneTry(dudes,depth);
    oneValidation(dudes,indicator);
}

void binarySearch(double targetHeight,double bias,double left,double right)
{
    double leftHeight=targetHeight*(1-bias);
    double rightHeight=targetHeight*(1+bias);
    
    std::vector<Dude> dudes;
    Indicators indicator;

    while(indicator._height<leftHeight||indicator._height>rightHeight){
        double mid=left+(right-left)/2;
        seachTheDepth(mid,dudes,indicator);
        if(indicator._height>=rightHeight){
            right=mid;
        }else if(indicator._height<=leftHeight){
            left=mid;
        }
    }

    indicator.display();

    return ;
}



int main()
{
    /* std::vector<Dude> dudes;
    //OneTry(dudes,0.7348f);

    Indicators indicator; */
    //seachTheDepth(0.7348f,dudes,indicator);
    binarySearch(18.0f,0.00005,0.5,1.5);
    
    //oneValidation(dudes,indicator);
    /* indicator.display();

    auto points=getChainShape(dudes);

    saveTheChainShapeToFile(points); */
}