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

		Vector3D v[3] = {
			{ 150.0, 0.0,  0.0 },
			{ 150.0, 0.0, 50.0 },
			{   0.0, 0.0, 50.0 },
		};
		Quad q(v[0], v[1], v[2]);
		q.draw();

		Vector3D v2[3] = {
			{   0.0, 50.0, 0.0 },
			{ 150.0, 50.0, 0.0 },
			{ 150.0,  0.0, 0.0 },
		};
		Quad q2(v2[0], v2[1], v2[2]);
		q2.draw();

		glPushMatrix();
			glTranslated(0.0, 50.0, 0.0);
			Vector3D v3[3] = {
				{   0.0, 0.0, 50.0 },
				{ 150.0, 0.0, 50.0 },
				{ 150.0, 0.0,  0.0 }
			};
			Quad q3(v3[0], v3[1], v3[2]);
			q3.draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0.0, 0.0, 50.0);
			Vector3D v4[3] = {
				{ 150.0,  0.0, 0.0 },
				{ 150.0, 50.0, 0.0 },
				{   0.0, 50.0, 0.0 },
			};
			Quad q4(v4[0], v4[1], v4[2]);
			q4.draw();
		glPopMatrix();

		glutSolidTeapot(50.0);
	glPopMatrix();
}

