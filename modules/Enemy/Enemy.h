#ifndef _INCLUDE_ENEMY_H_
#define _INCLUDE_ENEMY_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "modules/DrawableEntity/DrawableEntity.h"

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