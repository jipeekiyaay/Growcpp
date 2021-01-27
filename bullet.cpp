#include "bullet.h"



// Put your bullet methods here


void Bullet::fire(Point point, float angle)
{
	float angleVHorizontal;
	float angleVVerticle;
	this->fPoint.setX(point.getX());
	this->fPoint.setY(point.getY());
	angleVHorizontal = bulletSpeed * (cos(M_PI / 180.0 * angle));
	angleVVerticle = bulletSpeed * (sin(M_PI / 180.0 * angle));
	this->fVelocity.setDx(angleVHorizontal);
	this->fVelocity.setDy(angleVVerticle);
}

void Bullet::combineVelocities(Velocity s)
{
	this->fVelocity.addDx(s.getDx());
	this->fVelocity.addDY(s.getDy());
}

void Bullet::countBulletFrames()
{
	bulletFrames++;
	
	if (bulletFrames > 40) {
		this->kill();
	}
}

