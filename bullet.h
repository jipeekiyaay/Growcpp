#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40



// Put your Bullet class here
#include <cmath>
#include <iostream>
#include <string>
#include "ship.h"
#include "flyingObject.h"



class Bullet : public FlyingObject
{
public:
	Bullet()
	{
		angle = 90;
		radius = 0;
		rotationRate = 0;
		alive = true;
		bulletSpeed = BULLET_SPEED;
		bulletFrames = 0;
	}
	virtual void draw()
	{
		drawDot(fPoint);
	}
	virtual void setRotationRate()
	{
		rotationRate += ROTATE_AMOUNT;
	}
	
	int getBulletFrames() const { return bulletFrames; }
	
	void fire(Point point, float angle);
	void combineVelocities(Velocity s);
	
	void countBulletFrames();
	
protected:
	float bulletSpeed;
	int bulletFrames;
};



#endif /* bullet_h */

