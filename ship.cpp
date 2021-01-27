#include "ship.h"



void Ship:: setThurst(bool t)
{
	this->thrust = t;
}

void Ship:: moveLeft()
{
	rotationRate -= ROTATE_AMOUNT;
	if (rotationRate < 0) {
		rotationRate += 360;
	}
	angle -= ROTATE_AMOUNT;
	if (angle < 0) {
		angle += 360;
	}
	
}

void Ship:: moveRight()
{
	rotationRate += ROTATE_AMOUNT;
	if (rotationRate > 360) {
		rotationRate -= 360;
	}
	angle += ROTATE_AMOUNT;
	if (angle > 360) {
		angle -= 360;
	}
	
}

void Ship::addThrust()
{
	angleVHorizontal += THRUST_AMOUNT * (cos(M_PI / 180.0 * this->getAngle()));
	angleVVerticle += THRUST_AMOUNT * (sin(M_PI / 180.0 * this->getAngle()));
	this->fVelocity.setDx(angleVHorizontal);
	this->fVelocity.setDy(angleVVerticle);
}

