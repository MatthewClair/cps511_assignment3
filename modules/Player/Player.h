#ifndef _INCLUDE_PLAYER_H_
#define _INCLUDE_PLAYER_H_

#include <list>

#include "modules/Ship/Ship.h"
#include "modules/Projectile/Projectile.h"

class Player : public Ship
{
	public:
		Player();
		Player(Vector3D origin);
		~Player();
		void draw();

		void fire(std::list<Projectile>* projectiles);
};

#endif
