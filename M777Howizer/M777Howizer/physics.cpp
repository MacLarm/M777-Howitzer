/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   double d0 = mapping[0].domain;
   double r0 = mapping[0].range;
   double d1 = mapping[1].domain;
   double r1 = mapping[1].range;
   int i = 0;

   do {
      d0 = mapping[i].domain;
      r0 = mapping[i].range;
      i++;
   } while (domain > d0 && domain < d1 && i < numMapping);

   d1 = mapping[i].domain;
   r1 = mapping[i].range;
   double r = r0 + (r1 - r0) * (domain - d0) / (d1 - d0);
   return r;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   return -99.9;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   return -99.9;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   return -99.9;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   return -99.9;
}

