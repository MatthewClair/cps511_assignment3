#define _USE_MATH_DEFINES
#include <cstdlib>
#include <limits.h>
#include <cmath>
#include <GL/glu.h>

#include "Player.h"

Player::Player() : Ship()
{ }

Player::Player(Vector3D origin) :
	Ship(origin)
{
	isAlive = true;
	fireDelay = 25;
	maxSpeed = 5;
	timeSinceLastFired = fireDelay;
	boundingBox[0] = {  75.0,  25.0,  50.0 };
	boundingBox[1] = { -75.0, -25.0, -50.0 };
}

Player::~Player()
{ }

void Player::draw()
{
	gluLookAt(origin.x, origin.y, origin.z,
			origin.x, origin.y, origin.z - 1,
			0, 1, 0);

	glDisable(GL_LIGHTING);
	glColor3ub(150, 150, 150);
	glBegin(GL_QUADS);
		//top left bar
		glVertex3d(origin.x - 4   , origin.y + 5, origin.z - 2);
		glVertex3d(origin.x - 3.75, origin.y    , origin.z - 5);
		glVertex3d(origin.x - 3.5 , origin.y    , origin.z - 5);
		glVertex3d(origin.x - 3.75, origin.y + 5, origin.z - 2);

		//top right bar
		glVertex3d(origin.x + 4   , origin.y + 5, origin.z - 2);
		glVertex3d(origin.x + 3.75, origin.y    , origin.z - 5);
		glVertex3d(origin.x + 3.5 , origin.y    , origin.z - 5);
		glVertex3d(origin.x + 3.75, origin.y + 5, origin.z - 2);

		//bottom left bar
		glVertex3d(origin.x - 3.75, origin.y      , origin.z - 5);
		glVertex3d(origin.x - 3.75, origin.y - 2.2, origin.z - 4.5);
		glVertex3d(origin.x - 3.5 , origin.y - 2.2, origin.z - 4.5);
		glVertex3d(origin.x - 3.5 , origin.y      , origin.z - 5);

		//bottom right bar
		glVertex3d(origin.x + 3.75, origin.y      , origin.z - 5);
		glVertex3d(origin.x + 3.75, origin.y - 2.5, origin.z - 4.5);
		glVertex3d(origin.x + 3.5 , origin.y - 2.5, origin.z - 4.5);
		glVertex3d(origin.x + 3.5 , origin.y      , origin.z - 5);

		//bottom left panel
		glVertex3d(origin.x - 6   , origin.y - 2  , origin.z - 4);
		glVertex3d(origin.x	- 6   , origin.y - 4  , origin.z - 4);
		glVertex3d(origin.x       , origin.y - 4  , origin.z - 4.5);
		glVertex3d(origin.x       , origin.y - 2  , origin.z - 4.5);

		//bottom right panel
		glVertex3d(origin.x + 6   , origin.y - 2  , origin.z - 4);
		glVertex3d(origin.x	+ 6   , origin.y - 4  , origin.z - 4);
		glVertex3d(origin.x       , origin.y - 4  , origin.z - 4.5);
		glVertex3d(origin.x       , origin.y - 2  , origin.z - 4.5);

		//crosshair{{{
		glVertex3d(origin.x - .01, origin.y + .1, origin.z - 5);
		glVertex3d(origin.x - .01, origin.y - .1, origin.z - 5);
		glVertex3d(origin.x + .01, origin.y - .1, origin.z - 5);
		glVertex3d(origin.x + .01, origin.y + .1, origin.z - 5);

		glVertex3d(origin.x - .1, origin.y + .01, origin.z - 5);
		glVertex3d(origin.x - .1, origin.y - .01, origin.z - 5);
		glVertex3d(origin.x + .1, origin.y - .01, origin.z - 5);
		glVertex3d(origin.x + .1, origin.y + .01, origin.z - 5);
		//}}}

	glEnd();
	glEnable(GL_LIGHTING);
}

void Player::fire(std::list<Projectile>* projectiles)
{
	if (timeSinceLastFired >= fireDelay) {
		//Vector3D pVelocity(velocity.x, velocity.y, velocity.z - 5);
		Vector3D pVelocity(0, 0, -10);
		Colour pColour(255, 0, 0);
		double pRadius = 4;

		Vector3D o1(origin.x - 15, origin.y, origin.z);
		Vector3D o2(origin.x + 15, origin.y, origin.z);

		Projectile p1(o1, pVelocity, pRadius, pColour);
		Projectile p2(o2, pVelocity, pRadius, pColour);

		projectiles->push_back(p1);
		projectiles->push_back(p2);

		timeSinceLastFired = 0;
	}
}
