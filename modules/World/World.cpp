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
}

World::~World()
{
	free(quadric);
}

void World::draw()
{
	glColor3ub(0, 0, 64);

	gluSphere(quadric, 2000, 32, 16);
}
