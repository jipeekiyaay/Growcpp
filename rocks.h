#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include <vector>

using namespace std;


//   Rock class with member variables and functions
class Rock : public FlyingObject
{
public:
	Rock()
	{
		alive = true;
	}
	virtual void breakUp(vector<Rock*> &gameVector) = 0;
	virtual void setRockVelocity() = 0;
	virtual void draw()
	{
		return;
	}
	virtual void setRotationRate()
	{
		return;
	}
	virtual ~Rock() { }
};

//   SmallRock
class SmallRock : public Rock
{
public:
	SmallRock()
	{
		this->alive = true;
		this->radius = 4;
		
	}
	SmallRock(Point p, Velocity v)
	{
		this->fPoint = p;
		this->fVelocity = v;
		this->alive = true;
		this->radius = 4;
		
	}
	virtual ~SmallRock()
	{
		cout << "Deleting SMALL Rock" << endl;
	}
	virtual void draw()
	{
		drawSmallAsteroid(fPoint, rotationRate);
	}
	virtual void setRockVelocity()
	{
		return;
	}
	virtual void setRotationRate()
	{
		rotationRate = rotationRate + SMALL_ROCK_SPIN;
	}
	virtual void breakUp(vector<Rock*> &gameVector)
	{
		return;
	}
};

//   MediumRock
class MediumRock : public Rock
{
public:
	MediumRock()
	{
		this->alive = true;
		this->radius = 8;
		
	}
	MediumRock(Point p, Velocity v)
	{
		this->fPoint = p;
		this->fVelocity = v;
		this->alive = true;
		this->radius = 8;
		
	}
	virtual ~MediumRock()
	{
		cout << "Deleting MEDIUM Rock" << endl;
	}
	virtual void draw()
	{
		drawMediumAsteroid(fPoint, rotationRate);
	}
	virtual void setRockVelocity()
	{
		return;
	}
	virtual void setRotationRate()
	{
		rotationRate = rotationRate + MEDIUM_ROCK_SPIN;
	}
	
	virtual void breakUp(vector<Rock*> &gameVector)
	{
		SmallRock* s1Rock;
		s1Rock = new SmallRock(getPoint(), getVelocity());
		s1Rock->changeVelocityX(3.0);
		s1Rock->setRotationRate();
		
		SmallRock* s2Rock;
		s2Rock = new SmallRock(getPoint(), getVelocity());
		s2Rock->changeVelocityX(-3.0);
		s2Rock->setRotationRate();
		
		gameVector.push_back(s1Rock);
		gameVector.push_back(s2Rock);
	}
};


//   BigRock
class BigRock : public Rock
{
public:
	BigRock()
	{
		this->alive = true;
		this->fPoint = Point(random(-200, 200), random(-200, 200));
		this->radius = 16;
		this->fVelocity = Velocity(-0.5, -0.5);
	}
	virtual ~BigRock()
	{
		cout << "Deleting BIG Rock" << endl;
	}
	
	virtual void setRockVelocity()
	{
		return;
	}
	
	virtual void setRotationRate()
	{
		rotationRate = rotationRate + BIG_ROCK_SPIN;
	}
	
	
	virtual void draw()
	{
		drawLargeAsteroid(fPoint, rotationRate);
	}
	
	virtual void breakUp(vector<Rock*> &gameVector)
	{
		MediumRock* m1Rock;
		m1Rock = new MediumRock(this->getPoint(), this->getVelocity());
		m1Rock->changeVelocityY(1.0);
		m1Rock->setRotationRate();
		
		MediumRock* m2Rock;
		m2Rock = new MediumRock(getPoint(), getVelocity());
		m2Rock->changeVelocityY(-1.0);
		m2Rock->setRotationRate();
		
		SmallRock* sRock;
		sRock = new SmallRock(getPoint(), getVelocity());
		sRock->changeVelocityX(2.0);
		sRock->setRotationRate();
		
		gameVector.push_back(m1Rock);
		gameVector.push_back(m2Rock);
		gameVector.push_back(sRock);
	}
};



#endif /* rocks_h */

