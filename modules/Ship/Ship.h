#ifndef _INCLUDE_SHIP_H_
#define _INCLUDE_SHIP_H_

#include <list>

#include "modules/DrawableEntity/DrawableEntity.h"
#include "modules/Projectile/Projectile.h"

class Ship : public DrawableEntity
{
	public:
		enum Direction{ LEFT, RIGHT, UP, DOWN };
		bool isAlive;

	public:
		Ship();
		Ship(Vector3D origin);
		~Ship();
		void update();

		void accelerate(Direction dir);
		void brake();

		virtual void draw() = 0;
		virtual void fire(std::list<Projectile>* projectiles) = 0;

	protected:
		double maxSpeed;
		int fireDelay;
		int timeSinceLastFired;
};

#endif
