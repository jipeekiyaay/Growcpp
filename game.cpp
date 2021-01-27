/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <vector>
#include <math.h>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "game.h"

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
: topLeft(tl), bottomRight(br)
{
	// Set up the initial conditions of the game
    gameOn = true;
	score = 0;
	ship = new Ship();
	asteroids.clear();
	for (int i = 0; i < 5; i++) {
		BigRock* bRock;
		bRock = new BigRock();
		asteroids.push_back(bRock);
	}
	
}

Game :: ~Game()
{
	// delete vector items and clear vectors...
	if (!asteroids.empty()) {
		for (int i = 0; i < asteroids.size(); i++) {
			delete asteroids[i];
		}
		asteroids.clear();
	}
	
	if (!bullets.empty()) {
		bullets.clear();
	}
	
	
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game:: advance()
{
	advanceRocks();
	advanceBullets();
	advanceShip();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
		}
	}
}

/***************************************
 * GAME :: ADVANCE SHIP
 * Move the ship.
 ***************************************/

void Game::advanceShip()
{
	ship->advance();
}

/**************************************************************************
 * GAME :: ADVANCE ROCKS
 *
 If there is a group of rocks, and it's alive, advance it
 *
 **************************************************************************/
void Game:: advanceRocks()
{
	if (asteroids.empty()) {
		// start with the 5 big rocks
		asteroids.clear();
		for (int i = 0; i < 5; i++) {
			BigRock* bRock;
			bRock = new BigRock();
			asteroids.push_back(bRock);
		}
	}
	
	else {
		for (int i = 0; i < asteroids.size(); i++) {
			if (asteroids[i]->isAlive()) {
				asteroids[i]->advance();
			}
		}
	}
}



/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
	// Change the direction of the ship
	if (ui.isLeft())
	{
		ship->moveLeft();
		
	}
	
	if (ui.isRight())
	{
		ship->moveRight();
	}
	
	if (ui.isUp()) {
		ship->setThurst(true);
		ship->getThrust();
		ship->addThrust();
	}
	
	// Check for "Spacebar
	if (ui.isSpace())
	{
		Bullet newBullet;
		newBullet.fire(ship->getPoint(), ship->getAngle());
		newBullet.combineVelocities(ship->getVelocity());
		bullets.push_back(newBullet);
		
		
	}
	
}


/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	if (!asteroids.empty()) {
		// draw our big rocks...
		for (int a = 0; a < asteroids.size(); a++) {
			if (asteroids[a]->isAlive()) {
				asteroids[a]->draw();
				asteroids[a]->setRotationRate();
			}
		}
	}
	
	// draw our ship
	if (ship->isAlive()) {
		ship->draw();
	}
    else {
        gameOn = false;
        drawText(ship->getPoint(), "GAME_OVER");
        drawText(ship->getPoint(), "2");
                 
        
	}
	 
	drawNumber(topLeft, score);
	
	// draw our bullets...
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive() && bullets[i].getBulletFrames() <= 40 && ship->isAlive())
		{
			bullets[i].draw();
			bullets[i].countBulletFrames();
		}
	}
}

void Game :: checkBulletImpact()
{
	bulletImpact = 0;
	if (!asteroids.empty() && !bullets.empty() && ship->isAlive()) {
		
		for (int i = 0; i < asteroids.size(); i++) {
			
			for (int b = 0; b < bullets.size(); b++) {
				
				if (asteroids[i]->isAlive() && bullets[b].isAlive()) {
					
					bulletImpact = getClosestDistance(*(asteroids[i]), bullets[b]);
					
					if (bulletImpact <= 17 && asteroids[i]->getRadius() == 16) {
						bullets[b].setAlive(false);
						asteroids[i]->setAlive(false);
						drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
						asteroids[i]->breakUp(asteroids);
						drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
						score = score + 1;
					}
					else {
						if (bulletImpact <= 9 && asteroids[i]->getRadius() == 8) {
							bullets[b].setAlive(false);
							asteroids[i]->setAlive(false);
							drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
							asteroids[i]->breakUp(asteroids);
							drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
							cout << "hit a medium rock!" << endl;
							score = score + 3;
						}
						else {
							if (bulletImpact <= 5 && asteroids[i]->getRadius() == 4) {
								bullets[b].setAlive(false);
								asteroids[i]->setAlive(false);
								drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
								score = score + 10;
							}
							else {
							}
							
						}
						
					}
					
				}
				
			}
			
		}
		
	}
}
void Game :: handleCollisions()
{
	checkBulletImpact();
	checkShipImpact();
	cleanUpZombies();
}



void Game :: checkShipImpact()
{
	shipImpact = 0;
	
	for (int i = 0; i < asteroids.size(); i++) {
		
		if (asteroids[i]->isAlive() && ship->isAlive()) {
			
			shipImpact = getClosestDistance(*(asteroids[i]), *ship);
			
			if (shipImpact <= 17 && asteroids[i]->getRadius() == 16) {
				ship->setAlive(false);
				drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
			}
			else {
				if (shipImpact <= 9 && asteroids[i]->getRadius() == 9) {
					ship->setAlive(false);
					drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
				}
				else {
					if (shipImpact <= 5 && asteroids[i]->getRadius() == 4) {
						ship->setAlive(false);
						drawLanderFlames(asteroids[i]->getPoint(), true, true, true);
						
					}
					
				}
				
			}
			
		}
		
	}
	
}


void Game :: cleanUpZombies()
{
	for (int i = 0; i < asteroids.size(); ) {
		if (!asteroids[i]->isAlive()) {
			delete asteroids[i];
			asteroids.erase(asteroids.begin() + i);
		}
		else {
			i++;
		}
	}
	
	for (int b = 0; b < bullets.size(); ) {
		if (!bullets[b].isAlive()) {
			bullets.erase(bullets.begin() + b);
		}
		else {
			b++;
		}
	}
}



// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
	// find the maximum distance traveled
	float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
	dMax = max(dMax, abs(obj2.getVelocity().getDx()));
	dMax = max(dMax, abs(obj2.getVelocity().getDy()));
	dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
	
	float distMin = std::numeric_limits<float>::max();
	for (float i = 0.0; i <= dMax; i++)
	{
		Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
						 obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
		Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
						 obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
		
		float xDiff = point1.getX() - point2.getX();
		float yDiff = point1.getY() - point2.getY();
		
		float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
		
		distMin = min(distMin, distSquared);
	}
	
	return sqrt(distMin);
}
