#include <GL/glut.h>

#include "Projectile.h"

Projectile::Projectile() : DrawableEntity()
{ }

Projectile::Projectile(Vector3D origin, Vector3D angles, Vector3D velocity,
		GLdouble radius, Colour c) : DrawableEntity(origin, angles, velocity)
{
	this->radius = radius;
	this->colour = c;
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
