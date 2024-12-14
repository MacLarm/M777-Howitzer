/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "ground.h"
#include "projectile.h"
#include "uiInteract.h" // for INTERFACE
#define CLOSE_ENOUGH 500


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight)
   {
      upperRight = posUpperRight;
      ground = Ground(posUpperRight);
      howitzer.generatePosition(posUpperRight);
      ground.reset(howitzer.getPosition());
      projectile.reset();
      time = 0;
   }
   
   void display();
   void advance()
   {
       if (projectile.isFired() && !hitGround())
       {
           time += 0.5;
           projectile.advance(time);
       }
   }
   void input(const Interface* pUI);
   void fire() { time = 0;  projectile.fire(howitzer.getPosition(), time, howitzer.getElevation(), howitzer.getMuzzleVelocity()); }
   //void genPos();

   double computeDistance(Position pos1, Position pos2)
   {
       double x = pos1.getMetersX() - pos2.getMetersX();
       double y = pos1.getMetersY() - pos2.getMetersY();
       return sqrt((x * x) + (y * y));
   }

   bool hitGround()
   {
       Position bulletPos = projectile.getPos();
       double elevation = ground.getElevationMeters(bulletPos);
       if (bulletPos.getMetersY() < elevation)
       {
           if (computeDistance(bulletPos, ground.getTarget()) < CLOSE_ENOUGH)
           {
               howitzer.generatePosition(upperRight);
               ground.reset(howitzer.getPosition());
           }
           projectile.reset();
           return true;
       }
       
       return false;



   }

   void displayStats(const Position& posUpperRight)
   {
       double altitude;
       double distance;
       double speed;
       double hangTime;

       Position start = howitzer.getPosition();
       Position changingPos = projectile.getPos();
       distance = start.getMetersX() - changingPos.getMetersX();
       if (distance < 0) { distance = distance * -1; }
       altitude = start.getMetersY();

   }
  





private:
   Howitzer howitzer;
   Projectile projectile;
   Ground ground;
   Position upperRight;
   double time;
};
