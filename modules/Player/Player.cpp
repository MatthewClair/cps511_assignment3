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
{ }

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
}

void Player::accelerateLeft()
{
	if (velocity.x > -5) {
		velocity.x -= 1;
	}
}

void Player::accelerateRight()
{
	if (velocity.x < 5) {
		velocity.x += 1;
	}
}

void Player::brake()
{
	velocity.x *= .98;
	velocity.y *= .98;
	velocity.z *= .98;

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
	Vector3D pVelocity(velocity.x, velocity.y, velocity.z - 10);
	Colour pColour(255, 0, 0);
	double pRadius = 3;

	Vector3D o1(origin.x - 15, origin.y, origin.z);
	Vector3D o2(origin.x + 15, origin.y, origin.z);

	Projectile p1(o1, angles, pVelocity, pRadius, pColour);
	Projectile p2(o2, angles, pVelocity, pRadius, pColour);

	projectiles->push_back(p1);
	projectiles->push_back(p2);
}
