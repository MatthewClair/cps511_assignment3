#include <GL/glut.h>

#include "Projectile.h"

Projectile::Projectile() : DrawableEntity()
{ }

Projectile::Projectile(Vector3D origin, Vector3D velocity,
		GLdouble radius, Colour c) : DrawableEntity(origin, velocity)
{
	this->radius = radius;
	colour = c;

	timeExisted = 0;
	lifeSpan = 500;
	noLongerExists = false;

	boundingBox[0] = { radius, radius, radius };
	boundingBox[1] = { -radius, -radius, -radius };
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
