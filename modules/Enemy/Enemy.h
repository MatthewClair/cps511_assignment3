#ifndef _INCLUDE_ENEMY_H_
#define _INCLUDE_ENEMY_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "modules/World/World.h"
#include "modules/Player/Player.h"
#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Vector3D/Vector3D.h"
#include "modules/Quad/Quad.h"

class Enemy : public DrawableEntity
{
	public:
		Enemy();
		Enemy(Vector3D origin);
		Enemy(Vector3D origin,
				Vector3D boxCoord1, Vector3D boxCoord2);
		~Enemy();
		void draw();
		void update();

		bool attacking;
		bool isAlive;

	private:
		void generateBoundingBox();

	private:
		int enemyType;
		int attackType;

		Vector3D originalPos;

		void specialMovement();
};

#endif
