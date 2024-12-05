/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    McKay Larman
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle()                  : radians(0.0)               {}
   Angle(const Angle& rhs)  : radians(rhs.getRadians())  {}
   Angle(double degrees)    : radians(this->normalize(degrees * (M_PI / 180)))           {}
   Angle & operator=(Angle &rhs) { this->radians = rhs.radians; return *this; }

   // Getters
   double getDegrees() const { return radians * (180/M_PI); }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx()    const { return sin(radians); }
   double getDy()    const { return cos(radians); }
   bool   isRight()  const { return radians < M_PI; }
   bool   isLeft()   const { return radians > M_PI; }


   // Setters
   void setDegrees(double degrees) { radians = this->normalize(degrees * (M_PI / 180)); }
   void setRadians(double radians) { this -> radians = this->normalize(radians); }
   void setUp()                    { radians = 0.0; }
   void setDown()                  { radians = M_PI; }
   void setRight()                 { radians = M_PI_2; }
   void setLeft()                  { radians = M_PI + M_PI_2; }
   void reverse()                  { radians += M_PI; }
   Angle& add(double delta)        { radians = this->normalize(radians + delta); return *this; }

   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy)  { radians = this->normalize(atan(dx/dy)); }
   
   Angle operator+(double degrees) const { return Angle(); }
   bool operator==(Angle &rhs) const { return radians == rhs.radians;}

private:

   double normalize(double radians) const;
   double radians;   // 360 degrees equals 2 PI radians
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}
