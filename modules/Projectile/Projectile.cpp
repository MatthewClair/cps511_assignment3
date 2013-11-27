#include <GL/glut.h>

#include "Projectile.h"

Projectile::Projectile() : DrawableEntity()
{ }

Projectile::Projectile(Vector3D origin, Vector3D angles, Vector3D velocity,
		GLdouble radius, Colour c) : DrawableEntity(origin, angles, velocity)
{
	this->radius = radius;
	this->colour = c;

	this->timeExisted = 0;
	this->lifeSpan = 250;
	this->noLongerExists = false;
}

Projectile::~Projectile()
{ }

void Projectile::draw()
{
	glColor3ub(colour.red, colour.green, colour.blue);

	glPushMatrix();
		glTranslated(origin.x, origin.y, origin.z);

		glutSolidSphere(radius, 16, 16);
	glPopMatrix();
}

void Projectile::update()
{
	DrawableEntity::update();

	timeExisted++;
	if (timeExisted >= lifeSpan) {
		noLongerExists = true;
	}
}
