/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "angle.h"
#include <cmath>

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {};

   double areaCircle()
   {
       return M_PI * radius * radius;
   }

   // advance the round forward until the next unit of time
   void advance(double simulationTime) 
   {
      Projectile::PositionVelocityTime pvt;
      pvt = flightPath.back();
      double time = simulationTime - pvt.t;

      double velocity = pvt.v.getSpeed();
      double mach = velocity / speedSoundFromAltitude(pvt.pos.getMetersY());
      double airDensity = densityFromAltitude(pvt.pos.getMetersY());
      double dragCoefficient = dragFromMach(mach);
      double gravity = gravityFromAltitude(pvt.pos.getMetersY());
      double drag = 0.5 * dragCoefficient * airDensity * velocity * velocity * areaCircle();
      double dragAccel = drag / mass;
      double angle = atan2(pvt.v.getDX(), pvt.v.getDY());

      double ddx = -dragAccel * sin(angle);
      double ddy = -dragAccel * cos(angle) - gravity;
      double x = pvt.pos.getMetersX();
      double y = pvt.pos.getMetersY();
      x += pvt.v.getDX() * time + 0.5 * ddx * time * time;
      y += pvt.v.getDY() * time + 0.5 * ddy * time * time;
      double dx = pvt.v.getDX() + (ddx * time);
      double dy = pvt.v.getDY() + (ddy * time);
      Velocity newVelocity(dx,dy);
      
      PositionVelocityTime newPvt;
      Position pos;
      pos.setMetersX(x);
      pos.setMetersY(y);
      newPvt.pos = pos;
      newPvt.v = newVelocity;
      newPvt.t = simulationTime;
      flightPath.push_back(newPvt);
      if (flightPath.size() >= 20)
          flightPath.pop_front();
      
//           fire(pos, simulationTime, angle, velocity);
   }
   void reset() 
   {
       mass = DEFAULT_PROJECTILE_WEIGHT;
       radius = DEFAULT_PROJECTILE_RADIUS;
       flightPath.clear();
   }

   
   void fire(Position pos, double time, Angle angle, double vel)
   {
       Projectile::PositionVelocityTime pvt;
       pvt.pos = pos;   
       pvt.t = time;
       Velocity v;
       v.set(angle, vel);
       pvt.v = v;
       flightPath.push_back(pvt);
   }

   bool isFired()
   {
       return flightPath.size() > 0;
   }
   
   void drawProjectile(ogstream & gout);

   Position getPosition()
   {
       PositionVelocityTime pvt;
       pvt = flightPath.back();
       Position pos;
       pos = pvt.pos;
       return pos;
   }
   
   double getVelocity()
   {
      PositionVelocityTime pvt;
      pvt = flightPath.back();
      Velocity v;
      v = pvt.v;
      return v.getSpeed();
   }

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;

      //PositionVelocityTime& operator = (PositionVelocityTime& rhs) 
      //{ 
      //    if (this != &rhs) { // Avoid self-assignment
      //        pos = rhs.pos;
      //        v = rhs.v;
      //        t = rhs.t;
      //    }
      //    return  *this;  
      //}
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
};
