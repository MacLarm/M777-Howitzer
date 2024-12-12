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
}
