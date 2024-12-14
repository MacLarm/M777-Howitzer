/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION
using namespace std;

/******************************************
 * SIMULATOR: DISPLAY
 * Display all of the objects in the simulation.
 ******************************************/
void Simulator::display()
{
   ogstream gout;
   ground.draw(gout);
   howitzer.draw(gout, time);
   projectile.drawProjectile(gout);
//   displayStats();
   
    double altitude = 0;
    double distance = 0;
    double speed = 0;
    double hangTime = 0;
   
   if (time > 0) // we got isues in here when it resets.
   {
      altitude = getAltitude();
      distance = computeDistance(howitzer.getPosition(), projectile.getPos());
      speed = projectile.getVelocity();
      hangTime = time;
   }
   else
   {
      altitude = 0;
      distance = 0;
      speed = 0;
      hangTime = 0;
   }
   
   gout.drawText(Position(700,500), "Altitude: "); // its only drawing in the bottom for some reason.
}

// May delete this function completely.
//   |
//  \|/
//   V

/******************************************
 * SIMULATOR: DISPLAY STATS
 * Display the stats of the howitzer and projectile.
 ******************************************/
void Simulator::displayStats()
{
   ogstream gout;
    double altitude = 0;
    double distance = 0;
    double speed = 0;
    double hangTime = 0;
   
   if (time > 0)
   {
      altitude = getAltitude();
      distance = computeDistance(howitzer.getPosition(), projectile.getPos());
      speed = projectile.getVelocity();
      hangTime = time;
   }
   else
   {
      altitude = 0;
      distance = 0;
      speed = 0;
      hangTime = 0;
   }
   
   gout.drawText(Position(0,500), "Altitude: ");
   
//   gout.setf(ios::fixed | ios::showpoint);
//   gout.precision(1);
//   
//   gout << "Altitude: " << altitude << "s\n";
//   gout << "Distance: " << distance << "s\n";
//   gout << "Speed: "    << speed    << "s\n";
//   gout << "Time: "     << hangTime << "s\n";
}

/******************************************
 * SIMULATOR: ADANCE
 * Move the projectile.
 ******************************************/
void Simulator::advance()
{
    if (projectile.isFired() && !hitGround())
    {
        time += 0.5;
        projectile.advance(time);
    }
}

/******************************************
 * SIMULATOR: INPUT
 * Take the input from the user and apply it to the simulation.
 ******************************************/
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
   if (pUI->isSpace() && !projectile.isFired())
      this->fire();
}

/******************************************
 * SIMULATOR: Compute Distance
 * Find the distance between two points.
 ******************************************/
double Simulator::computeDistance(Position pos1, Position pos2)
{
    double x = pos1.getMetersX() - pos2.getMetersX();
    double y = pos1.getMetersY() - pos2.getMetersY();
    return sqrt((x * x) + (y * y)); // Pythagorean theorem?? Lets go baby!
}

/******************************************
 * SIMULATOR: HIT GROUND
 * See if the bullet has hit the ground.
 ******************************************/
bool Simulator::hitGround()
{
   Position bulletPos = projectile.getPos(); // where the bullet is.
   double elevation = ground.getElevationMeters(bulletPos); // How high off the ground the bullet is.
   // see if we are below the ground.
   if (bulletPos.getMetersY() < elevation)
   {
      // See if we hit the target.
      if (computeDistance(bulletPos, ground.getTarget()) < CLOSE_ENOUGH)
      {
         // do some resets.
         howitzer.generatePosition(upperRight);
         ground.reset(howitzer.getPosition());
      }
      // reset the projectile for the next shot.
      projectile.reset();
      return true;
   }
   // We are still above the ground.
   return false;
}

/******************************************
 * SIMULATOR: HIT GROUND
 * See if the bullet has hit the ground.
 ******************************************/
double Simulator::getAltitude()
{
   double altitude = ground.getElevationMeters(projectile.getPos());
   return altitude;
}
