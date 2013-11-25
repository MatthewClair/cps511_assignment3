#include "modules/DrawableEntity/DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
	origin.x = 0; origin.y = 0; origin.z = 0;
	angles.x = 0; angles.y = 0; angles.z = 0;
}

DrawableEntity::DrawableEntity(Vector3D origin, Vector3D angles)
{
	this->origin = origin;
	this->angles = angles;
}

DrawableEntity::~DrawableEntity()
{ }
