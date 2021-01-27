
#ifndef velocity_h
#define velocity_h

#include <iostream>
class Velocity
{
private:
	float x;
	float y;
	
public:
	Velocity()
	{
		x = 0.0;
		y = 0.0;
	}
	
	Velocity(float x1, float y2)
	{
		x = x1;
		y = y2;
	}
	
	float getDx() { return x; }
	float getDy() { return y; }
	
	void setDx(float x);
	void setDy(float y);
	void addDx(float dx) { setDx(getDx() + dx); }
	void addDY(float dy) { setDy(getDy() + dy); }
};

#endif /* velocity_h */


