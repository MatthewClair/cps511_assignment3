#ifndef _INCLUDE_LIGHT_H_
#define _INCLUDE_LIGHT_H_

#include <GL/gl.h>

#include "modules/DrawableEntity/DrawableEntity.h"

class Light : public DrawableEntity
{
	public:
		Light();
		Light(Vector3D origin, Vector3D angles,
				GLenum light, const float *diffuse);
		~Light();
		void Draw();
	
	private:
		GLenum light;

		GLfloat diffuse[4];
		GLfloat specular[4] = {0, 0, 0, 1};
};

#endif

