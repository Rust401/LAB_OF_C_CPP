#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>
#include <limits.h>
#include "para.h"
#include "dude.h"
#include "indicator.h"


/* -------------------------------------------------------------------------------- */
/* ---------------------------- PREVIOUS & NEXT ---------------------------- */
/* -------------------------------------------------------------------------------- */
void nextDude(Dude& preDude,Dude& currentDude, uint32_t index, double depth)
{
    /* the dummy dude, contain no data */
    if (index == 0){
        currentDude._type="dummy";
        currentDude._index=0;
    }

    /* buoy */
    if (index == 1){
        /* calculate */
        double windForce = 0.625 * (BUOY_HEIGHT - depth) * 2 * BUOY_R * pow(WIND_SPEED, 2);
        double floatage = SEA_WATER_DENSITY * G * depth * PHI * pow(BUOY_R, 2);
        double gravity = BUOY_MASS * G;
        double thetaOne = atan((floatage - gravity) / windForce); /* it's a radian */
        double tractionOne = windForce / cos(thetaOne);


        /* put the value back */
        currentDude._index=index;
        currentDude._type="buoy";
        currentDude._thetaOne=thetaOne;
        currentDude._tractionOne=tractionOne;
        currentDude._length=depth;
        currentDude._phi=PHI/2;
    }

    /* tube */
    if(index<=2&&index<=5){
        /* calculate */
        double thetaOne=preDude._thetaOne;
        double tractionOne=preDude._tractionOne;
        double gravity=TUBE_MASS*G;
        double floatage=SEA_WATER_DENSITY*G*PHI*pow(TUBE_RADIUS,2)*TUBE_LENGTH;
        double horizontal=tractionOne*cos(thetaOne);
        double vertical = tractionOne * sin(thetaOne) - (gravity - floatage);
        double thetaTwo=atan(vertical/horizontal);/* it's a radian */
        double tractionTwo=horizontal/cos(thetaTwo);
        double phi=atan(
            (
                2*tractionOne*sin(thetaOne)-(gravity-floatage)
            )/(
                2*tractionOne*cos(thetaOne)
            )
        );
        

        /* put the value back */
        currentDude._index=index;
        currentDude._type="tube";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo+tractionTwo;
        currentDude._phi=phi;
        currentDude._length=TUBE_LENGTH;
    }


    /* cylinder */
    if(index==5){
        /* calculate */
        double thetaOne=preDude._thetaOne;
        double tractionOne=preDude._tractionOne;

        // 1) ball
        double gravityBall=HAMMER_MASS*G;
        double ballVolumn=HAMMER_MASS/HAMMER_DENSITY;
        double floatageBall=ballVolumn*SEA_WATER_DENSITY*G;

        // 2) cylinder
        double gravityCyinder=CYLINDER_MASS*G;
        double cylinderVolumn=pow(CYLINDER_RADIUS,2)*PHI*CYLINDER_LENGTH;
        double floatageCylinder=SEA_WATER_DENSITY*G*cylinderVolumn;


        double horizontal=tractionOne*cos(thetaOne);;
        double vertical = 
        tractionOne * sin(thetaOne) - 
        (gravityCyinder - floatageCylinder) - 
        (gravityBall-floatageBall);

        double thetaTwo=atan(vertical/horizontal);/* it's a radian */
        double tractionTwo=horizontal/cos(thetaTwo);

        double phi=atan(
            (
                2*tractionOne*sin(thetaOne)-(gravityCyinder-floatageCylinder)
            )/(
                2*tractionOne*cos(thetaOne)
            )
        );

        /* put the value back */
        currentDude._index=index;
        currentDude._type="cylinder";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo+tractionTwo;

        currentDude._phi=phi;
        currentDude._length=CYLINDER_LENGTH;
    }

    /* chain */
    if(index>5){
        /* calculate */
        double thetaOne=preDude._thetaOne;
        double tractionOne=preDude._tractionOne;
        double gravity=UNIT_LENGTH*UNIT_MASS*G;
        double floatage=0;
        double horizontal=tractionOne*cos(thetaOne);
        double vertical = tractionOne * sin(thetaOne) - (gravity - floatage);
        double thetaTwo=atan(vertical/horizontal);/* it's a radian */
        double tractionTwo=horizontal/cos(thetaTwo);
        double phi=atan(
            (
                2*tractionOne*sin(thetaOne)-(gravity-floatage)
            )/(
                2*tractionOne*cos(thetaOne)
            )
        );
        

        /* put the value back */
        currentDude._index=index;
        currentDude._type="chain";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo+tractionTwo;
        currentDude._phi=phi;
        currentDude._length=UNIT_LENGTH;
    }
}

/* -------------------------------------------------------------------------------- */
/* ---------------------------- TRY ONE IMMERSION TYEP ---------------------------- */
/* -------------------------------------------------------------------------------- */


void OneTry(std::vector<Dude>& dudes, double depth)
{
    if(dudes.size()!=0){
        dudes.clear();
    }

    uint32_t count=0;

    // 1) dummy dude
    Dude nullDude;
    Dude dummyDude;
    nextDude(nullDude,dummyDude,count,depth);
    dudes.push_back(dummyDude);
    ++count;

    // 2) buoy
    Dude buoyDude;
    nextDude(dudes.back(),buoyDude,count,depth);
    dudes.push_back(buoyDude);
    ++count;

    // 3) tube
    while(count<=5){
        Dude currentTube;
        nextDude(dudes.back(),currentTube,count,depth);
        dudes.push_back(currentTube);
        ++count;
    }

    // 4) cylinder
    Dude cylinderDude;
    nextDude(dudes.back(),cylinderDude,count,depth);
    dudes.push_back(cylinderDude);
    ++count;
    

    // 5) chain
    while(count<=TOTAL_COUNT){
        Dude currentChain;
        nextDude(dudes.back(),currentChain,count,depth);
        dudes.push_back(currentChain);
        ++count;
    }
}

/* -------------------------------------------------------------------------------- */
/* ---------------------------- GET THE INDICATORS ---------------------------- */
/* -------------------------------------------------------------------------------- */

void oneValidation(std::vector<Dude>& dudes, Indicators& indicators){
    if(dudes.size()==0){
        return;
    }

    // Distance from the sea level
    double currentHeight=0;
    for(int i=1;i<dudes.size();++i){
        currentHeight+=dudes[i]._length*sin(dudes[i]._phi);
    }
    indicators._height=currentHeight;

    // Distance betweeen buoy and anchor
    double currentLength=0;
    for(int i=2;i<dudes.size();++i){
        currentLength=dudes[i]._length*cos(dudes[i]._phi);
    }
    indicators._distance=currentLength;

    // phi of cylinder
    indicators._phiCylinder=dudes[6]._phi*180/PHI; /* now it's a degree */
    
    // phi of last Chain
    indicators._phiLastChain=dudes.back()._phi*180/PHI;

    // immersion depth
    indicators._depth=dudes[1]._length;
}

/* -------------------------------------------------------------------------------- */
/* ---------------------------- THE SHAPE OF THE CHAIN ---------------------------- */
/* -------------------------------------------------------------------------------- */

/* Get the data of chain shape */
std::vector<std::pair<double,double>> getChainShape(std::vector<Dude>& dudes){
    std::vector<std::pair<double,double>> points;
    uint32_t i=dudes.size()-1;

    //insert the first point
    std::pair<double,double> firstPoint=std::make_pair(0.0,0.0);
    points.push_back(firstPoint);

    //inser the chains from the last chain
    while(dudes[i]._type=="chain"){
        double deltaX=dudes[i]._length*cos(dudes[i]._phi);
        double deltaY=dudes[i]._length*sin(dudes[i]._phi);
        auto currentPoint=std::make_pair(points.back().first+deltaX,points.back().second+deltaY);
        points.push_back(currentPoint);
    }
    
    return points;
}

/* out put the data to a file */

