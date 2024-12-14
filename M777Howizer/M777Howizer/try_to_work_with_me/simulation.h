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
   
   // Constructor
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
   void advance();
   void input(const Interface* pUI);


private:
   
   // Fire the Howitzer.
   void fire() { time = 0;  projectile.fire(howitzer.getPosition(), time, howitzer.getElevation(), howitzer.getMuzzleVelocity()); }
   double computeDistance(Position pos1, Position pos2);
   bool hitGround();
   void displayStats();
   double getAltitude();
   
   Howitzer howitzer;
   Projectile projectile;
   Ground ground;
   Position upperRight;
   double time;
};
