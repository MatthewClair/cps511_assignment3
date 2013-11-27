#include "Enemy.h"
#include "global.h"

Enemy::Enemy() : DrawableEntity()
{ }

Enemy::Enemy(Vector3D origin, Vector3D angles) :
	DrawableEntity(origin, angles)
{ }

Enemy::~Enemy()
{ }

void Enemy::draw()
{
	glColor3d(0.6, 0.3, 0.6);

	glPushMatrix();
		glTranslated(origin.x, origin.y, origin.z);
		glRotated(angles.x, 1.0, 0.0, 0.0);
		glRotated(angles.y, 0.0, 1.0, 0.0);
		glRotated(angles.z, 0.0, 0.0, 1.0);

		glPushMatrix();
			glScaled(50.0, 50.0, 100.0);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslated(50.0, 0, -40.0);
			glScaled(50.0, 50.0, 50.0);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslated(-50.0, 0, -40.0);
			glScaled(50.0, 50.0, 50.0);
			glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();
}

void Enemy::update()
{
	velocity.z = 1;

	if (origin.z > ThePlayer.getOrigin().z) {
		origin.z = -TheWorld.getRadius()/2;
	}

	DrawableEntity::update();
}
