#ifndef _INCLUDE_DRAWABLEENTITY_H_
#define _INCLUDE_DRAWABLEENTITY_H_

#include "modules/Vector3D/Vector3D.h"

class DrawableEntity
{
	public:
		DrawableEntity();
		DrawableEntity(Vector3D origin);
		DrawableEntity(Vector3D origin,
				Vector3D boxCoord1, Vector3D boxCoord2);
		DrawableEntity(Vector3D origin, Vector3D velocity);
		DrawableEntity(Vector3D origin, Vector3D velocity,
				Vector3D boxCoord1, Vector3D boxCoord2);
		~DrawableEntity();
		virtual void draw() = 0;

		void update();
		void drawBBox();
		void setOrigin(Vector3D newOrigin);
		bool isColliding(const DrawableEntity &other);

	public:
		Vector3D origin;
		Vector3D velocity;
		Vector3D boundingBox[2];
};

#endif
