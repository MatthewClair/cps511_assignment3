#include "Player.h"

Player::Player() : DrawableEntity()
{ }

Player::Player(Vector3D origin, Vector3D angles) :
	DrawableEntity(origin, angles)
{ }

Player::~Player()
{ }

void Player::draw()
{ }
