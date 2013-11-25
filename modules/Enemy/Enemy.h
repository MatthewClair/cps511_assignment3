#ifndef _INCLUDE_ENEMY_H_
#define _INCLUDE_ENEMY_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Vector3D/Vector3D.h"
#include "modules/Quad/Quad.h"

class Enemy : public DrawableEntity
{
	public:
		Enemy();
		Enemy(Vector3D origin, Vector3D angles);
		~Enemy();
		void Draw();

	private:
};

#endif
