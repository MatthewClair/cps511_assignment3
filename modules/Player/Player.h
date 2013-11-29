#ifndef _INCLUDE_PLAYER_H_
#define _INCLUDE_PLAYER_H_

#include <list>

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Projectile/Projectile.h"

class Player : public DrawableEntity
{
	public:
		enum Direction{ LEFT, RIGHT, UP, DOWN };

	public:
		Player();
		Player(Vector3D origin);
		~Player();
		void draw();
		void update();

		void accelerate(Direction dir);
		void brake();

		void fireProjectiles(std::list<Projectile>* projectiles);

	private:
		double maxSpeed;
		int fireDelay;
		int timeSinceLastFired;
};

#endif
