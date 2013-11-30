#ifndef _INCLUDE_WORLD_H_
#define _INCLUDE_WORLD_H_

#include <GL/glu.h>

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Image/Image.h"

class World : public DrawableEntity
{
	public:
		World();
		~World();
		void draw();

		double getRadius();

	private:
		GLUquadric *quadric;
		GLuint textureID;
		double radius;
		Image image;
};

#endif
