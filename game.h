//
//  game.h
//  Asteroid Project
//
//  Created by Justin Armstrong on 12/6/17.
//  Copyright © 2017 Justin Armstrong. All rights reserved.
//

#ifndef game_h
#define game_h
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"
#include <vector>
#include <string>
#define CLOSE_ENOUGH 15

using namespace std;

class Game
{
public:
	/*********************************************
	 * Constructor
	 * Initializes the game
	 *********************************************/
	Game(Point tl, Point br);
	~Game();
	
	/*********************************************
	 * Function: handleInput
	 * Description: Takes actions according to whatever
	 *  keys the user has pressed.
	 *********************************************/
	void handleInput(const Interface & ui);
	
	/*********************************************
	 * Function: advance
	 * Description: Move everything forward one
	 *  step in time.
	 *********************************************/
	void advance();
	
	/*********************************************
	 * Function: draw
	 * Description: draws everything for the game.
	 *********************************************/
	void draw(const Interface & ui);
	
	/*********************************************
	 * Function: handle interactions
	 * Description: checks for collisions and
	 * makes necessary updates to game objects
	 *********************************************/
	vector<Rock*> asteroids;
	vector<Bullet> bullets;
	
	
	void handleCollisions();
	
protected:
	/*************************************************
	 * Private methods to help with the game logic.
	 *************************************************/
	void advanceBullets();
	void advanceRocks();
	void advanceShip();
	void checkShipImpact();
	void checkBulletImpact();
	void cleanUpZombies();
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
	
	
	Ship* ship;
	Point topLeft;
	Point bottomRight;
	int score;
	float bulletImpact;
	float shipImpact;
    bool gameOn;
	
};

#endif /* game_h */

