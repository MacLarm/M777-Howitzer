/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION

void Simulator::display()
{
   ogstream gout;
   ground.draw(gout);
   howitzer.draw(gout, 1);
//   projectile.drawProjectile(gout);
}

void Simulator::input(const Interface* pUI)
{
   // input to rotate howitzer
   if (pUI->isRight())
      howitzer.rotate(0.05);
   if (pUI->isLeft())
      howitzer.rotate(-0.05);
   
   // input to raise howitzer
   if (pUI->isUp())
      howitzer.raise(0.003);
   if (pUI->isDown())
      howitzer.raise(-0.003);
   
   // Open Fire!
   if (pUI->isSpace())
      this->fire();
   
}
