#ifndef _INCLUDE_PROJECTILE_H_
#define _INCLUDE_PROJECTILE_H_

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Colour/Colour.h"

class Projectile : public DrawableEntity
{
	public:
		Projectile();
		Projectile(Vector3D origin, Vector3D velocity, GLdouble radius, Colour c);
		~Projectile();
		void draw();
		void update();

		bool noLongerExists;

	private:
		GLdouble radius;
		Colour colour;

		int lifeSpan;
		int timeExisted;
};

#endif
