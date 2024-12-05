/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/

#include "physics.h"  // for the prototypes
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
    double r;

    // Check if our target is smaller than the first item in the list
    if (domain < mapping[0].domain) {
        r = mapping[0].range;
    }
    // Check if our target is larger than the last item in the list.
    else if (domain > mapping[numMapping - 1].domain) {
        r = mapping[numMapping - 1].range;
    }
    // The number is in range, find the correct location
    else {
        int i = 0;

        // Find the correct interval for interpolation
        // Increase the index until the next number is larger than domain
        while (domain > mapping[i + 1].domain) {
            i++;
        }

        double d0 = mapping[i].domain;
        double r0 = mapping[i].range;
        double d1 = mapping[i + 1].domain;
        double r1 = mapping[i + 1].range;

        // Perform linear interpolation
        r = r0 + (r1 - r0) * (domain - d0) / (d1 - d0);
    }
    return r;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
    const Mapping gravityFromAltitudeTable[] =
    {//    alt | density
        {0	    , 9.807},
        {1000	, 9.804},
        {2000	, 9.801},
        {3000	, 9.797},
        {4000	, 9.794},
        {5000	, 9.791},
        {6000	, 9.788},
        {7000	, 9.785},
        {8000	, 9.782},
        {9000	, 9.779},
        {10000	, 9.776},
        {15000	, 9.761},
        {20000	, 9.745},
        {25000	, 9.730},
        {30000	, 9.715},
        {40000	, 9.684},
        {50000	, 9.654},
        {60000	, 9.624},
        {70000	, 9.594},
        {80000	, 9.564}  // 20
    };

    double gravAltitude = linearInterpolation(gravityFromAltitudeTable, 20, altitude);
    return gravAltitude;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
    const Mapping densityAltitudeTable[] =
    {//    alt | density
        {    0, 1.2250000}, // 1
        { 1000, 1.1120000}, // 2
        { 2000, 1.0070000}, // 3
        { 3000, 0.9093000}, // 4
        { 4000, 0.8194000}, // 5
        { 5000, 0.7364000}, // 6
        { 6000, 0.6601000}, // 7
        { 7000, 0.5900000}, // 8
        { 8000, 0.5258000}, // 9
        { 9000, 0.4671000}, // 10
        {10000, 0.4135000}, // 11
        {15000, 0.1948000}, // 12
        {20000, 0.0889100}, // 13
        {25000, 0.0400800}, // 14
        {30000, 0.0184100}, // 15
        {40000, 0.0039960}, // 16
        {50000, 0.0010270}, // 17
        {60000, 0.0003097}, // 18
        {70000, 0.0000828}, // 19
        {80000, 0.0000185}  // 20
    };

    double density = linearInterpolation(densityAltitudeTable, 20, altitude);
    return density;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
    const Mapping soundSpeedAltitudeTable[] =
    {//  Mach | DragCoefficient
        {0,	340},
        {1000, 336},
        {2000, 332},
        {3000, 328},
        {4000, 324},
        {5000, 320},
        {6000, 316},
        {7000, 312},
        {8000, 308},
        {9000, 303},
        {10000,	299},
        {15000,	295},
        {20000,	295},
        {25000,	295},
        {30000,	305},
        {40000,	324},
        {50000,	337},
        {60000,	319},
        {70000,	289},
        {80000,	269}
    };

    double soundSpeedAltitude = linearInterpolation(soundSpeedAltitudeTable, 20, altitude);
    return soundSpeedAltitude;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
    const Mapping dragCoefficientTable[] =
    {//  Mach | DragCoefficient
        {0.000, 0.0000}, // 1
        {0.300, 0.1629}, // 2
        {0.500, 0.1659}, // 3
        {0.700, 0.2031}, // 4
        {0.890, 0.2597}, // 5
        {0.920, 0.3010}, // 6
        {0.960, 0.3287}, // 7
        {0.980, 0.4002}, // 8
        {1.000, 0.4258}, // 9
        {1.020, 0.4335}, // 10
        {1.060, 0.4483}, // 11
        {1.240, 0.4064}, // 12
        {1.530, 0.3663}, // 13
        {1.990, 0.2897}, // 14
        {2.870, 0.2297}, // 15
        {2.890, 0.2306}, // 16
        {5.000, 0.2656}  // 17
    };

    double dragCoefficient = linearInterpolation(dragCoefficientTable, 17, speedMach);
    return dragCoefficient;
}

