#ifndef _INCLUDE_DRAWABLEENTITY_H_
#define _INCLUDE_DRAWABLEENTITY_H_

#include "modules/Vector3D/Vector3D.h"

class DrawableEntity
{
	public:
		DrawableEntity();
		DrawableEntity(Vector3D origin, Vector3D angles);
		DrawableEntity(Vector3D origin, Vector3D angles, Vector3D velocity);
		~DrawableEntity();
		virtual void draw() = 0;

		void update();

	public:
		Vector3D origin;
		Vector3D angles;
		Vector3D velocity;
};

#endif
