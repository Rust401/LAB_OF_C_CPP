#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits.h>
#include "parameters.h"
#include "dude.h"

Dude nextDude(Dude preDude, uint32_t index, double depth)
{
    /* the dummy dude, contain no data */
    if (index == 0)
    {
        return new Dude(index, "dummy");
    }

    /* the buoy */
    if (index == 1)
    {
        Dude currentDude = new Dude(index, "buoy");
        double windForce = 0.625 * (BUOY_HEIGHT - depth) * 2 * BUOY_R * pow(WIND_SPEED, 2);
        double floatage = SEA_WATER_DENSITY * G * depth * PHI * pow(BUOY_R, 2);
        double gravity = BUOY_MASS * G;
        double thetaOne = atan((floatage - gravity) / windForce); /* it's a radian */
        double tractionOne = windForce / cos(thetaOne);
    }
}