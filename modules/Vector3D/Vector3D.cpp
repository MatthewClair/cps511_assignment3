#include "modules/Vector3D/Vector3D.h"
#include <cmath>

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}
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

Vector3D Vector3D::crossProduct(const Vector3D &other)
{
	Vector3D a(
			(y*other.z - z*other.y),
			(z*other.x - x*other.z),
			(x*other.y - y*other.x)
			);
	return a;
}

double Vector3D::dotProduct(const Vector3D &other)
{
	return x*other.x + y*other.y + z*other.z;
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

void Vector3D::getFloatArray(float *array)
{
	array[0] = x;
	array[1] = y;
	array[2] = z;
}
