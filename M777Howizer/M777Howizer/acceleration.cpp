/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & a, double magnitude)
{
   double radians = a.getRadians();
   ddx = magnitude * sin(radians);
   ddy = magnitude * cos(radians);
}

/*********************************************
* ACCELERATION : ADD
* a += a
*********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}
