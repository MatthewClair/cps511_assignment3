#include "Enemy.h"

Enemy::Enemy() : DrawableEntity()
{ }

Enemy::Enemy(Vector3D origin, Vector3D angles) :
	DrawableEntity(origin, angles)
{ }

Enemy::~Enemy()
{ }

void Enemy::Draw()
{
	glColor3d(0.6, 0.3, 0.6);
	glPushMatrix();

	glTranslated(origin.x, origin.y, origin.z);
	glRotated(angles.x, 1.0, 0.0, 0.0);
	glRotated(angles.y, 0.0, 1.0, 0.0);
	glRotated(angles.z, 0.0, 0.0, 1.0);

	glutSolidTeapot(50.0);

	glPopMatrix();
}

