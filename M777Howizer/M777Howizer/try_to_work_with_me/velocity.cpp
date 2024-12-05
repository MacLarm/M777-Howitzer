/***********************************************************************
* Source File:
* VELOCITY
* Author:
* <your name here>
* Summary:
* Everything we need to know about speed
************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h> // for sqrt()
#include <cassert>

/*********************************************
* VELOCITY : ADD
* v = v_0 + a t
*********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
	dx += (acceleration.getDDX() * time);
	dy += (acceleration.getDDY() * time);
}


/*********************************************
* VELOCITY : GET SPEED
* find the magnitude of velocity
* dx
* +-------/
* |      /
* |dy   /
* |    / speed or magnitude
* | a /
* |  /
* | /
* _____________
* speed = \/ dx^2 + dy^2
*********************************************/
double Velocity::getSpeed() const
{
	// A^2 + B^2 = C^2
	double velocity = (getDX() * getDX()) + (getDY() * getDY()); //A^2 + B^2
	velocity = sqrt(velocity); //square root of C^2
	return velocity;
}

/*********************************************
* VELOCITY : SET
* dx
* +-------/
* |      /
* |dy   /
* |    /speed or magnitude
* | a /
* |  /
* | /
* dy = speed cos(a)
* dx = speed sin(a)
*********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
	double radians = angle.getRadians();
	dx = sin(radians) * magnitude; // get the x factor
	dy = cos(radians) * magnitude; // get the y factor
}


/************************************************
* Velocity :: GET ANGLE
* Determine the direction things are going
* where 0 is up. This returns angle (clockwise) in radians
* dx
* +-------/
* |      /
* |dy   /
* |    / speed
* | a /
* |  /
* | /
*
* a = atan2(dx, dy)
* dx = cos(a) x speed
* dy = sin(a) x speed
************************************************/
Angle Velocity::getAngle() const
{
	double angleInRadians = atan2(dy, dx); // atan2 gives the angle in radians
	return Angle(angleInRadians);
}
