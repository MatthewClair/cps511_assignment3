#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glu.h>

#include "Player.h"

Player::Player() : DrawableEntity()
{
	origin = {0, 0, 0};
	angles = {0, 0, 0};
	velocity = {0, 0, 0};
}

Player::Player(Vector3D origin, Vector3D angles) :
	DrawableEntity(origin, angles)
{
	velocity = {0, 0, 0};

	fireDelay = 25;
	maxSpeed = 5;
	timeSinceLastFired = fireDelay;
}

Player::~Player()
{ }

void Player::draw()
{
	gluLookAt(origin.x, origin.y, origin.z,
			//origin.x - std::sin(M_PI/180 * angles.y),
			//0,
			//origin.z - std::cos(M_PI/180 * angles.y),
			origin.x, origin.y, origin.z - 1,
			0, 1, 0);

	//x = sin(q) cos(f)

	//z = sin(q) sin(f)

	//y = cos(q)

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

		//crosshair-->
		glVertex3d(origin.x - .01, origin.y + .1, origin.z - 5);
		glVertex3d(origin.x - .01, origin.y - .1, origin.z - 5);
		glVertex3d(origin.x + .01, origin.y - .1, origin.z - 5);
		glVertex3d(origin.x + .01, origin.y + .1, origin.z - 5);

		glVertex3d(origin.x - .1, origin.y + .01, origin.z - 5);
		glVertex3d(origin.x - .1, origin.y - .01, origin.z - 5);
		glVertex3d(origin.x + .1, origin.y - .01, origin.z - 5);
		glVertex3d(origin.x + .1, origin.y + .01, origin.z - 5);
		//<--

	glEnd();
}

void Player::accelerate(Player::Direction dir)
{
	switch (dir)
	{
		case LEFT:
			velocity.x -= .1;
			break;
		case RIGHT:
			velocity.x += .1;
			break;
		case UP:
			velocity.y += .1;
			break;
		case DOWN:
			velocity.y -= .1;
			break;
	}

	double vMagnitude = (velocity.x * velocity.x) + (velocity.y * velocity.y);
	if(vMagnitude > maxSpeed*maxSpeed)
	{
		double scaleRatio = std::sqrt(vMagnitude)/maxSpeed;
		velocity.x /= scaleRatio;
		velocity.y /= scaleRatio;
	}
}

void Player::brake()
{
	velocity.x *= .92;
	velocity.y *= .92;
	velocity.z *= .92;

	if (velocity.x < .01 && velocity.x > -0.01) {
		velocity.x = 0;
	}

	if (velocity.y < .01 && velocity.y > -0.01) {
		velocity.y = 0;
	}

	if (velocity.z < .01 && velocity.z > -0.01) {
		velocity.z = 0;
	}
}

void Player::fireProjectiles(std::list<Projectile>* projectiles)
{
	if (timeSinceLastFired >= fireDelay) {
		//Vector3D pVelocity(velocity.x, velocity.y, velocity.z - 5);
		Vector3D pVelocity(0, 0, -5);
		Colour pColour(255, 0, 0);
		double pRadius = 3;

		Vector3D o1(origin.x - 15, origin.y, origin.z);
		Vector3D o2(origin.x + 15, origin.y, origin.z);

		Projectile p1(o1, angles, pVelocity, pRadius, pColour);
		Projectile p2(o2, angles, pVelocity, pRadius, pColour);

		projectiles->push_back(p1);
		projectiles->push_back(p2);

		timeSinceLastFired = 0;
	}
}

void Player::update()
{
	timeSinceLastFired++;

	DrawableEntity::update();
}
