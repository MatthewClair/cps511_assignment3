#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "World.h"
#include "global.h"

World::World() : DrawableEntity()
{
	this->radius = 50;

	quadric = gluNewQuadric();
	image.loadImage("./res/crate.bmp");

	textureID = 0;
	glBindTexture(1, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.sizeX, image.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
	gluQuadricTexture(quadric, GL_TRUE);
}

World::~World()
{
	free(quadric);
}

void World::draw()
{
	glPushMatrix();
		glTranslated(ThePlayer.origin.x, ThePlayer.origin.y, ThePlayer.origin.z - 100);

		glBindTexture(GL_TEXTURE_2D, textureID);

		//gluQuadricOrientation(quadric, GLU_INSIDE);

		gluSphere(quadric, radius, 32, 16);
	glPopMatrix();
}

double World::getRadius()
{
	return this->radius;
}
