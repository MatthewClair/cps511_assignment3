#include "Light.h"

Light::Light() : DrawableEntity()
{ }

Light::Light(Vector3D origin, Vector3D angles,
		GLenum light, const float *diffuse): DrawableEntity(origin, angles)
{
	this->light = light;
	this->diffuse[0] = diffuse[0];
	this->diffuse[1] = diffuse[1];
	this->diffuse[2] = diffuse[2];
	this->diffuse[3] = diffuse[3];
}

Light::~Light()
{ }

void Light::Draw()
{
	glEnable(light);

	glLightfv(light, GL_DIFFUSE,  diffuse);
	glLightfv(light, GL_SPECULAR, specular);
	float array[4];
	origin.getFloatArray(array);
	array[3] = 1.0;
	glLightfv(light, GL_POSITION, array);

}
