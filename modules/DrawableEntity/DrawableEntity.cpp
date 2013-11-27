#include "modules/DrawableEntity/DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
	origin = {0, 0, 0};
	angles = {0, 0, 0};
	velocity = {0, 0, 0};
}

DrawableEntity::DrawableEntity(Vector3D origin, Vector3D angles)
{
	this->origin = origin;
	this->angles = angles;
	this->velocity = {0, 0, 0};
}

DrawableEntity::DrawableEntity(Vector3D origin, Vector3D angles, Vector3D velocity)
{
	this->origin = origin;
	this->angles = angles;
	this->velocity = velocity;
}

DrawableEntity::~DrawableEntity()
{ }

void DrawableEntity::update()
{
	origin += velocity;
}

Vector3D DrawableEntity::getOrigin()
{
	return this->origin;
}

void DrawableEntity::setOrigin(Vector3D newOrigin)
{
	this->origin = newOrigin;
}
