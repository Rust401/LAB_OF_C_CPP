#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits.h>
#include "para.h"
#include "dude.h"

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
    }
}