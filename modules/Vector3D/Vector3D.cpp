#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::~Vector3D()
{ }

double Vector3D::getDistance(const Vector3D &other)
{
	double a = (x - other.x)*(x - other.x);
	double b = (y - other.y)*(y - other.y);
	double c = (z - other.z)*(z - other.z);
	return std::sqrt(a + b + c);
}

bool Vector3D::operator==(const Vector3D &rhs)
{
	return (x == rhs.x) &&
		(y == rhs.y) &&
		(z == rhs.z);
}

Vector3D &Vector3D::operator+=(const Vector3D &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}