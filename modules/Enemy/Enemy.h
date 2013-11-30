#ifndef _INCLUDE_ENEMY_H_
#define _INCLUDE_ENEMY_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "modules/Ship/Ship.h"
#include "modules/Vector3D/Vector3D.h"

class Enemy : public Ship
{
	public:
		Enemy();
		Enemy(Vector3D origin);
		Enemy(Vector3D origin,
				Vector3D boxCoord1, Vector3D boxCoord2);
		~Enemy();
		void draw();
		void update(std::list<Projectile>* projectiles);
		void fire(std::list<Projectile>* projectiles);

		bool attacking;

	private:
		void generateBoundingBox();

	private:
		int enemyType;
		int attackType;

		Vector3D originalPos;

		void specialMovement();
};

#endif
