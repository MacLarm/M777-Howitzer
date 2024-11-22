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
    double g = 9.80665;
    double r = 6371000.0;
    double gravity = g * pow(r / (r + altitude), 2);
   return gravity;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
    // Constants
    const double rho0 = 1.225;      // Sea level air density (kg/m³)
    const double T0 = 288.15;      // Sea level standard temperature (K)
    const double L = 0.0065;       // Temperature lapse rate (K/m) (troposphere)
    const double g = 9.80665;      // Gravitational acceleration (m/s²)
    const double R = 287.05;       // Specific gas constant for air (J/(kg·K))

    if (altitude < 0)
        altitude = 0;

    // Troposphere: below 11,000 m
    if (altitude <= 11000.0)
    {
        double T = T0 - L * altitude; // Temperature at given altitude
        return rho0 * pow(T / T0, g / (L * R) - 1.0);
    }

    // Stratosphere: 11,000 m to 20,000 m
    else if (altitude <= 20000.0)
    {
        double T11 = T0 - L * 11000.0;                 // Temperature at 11,000 m
        double rho11 = rho0 * pow(T11 / T0, g / (L * R) - 1.0); // Density at 11,000 m
        double h_diff = altitude - 11000.0;           // Height difference
        return rho11 * exp(-g * h_diff / (R * T11));
    }

    // Above stratosphere (up to 80,000 m): use exponential decay approximation
    else
    {
        double T20 = T0 - L * 11000.0;                 // Approximate constant T above 20,000 m
        double rho20 = densityFromAltitude(20000.0);  // Density at 20,000 m
        double h_diff = altitude - 20000.0;           // Height difference
        return rho20 * exp(-g * h_diff / (R * T20));
    }
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
    // Constants
    const double T0 = 288.15;      // Sea level standard temperature (K)
    const double L = 0.0065;       // Temperature lapse rate (K/m) (troposphere)
    const double R = 287.05;       // Specific gas constant for air (J/(kg·K))
    const double gamma = 1.4;      // Adiabatic index for air

    // Troposphere: below 11,000 m
    if (altitude <= 11000.0)
    {
        double T = T0 - L * altitude; // Temperature at given altitude
        return sqrt(gamma * R * T);  // Speed of sound
    }

    // Stratosphere and higher (temperature assumed constant beyond 11,000 m)
    else
    {
        double T11 = T0 - L * 11000.0; // Temperature at 11,000 m
        return sqrt(gamma * R * T11);  // Speed of sound
    }
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   return -99.9;
}

