#ifndef _INCLUDE_PLAYER_H_
#define _INCLUDE_PLAYER_H_

#include "modules/DrawableEntity/DrawableEntity.h"

class Player : public DrawableEntity
{
	public:
		Player();
		Player(Vector3D origin, Vector3D angles);
		~Player();
		void Draw();

	private:
};

#endif
