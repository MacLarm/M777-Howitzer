/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;
/****************************************
 * DRAW
 * Draw all the the projectiles on flightpath
 ***************************************/
void Projectile::drawProjectile(ogstream & gout)
{
   if (flightPath.size() > 0) {
      // loop through flight path using an iterator
      for (auto it = flightPath.begin(); it != flightPath.end(); ++it)
      {
         // for each item, draw it.
         gout.drawProjectile(it->pos);
      }
   }
   else
      return;
}
