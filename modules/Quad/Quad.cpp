#include "Quad.h"

Quad::Quad()
{ }

Quad::Quad(Vector3D p0, Vector3D p1, Vector3D p2)
{
	this->p[0] = p0;
	this->p[1] = p1;
	this->p[2] = p2;
	calculateNormal();
}

Quad::~Quad()
{ }

void Quad::calculateNormal()
{
	normal = p[0].crossProduct(p[1]);
}

void Quad::draw()
{
	float v[3];
	glBegin(GL_QUADS);
		normal.getFloatArray(v);
		glNormal3fv(v);
		glVertex3f(0.0, 0.0, 0.0);
		p[0].getFloatArray(v);
		glVertex3fv(v);
		p[1].getFloatArray(v);
		glVertex3fv(v);
		p[2].getFloatArray(v);
		glVertex3fv(v);
	glEnd();
}
