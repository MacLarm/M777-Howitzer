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


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight)
   {
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


   bool hitGround()
   {
       Position bulletPos = projectile.getPos();
       double elevation = ground.getElevationMeters(bulletPos);
       if (elevation <= 0) return true;
       
       return false;
   }





private:
   Howitzer howitzer;
   Projectile projectile;
   Ground ground;
   double time;
};
