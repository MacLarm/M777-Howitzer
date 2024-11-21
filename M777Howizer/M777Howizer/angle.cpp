/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    McKay Larman
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#define TWO_PI = M_PI * 2 //6.28318530718
#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
   double normalized; // Initialize.
   if (radians < 0) // If the number is negative we add TWO_PI to make it positve again;
      normalized = (fmod(radians, M_PI * 2)) + (M_PI * 2);
   else // If the number is positve we find the remainder.
      normalized = fmod(radians, M_PI * 2);
   return normalized;
}



