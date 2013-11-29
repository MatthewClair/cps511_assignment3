#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>

#include "World.h"
#include "global.h"

World::World() : DrawableEntity()
{
	quadric = gluNewQuadric();
	gluQuadricOrientation(quadric, GLU_INSIDE);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	this->radius = 10000;
}

World::~World()
{
	free(quadric);
}

void World::draw()
{
	glColor3ub(0, 0, 64);

	glPushMatrix();
		glTranslated(ThePlayer.origin.x, ThePlayer.origin.y, ThePlayer.origin.z);
		gluSphere(quadric, 4000, 32, 16);
	glPopMatrix();
}

double World::getRadius()
{
	return this->radius;
}
