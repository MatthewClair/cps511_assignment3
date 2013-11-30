#include <GL/gl.h>
#include <stdio.h>

#include "modules/DrawableEntity/DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
	origin = {0, 0, 0};
	velocity = {0, 0, 0};
}

DrawableEntity::DrawableEntity(Vector3D origin)
{
	this->origin = origin;
	velocity = {0, 0, 0};
}

DrawableEntity::DrawableEntity(Vector3D origin,
		Vector3D boxCoord1, Vector3D boxCoord2)
{
	this->origin = origin;
	this->velocity = velocity;
	boundingBox[0] = { boxCoord1.x, boxCoord1.y, boxCoord1.z };
	boundingBox[1] = { boxCoord2.x, boxCoord2.y, boxCoord2.z };
}

DrawableEntity::DrawableEntity(Vector3D origin, Vector3D velocity)
{
	this->origin = origin;
	this->velocity = velocity;
}

DrawableEntity::DrawableEntity(Vector3D origin, Vector3D velocity,
		Vector3D boxCoord1, Vector3D boxCoord2)
{
	this->origin = origin;
	this->velocity = velocity;
	boundingBox[0] = { boxCoord1.x, boxCoord1.y, boxCoord1.z };
	boundingBox[1] = { boxCoord2.x, boxCoord2.y, boxCoord2.z };
}

DrawableEntity::~DrawableEntity()
{ }

void DrawableEntity::update()
{
	origin += velocity;
}

void DrawableEntity::drawBBox()
{
	glColor3d(1, 1, 1);
	glPushMatrix();
		glTranslated(origin.x, origin.y, origin.z);
		glBegin(GL_QUADS);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[0].z);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[1].z);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[1].z);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[0].z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[1].z);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[1].z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[1].z);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[1].z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[1].z);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[0].z);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[0].z);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[1].z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[0].z);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[0].z);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[0].z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3d(boundingBox[0].x, boundingBox[0].y, boundingBox[1].z);
			glVertex3d(boundingBox[0].x, boundingBox[1].y, boundingBox[1].z);
			glVertex3d(boundingBox[1].x, boundingBox[1].y, boundingBox[1].z);
			glVertex3d(boundingBox[1].x, boundingBox[0].y, boundingBox[1].z);
		glEnd();

	glPopMatrix();
}

void DrawableEntity::setOrigin(Vector3D newOrigin)
{
	this->origin = newOrigin;
}

bool DrawableEntity::isColliding(const DrawableEntity &other)
{
	for (short i = 0; i < 8; i++)
	{
		bool a = i & 1 << 0;
		bool b = i & 1 << 1;
		bool c = i & 1 << 2;
		if (boundingBox[0].x + origin.x >= other.boundingBox[a].x + other.origin.x &&
			   	boundingBox[1].x + origin.x <= other.boundingBox[a].x + other.origin.x &&
				boundingBox[0].y + origin.y >= other.boundingBox[b].y + other.origin.y &&
			   	boundingBox[1].y + origin.y <= other.boundingBox[b].y + other.origin.y &&
				boundingBox[0].z + origin.z >= other.boundingBox[c].z + other.origin.z &&
			   	boundingBox[1].z + origin.z <= other.boundingBox[c].z + other.origin.z)
		{
			return true;
		}
	}
	return false;
}
