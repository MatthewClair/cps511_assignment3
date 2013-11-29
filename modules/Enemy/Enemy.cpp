#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "Enemy.h"
#include "global.h"

Enemy::Enemy() : DrawableEntity()
{
	enemyType = std::rand() % 2;
	attackType = std::rand() % 2;
	isAlive = true;
	attacking = false;
	originalPos.x = origin.x;
	originalPos.y = origin.y;
	originalPos.z = origin.z;

	this->generateBoundingBox();
}

Enemy::Enemy(Vector3D origin) :
	DrawableEntity(origin)
{
	enemyType = std::rand() % 2;
	attackType = std::rand() % 2;
	isAlive = true;
	attacking = false;
	originalPos.x = origin.x;
	originalPos.y = origin.y;
	originalPos.z = origin.z;

	this->generateBoundingBox();
}

Enemy::~Enemy()
{ }

void Enemy::generateBoundingBox()
{
	switch (enemyType)
	{
		case 0:
			boundingBox[0] = {  75,  25.0,  50.0 };
			boundingBox[1] = { -75, -25.0, -65.0 };
			break;
		case 1:
			boundingBox[0] = {  75.0,  35.0,  75.0 };
			boundingBox[1] = { -75.0, -35.0, -75.0 };
			break;
	}
}

void Enemy::draw()
{
	glColor3d(0.6, 0.3, 0.6);

	glPushMatrix();
		glTranslated(origin.x, origin.y, origin.z);
		switch (enemyType)
		{
			case 0:
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
				break;
			case 1:
				glutSolidSphere(35.0, 32, 16);
				glPushMatrix();
					glScaled(75, 20, 75);
					glutSolidSphere(1.0, 32, 16);
				glPopMatrix();
				break;
		}
	glPopMatrix();
}

void Enemy::update()
{
	velocity.z = 0;

	if (origin.z > ThePlayer.origin.z) {
		attacking = false;
		velocity.x = 0;
		velocity.y = 0;
		origin.x = originalPos.x;
		origin.y = originalPos.y;
		origin.z = originalPos.z-1000;
	}

	if (origin.z < originalPos.z) {
		velocity.z = 1;
	}

	if (attacking) {
		specialMovement();
	}

	DrawableEntity::update();
}

void Enemy::specialMovement()
{
	velocity.z = 2;

	switch (attackType) {
		case 1:
			velocity.x = 2 * std::cos(tick/100.0);
			velocity.y = 2 * std::sin(tick/100.0);
			break;
		case 2:
			break;
	}
}
