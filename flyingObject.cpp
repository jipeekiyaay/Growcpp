//
//  flyingObject.cpp
//  SKEET
//
//  Created by Justin Armstrong on 11/6/17.
//  Copyright © 2017 Justin Armstrong. All rights reserved.
//
#include "flyingObject.h"

void FlyingObject::advance()
{
	
	fPoint.addX(fVelocity.getDx());
	fPoint.addY(fVelocity.getDy());
	
	// Now check for screen boundaries and
	// add code for correct wrap around
	
	if (fPoint.getX() > 200) {
		fPoint.setX(-200);
	}
	else if (fPoint.getX() < -200) {
		fPoint.setX(200);
	}
	else if (fPoint.getY() > 200) {
		fPoint.setY(-200);
	}
	else if (fPoint.getY() < -200) {
		fPoint.setY(200);
	}
}



void FlyingObject:: setPoint(Point p)
{
	this->fPoint = p;
}

void FlyingObject:: setVelocity(Velocity v)
{
	this->fVelocity = v;
}

void FlyingObject:: setAlive(bool a)
{
	this->alive = a;
}

void FlyingObject:: setRadius(int r)
{
	this->radius = r;
}

void FlyingObject:: setAngle(float a)
{
	this->angle = a;
}

void FlyingObject:: kill()
{
	setAlive(false);
}

void FlyingObject::changeVelocityX(float x)
{
	this->fVelocity.setDx(this->fVelocity.getDx() + x);
}

void FlyingObject::changeVelocityY(float y)
{
	this->fVelocity.setDy(this->fVelocity.getDy() + y);
}



