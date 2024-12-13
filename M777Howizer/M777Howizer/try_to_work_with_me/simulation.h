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
   }
   
   void display();
   void advance() { projectile.advance(1); }
   void input(const Interface* pUI);
   void fire() { projectile.fire(howitzer.getPosition(), 1, howitzer.getElevation(), howitzer.getMuzzleVelocity()); }
   void genPos();
   

private:
   Howitzer howitzer;
   Projectile projectile;
   Ground ground;
};
