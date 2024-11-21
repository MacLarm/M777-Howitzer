/***********************************************************************
* Header File:
* POSITION
* Author:
* <your name here>
* Summary:
* Everything we need to know about a location on the screen.
************************************************************************/


#pragma once

#include <iostream>
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;


/*********************************************
* Position
* A single position on the field in Meters
*********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;


   // constructors
   Position() : x(0.0), y(0.0) {}
   Position(double x, double y) : x(x), y(y) {};
   Position(const Position & pt) : x(pt.getMetersX()), y(pt.getMetersY()) {}
   Position& operator = (const Position& pt)
   {
      this->x = pt.getMetersX();
      this->y = pt.getMetersY();

      return *this;
   };

   // getters
   double getMetersX() const { return x; }
   double getMetersY() const { return y; }
   double getPixelsX() const { return x / metersFromPixels; }
   double getPixelsY() const { return y / metersFromPixels; }
   double getZoom()    const { return metersFromPixels; }

   // setters
   void setZoom(double z) { metersFromPixels = z; }
   void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
   void setMetersX(double xMeters) { x = xMeters; }
   void setMetersY(double yMeters) { y = yMeters; }
   void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }
   
   void addMetersX(double x) { this->x += x; }
   void addMetersY(double y) { this->y += y; }
   void addPixelsX(double x) { this->x += x * metersFromPixels; }
   void addPixelsY(double y) { this->y += y * metersFromPixels; }
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() { }


private:
   double x; // horizontal position
   double y; // vertical position
   static double metersFromPixels;
};



// stream IO useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in, Position& pt);


/*********************************************
* PT
* Trivial point
*********************************************/
struct PT
{
   double x;
   double y;
};
