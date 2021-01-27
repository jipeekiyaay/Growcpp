//
//  flyingObject.h
//  SKEET
//
//  Created by Justin Armstrong on 11/6/17.
//  Copyright © 2017 Justin Armstrong. All rights reserved.
//

#ifndef flyingObject_h
#define flyingObject_h

#include <iostream>
#include <string>
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

using namespace std;

class FlyingObject
{
public:
	FlyingObject()
	{
		alive = true;
	}
	// standard getters....
	Point getPoint() const { return fPoint; }
	Velocity getVelocity() const { return fVelocity; }
	bool isAlive() const { return alive; }
	int getRotationRate() const { return rotationRate; }
	int getRadius() const { return radius; }
	float getAngle() const { return angle; }
	
	
	// standard setters.....
	void setVelocity(Velocity v);
	void setPoint(Point p);
	void setAlive(bool a);
	void setRadius(int r);
	void setAngle(float a);
	
	
	// setters for game movement....
	void kill();
	void advance();
	virtual void draw() = 0;
	virtual void setRotationRate() = 0;
	void changeVelocityX(float x);
	void changeVelocityY(float y);
	
	
	
	
protected:
	Point fPoint;
	Velocity fVelocity;
	bool alive;
	int rotationRate;
	int radius;
	float angle;
};

#endif /* flyingObject_h */


