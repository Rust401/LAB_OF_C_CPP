#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>
#include <string.h>
#include <utility>
#include <algorithm>
#include <vector>
#include <limits.h>
#include "para.h"
#include "dude.h"
#include "indicator.h"
#include "core.h"

#ifdef SEA_FORCE
/* get the phi of the dude*/
double binarySearchGetPHI(double c,double a, double b,double thetaOne, double tractionOne)
{
    double left=0;
    double right=PHI/2;
    while(right-left>2*PHI_BIAS){
        double mid=left+(right-left)/2;
        double currentResult=tan(mid)-c/(a+b*sin(mid));
        if(currentResult>PHI_BIAS){
            right=mid;
        }else if(currentResult<-PHI_BIAS){
            left=mid;
        }else{
            return mid;
        }
    }
    return left+(right-left)/2;
}
#endif

/* -------------------------------------------------------------------------------- */
/* ---------------------------- PREVIOUS & NEXT ---------------------------- */
/* -------------------------------------------------------------------------------- */
void nextDude(Dude& preDude,Dude& currentDude, uint32_t index, double depth,double hammerMass)
{
    /* the dummy dude, contain no data */
    if (index == 0){
        currentDude._type="dummy";
        currentDude._index=0;
    }

    /* buoy */
    if (index == 1){
#ifdef SEA_FORCE
        /* calculate */
        double seaForce=374*BUOY_R*2*depth*pow(WATER_SPEED,2);
        double windForce = 0.625 * (BUOY_HEIGHT - depth) * 2 * BUOY_R * pow(WIND_SPEED, 2);
        double floatage = SEA_WATER_DENSITY * G * depth * PHI * pow(BUOY_R, 2);
        double gravity = BUOY_MASS * G;
        double horizontal=seaForce+windForce;
        double vertical=floatage-gravity;
        double thetaOne = atan((vertical /horizontal));/* it's a radian */
        double tractionOne = horizontal / cos(thetaOne);
#else
        /* calculate */
        double windForce = 0.625 * (BUOY_HEIGHT - depth) * 2 * BUOY_R * pow(WIND_SPEED, 2);
        double floatage = SEA_WATER_DENSITY * G * depth * PHI * pow(BUOY_R, 2);
        double gravity = BUOY_MASS * G;
        double thetaOne = atan((floatage - gravity) / windForce); /* it's a radian */
        double tractionOne = windForce / cos(thetaOne);        
#endif
    /* put the value back */
        currentDude._index=index;
        currentDude._type="buoy";
        currentDude._thetaTwo=thetaOne;
        currentDude._tractionTwo=tractionOne;
        currentDude._length=depth;
        currentDude._phi=PHI/2;
    }

    /* tube */
    if(index>=2&&index<=5){
#ifdef SEA_FORCE
        /* calculate */
        // 1) traction from the preDude
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;

        // 2) tube itself
        double gravity=TUBE_MASS*G;
        double floatage=SEA_WATER_DENSITY*G*PHI*pow(TUBE_RADIUS,2)*TUBE_LENGTH;

        // 3) get the phi of the tube
        /* warning! trick part Get phi*/
        /*
            tan(phi)=c/(a+b*sin(phi))
            here:
                c=2*TractionOne*sin(thetaOne)-(gravity-floatage);
                a=2*TractionOne*cos(thetaOne);
                b=374*TUBE_RADIUS*2*TUBE_LENGTH*pow(WATER_SPEED,2);
        */
       double c=2*tractionOne*sin(thetaOne)-(gravity-floatage);
       double a=2*tractionOne*cos(thetaOne);
       double b=374*TUBE_RADIUS*2*TUBE_LENGTH*pow(WATER_SPEED,2);
       double phi=binarySearchGetPHI(c,a,b,thetaOne,tractionOne);

       // 4) calculate the traction with nextDude
       double waterForceTube=374*2*TUBE_RADIUS*TUBE_LENGTH*sin(phi)*pow(WATER_SPEED,2);
       double horizontal=tractionOne*cos(thetaOne)+waterForceTube;
       double vertical=tractionOne*sin(thetaOne)-(gravity-floatage);
       double thetaTwo=atan(vertical/horizontal);
       double tractionTwo=horizontal/cos(thetaTwo);
        
#else
        /* calculate */
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;
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
#endif

        /* put the value back */
        currentDude._index=index;
        currentDude._type="tube";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo=tractionTwo;
        currentDude._phi=phi;
        currentDude._length=TUBE_LENGTH;
    }


    /* cylinder */
    if(index==6){

#ifdef SEA_FORCE
    /* calculate */
    // 1) traction from the preDude
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;
    // 2) ball
        double gravityBall=hammerMass*G;
        double ballVolumn=hammerMass/HAMMER_DENSITY;
        double floatageBall=ballVolumn*SEA_WATER_DENSITY*G;
        double ballHorizontal=374*
                              PHI*
                              pow(3*ballVolumn/(4*PHI),2/3)*
                              pow(WATER_SPEED,2);
        double ballVertical=gravityBall-floatageBall;

    // 3) cylinder
        double gravityCyinder=CYLINDER_MASS*G;
        double cylinderVolumn=pow(CYLINDER_RADIUS,2)*PHI*CYLINDER_LENGTH;
        double floatageCylinder=SEA_WATER_DENSITY*G*cylinderVolumn;

        /* warning! trick part Get phi*/
        /*
            tan(phi)=c/(a+b*sin(phi))
            here:
                c=2*TractionOne*sin(thetaOne)-
                                   (gravityCylinder-floatageCylinder)-
                                   ballVertical;
                a=2*TractionOne*cos(thetaOne)+ballHorizontal
                b=374*CYLINDER_RAIUS*2*CYLINDER_LENGTH*pow(WATER_SPEED,2);
        */
        double c=2*tractionOne*sin(thetaOne)-
                 (gravityCyinder-floatageCylinder)-
                 ballVertical;
        double a=2*tractionOne*cos(thetaOne)+ballHorizontal;
        double b=374*CYLINDER_RADIUS*2*CYLINDER_LENGTH*pow(WATER_SPEED,2);
        double phi=binarySearchGetPHI(c,a,b,thetaOne,tractionOne);
        double waterForceCylinder=b*sin(phi);

        double vertical=tractionOne*sin(thetaOne)-
                        (gravityCyinder-floatageCylinder)-
                        ballVertical;


        double horizontal=tractionOne*cos(thetaOne)+waterForceCylinder+ballHorizontal;
        double thetaTwo=atan(vertical/horizontal);
        double tractionTwo=vertical/sin(thetaTwo);
                          
#else
        /* calculate */
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;

        // 1) ball
        // CAUTION HERE!!!! THE HAMMER_MASS IS IMPORTANT!
        double gravityBall=hammerMass*G;
        double ballVolumn=hammerMass/HAMMER_DENSITY;
        double floatageBall=ballVolumn*SEA_WATER_DENSITY*G;

        // 2) cylinder
        double gravityCyinder=CYLINDER_MASS*G;
        double cylinderVolumn=pow(CYLINDER_RADIUS,2)*PHI*CYLINDER_LENGTH;
        double floatageCylinder=SEA_WATER_DENSITY*G*cylinderVolumn;


        double horizontal=tractionOne*cos(thetaOne);
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

#endif
        

        /* put the value back */
        currentDude._index=index;
        currentDude._type="cylinder";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo=tractionTwo;

        currentDude._phi=phi;
        currentDude._length=CYLINDER_LENGTH;
    }

    /* chain */
    if(index>6){

#ifdef SEA_FORCE
        /* calculate */
        // 1) traction from the preDude
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;

        // 2) chain itself
        double gravity=UNIT_MASS*UNIT_LENGTH*G;
        double volumn=UNIT_MASS/CHAIN_DENSITY;
        double floatage=SEA_WATER_DENSITY*G*volumn;

        // 3) get the phi of the chain
        /* warning! trick part Get phi*/
        /*
            tan(phi)=c/(a+b*sin(phi))
            here:
                c=2*TractionOne*sin(thetaOne)-(gravity-floatage);
                a=2*TractionOne*cos(thetaOne);
                b=374*2*pow(volumn/(PHI*UNIT_LENGTH),0.5)*UNIT_LENGTH*pow(WATER_SPEED,2);
        */
        double c=2*tractionOne*sin(thetaOne)-(gravity-floatage);
        double a=2*tractionOne*cos(thetaOne);
        /* b is the coefficient of the waterforce with out the sin(phi)*/
        double b=374*2*pow(volumn/(PHI*UNIT_LENGTH),0.5)*
                    UNIT_LENGTH*pow(WATER_SPEED,2);
        double phi=binarySearchGetPHI(c,a,b,thetaOne,tractionOne);
    
        // 4) calculate the traction with nextDude
        double waterForceChain=b*sin(phi);
        double horizontal=tractionOne*cos(thetaOne)+waterForceChain;
        double vertical=tractionOne*sin(thetaOne)-(gravity-floatage);
        double thetaTwo=atan(vertical/horizontal);
        double tractionTwo=horizontal/cos(thetaTwo);

#else
        /* calculate */
        double thetaOne=preDude._thetaTwo;
        double tractionOne=preDude._tractionTwo;

        double gravity=UNIT_LENGTH*UNIT_MASS*G;
        double volumn=UNIT_MASS/CHAIN_DENSITY;
        double floatage=SEA_WATER_DENSITY*G*volumn;

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
#endif

        /* put the value back */
        currentDude._index=index;
        currentDude._type="chain";
        currentDude._thetaOne=thetaOne;
        currentDude._thetaTwo=thetaTwo;
        currentDude._tractionOne=tractionOne;
        currentDude._tractionTwo=tractionTwo;
        currentDude._phi=phi;
        currentDude._length=UNIT_LENGTH;
    }
}

/* -------------------------------------------------------------------------------- */
/* ---------------------------- TRY ONE IMMERSION TYEP ---------------------------- */
/* -------------------------------------------------------------------------------- */


void OneTry(std::vector<Dude>& dudes, double depth,double hammerMass)
{
    if(dudes.size()!=0){
        dudes.clear();
    }

    uint32_t count=0;

    // 1) dummy dude
    Dude nullDude;
    Dude dummyDude;
    nextDude(nullDude,dummyDude,count,depth,hammerMass);
    dudes.push_back(dummyDude);
    ++count;


    // 2) buoy
    Dude buoyDude;
    nextDude(dudes.back(),buoyDude,count,depth,hammerMass);
    dudes.push_back(buoyDude);
    ++count;

    // 3) tube
    while(count<=5){
        Dude currentTube;
        nextDude(dudes.back(),currentTube,count,depth,hammerMass);
        dudes.push_back(currentTube);
        ++count;
    }

    // 4) cylinder
    Dude cylinderDude;
    nextDude(dudes.back(),cylinderDude,count,depth,hammerMass);
    dudes.push_back(cylinderDude);
    ++count;
    

    // 5) chain
    bool reachBottom=false;
    while(count<=TOTAL_COUNT+6){
        Dude currentChain;
        nextDude(dudes.back(),currentChain,count,depth,hammerMass);

        //check whether the chain get the bottom
        if(currentChain._thetaTwo<=0){
            currentChain._thetaOne=0;
            currentChain._thetaTwo=0;
            currentChain._tractionOne=0;
            currentChain._tractionTwo=0;
            currentChain._phi=0;

            reachBottom=true;
            break;
        }
        dudes.push_back(currentChain);
        ++count;
    }

    // 6) after reach the bottom
    if(reachBottom==true)
    {
        while(count<=TOTAL_COUNT+6){
            Dude bottomChain;
            bottomChain._type="bottomChain";
            bottomChain._index=count;
            bottomChain._length=UNIT_LENGTH;
            dudes.push_back(bottomChain);
            ++count;
        }
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
        currentLength+=dudes[i]._length*cos(dudes[i]._phi);
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

    //insert the chains from the last chain
    while(
        !strcmp(dudes[i]._type.c_str(),"chain")
        ||
        !strcmp(dudes[i]._type.c_str(),"bottomChain")
    ){
        double deltaX=dudes[i]._length*cos(dudes[i]._phi);
        double deltaY=dudes[i]._length*sin(dudes[i]._phi);
        auto currentPoint=std::make_pair(points.back().first+deltaX,points.back().second+deltaY);
        points.push_back(currentPoint);
        i-=1;
    }
    
    return points;
}

/* out put the data to a file */
void saveTheChainShapeToFile(std::vector<std::pair<double,double> >& points){
    if(points.size()==0){
        std::cout<<"No points data, ending the savving process..."<<std::endl;
        exit(1);
    }

    FILE* pFile = fopen(CHAIN_SHAPE_FILE,"w");
    if(pFile==nullptr){
        std::cout<<"Open file failed."<<std::endl;
        exit(1);
    }

    for(int i=0;i<points.size();++i)
    {
        fprintf(pFile,"%lf,%lf\n",points[i].first,points[i].second);
    }
    fclose(pFile);
    std::cout<<"File saved to "<<CHAIN_SHAPE_FILE<<std::endl;
    return;
}




