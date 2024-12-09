/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Module
 *      ANGLE
 * 3. Assignment Description:
 *      A class to represent an angle
 **************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#define TWO_PI 6.28318530718
#define PI_EIGHT (3.1415926 / 8.0)
using namespace std;

class TestAngle;
class TestAngleRadian;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
   
public:
   
   // Constructors
   Angle()                 : radians(0.0)  {}
   Angle(const Angle& rhs) : radians(rhs.radians)  {}
   Angle(double degrees)   : radians(convertToRadians(degrees))  {}

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees);
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp()                    { radians = 0.0; }
   void setDown()                  { radians = M_PI; }
   void setRight()                 { radians = M_PI_2; }
   void setLeft()                  { radians = M_PI + M_PI_2; }
   virtual void display(ostream & out) const { out << radians; }
   void reverse();
   Angle& add(double delta);
   
   virtual Angle& operator= (const Angle &rhs) { radians = rhs.radians; return *this; } // assignment
   Angle& operator- ()                 { this->reverse(); return *this; } // negative
   bool   operator==(const Angle &rhs) { return radians == rhs.radians; } // Equals
   bool   operator!=(const Angle &rhs) { return radians != rhs.radians; } // Not equals
   friend ostream& operator<<(ostream& out, const Angle &rhs);
   friend istream& operator>>(istream & in, Angle &rhs);
   
   virtual Angle& operator++() { radians += 0.0174533; return *this; }
   virtual Angle& operator++(int postfix) { Angle returnAngle(*this); radians += 0.0174533; return returnAngle; }
   virtual Angle& operator--() { radians -= 0.0174533; return *this; }
   virtual Angle& operator--(int postfix) { Angle returnAngle(*this); radians -= 0.0174533; return returnAngle; }
   
private:
   double normalize(double radians) const;
   double convertToDegrees(double radians) const;
   double convertToRadians(double degree) const;
protected:
   double radians;   // 360 degrees equals 2 PI radians

};


/************************************
 * ANGLE RADIANS
 ************************************/
class AngleRadians : public Angle
{
   friend TestAngleRadian;
   
public:
   // Constructors
   AngleRadians()                 : Angle()  {}
//   AngleRadians(const Angle& rhs) : Angle(const Angle& rhs)  {}
   AngleRadians(double degrees)   : Angle(degrees)  {}
   
   virtual void display(ostream & out) const { out << getRadians(); }
   
   virtual AngleRadians& operator = (const AngleRadians &rhs) { radians = rhs.radians; return *this; }
   virtual AngleRadians& operator ++ () { radians += 0.0174533; return *this; }
   virtual AngleRadians& operator -- () { radians -= 0.0174533; return *this; }
   
   
};

