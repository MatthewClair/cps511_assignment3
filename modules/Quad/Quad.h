#ifndef _INCLUDE_QUAD_H_
#define _INCLUDE_QUAD_H_

#include <GL/gl.h>

#include "modules/Vector3D/Vector3D.h"

class Quad
{
	public:
		Quad();
		Quad(Vector3D p0, Vector3D p1, Vector3D p2);
		~Quad();
		void draw();

	private:
		Vector3D p[3];
		Vector3D normal;
		void calculateNormal();
};

#endif
