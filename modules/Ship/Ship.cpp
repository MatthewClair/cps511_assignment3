#define _USE_MATH_DEFINES
#include <cstdlib>
#include <limits.h>
#include <cmath>
#include <GL/glu.h>

#include "Ship.h"

Ship::Ship() : DrawableEntity()
{ }

Ship::Ship(Vector3D origin) :
	DrawableEntity(origin)
{
	fireDelay = 25;
	maxSpeed = 5;
	timeSinceLastFired = fireDelay;
	boundingBox[0] = {  75.0,  25.0,  50.0 };
	boundingBox[1] = { -75.0, -25.0, -50.0 };
}

Ship::~Ship()
{ }

void Ship::accelerate(Ship::Direction dir)
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

	double speed = (velocity.x * velocity.x) + (velocity.y * velocity.y);
	if (speed > maxSpeed*maxSpeed)
	{
		double scaleRatio = std::sqrt(speed)/maxSpeed;
		velocity.x /= scaleRatio;
		velocity.y /= scaleRatio;
	}
}

void Ship::update()
{
	timeSinceLastFired++;

	DrawableEntity::update();
}

void Ship::brake()
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
