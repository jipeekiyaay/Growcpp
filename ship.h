#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define ANGLE_START 90
#define ANGLE_MAX 360
#define ANGLE_MIN 0


#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
#include <cmath>



// Put your Ship class here
class Ship : public FlyingObject
{
public:
	Ship()
	{
		this->fPoint = Point(random(-180, 180), random(-180, 180));
		this->alive = true;
		this->radius = SHIP_SIZE;
		this->thrust = false;
		this->angleVHorizontal = 0;
		this->angleVVerticle = 0;
		this->rotationRate = 0;
		this->angle = ANGLE_START;
		
	}
	
	bool getThrust() const { return thrust; }
	
	
	
	void setThurst(bool t);
	
	
	
	virtual void draw()
	{
		drawShip(fPoint, rotationRate, thrust);
	}
	
	void hit();
	
	virtual void setRotationRate()
	{
		rotationRate += ROTATE_AMOUNT;
	}
	
	void addThrust();
	
	void moveLeft();
	void moveRight();
	
	
private:
	
	bool thrust;
	float angleVHorizontal;
	float angleVVerticle;
	
	
};

#endif /* ship_h */

