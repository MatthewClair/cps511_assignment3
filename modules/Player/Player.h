#ifndef _INCLUDE_PLAYER_H_
#define _INCLUDE_PLAYER_H_

#include <list>

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Projectile/Projectile.h"

class Player : public DrawableEntity
{
	public:
		Player();
		Player(Vector3D origin, Vector3D angles);
		~Player();
		void draw();

		void accelerateLeft();
		void accelerateRight();
		void brake();

		void fireProjectiles(std::list<Projectile>* projectiles);

	private:
};

#endif
