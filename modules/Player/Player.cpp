#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glu.h>

#include "Player.h"

Player::Player() : DrawableEntity()
{ }

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
}

//f = z
//q = x
//x = sin(q) cos(f)

//z = sin(q) sin(f)

//y = cos(q)
