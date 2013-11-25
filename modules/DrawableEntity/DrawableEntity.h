#ifndef _INCLUDE_DRAWABLEENTITY_H_
#define _INCLUDE_DRAWABLEENTITY_H_

#include "modules/Vector3D/Vector3D.h"

class DrawableEntity
{
	public:
		DrawableEntity();
		DrawableEntity(Vector3D origin, Vector3D angles);
		~DrawableEntity();
		virtual void Draw() = 0;

	protected:
		Vector3D origin;
		Vector3D angles;
};

#endif
