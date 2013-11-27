#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>

#include "World.h"

World::World() : DrawableEntity()
{
	quadric = gluNewQuadric();
	gluQuadricOrientation(quadric, GLU_INSIDE);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	this->radius = 2000;
}

World::~World()
{
	free(quadric);
}

void World::draw()
{
	glColor3ub(0, 0, 64);

	gluSphere(quadric, radius, 32, 16);
}

double World::getRadius()
{
	return this->radius;
}
