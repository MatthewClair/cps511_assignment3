#include "Point3D.h"
#include <cmath>

Point3D::Point3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D::~Point3D()
{ }

double Point3D::getDistance(Point3D other)
{
	double a = (x - other.x)*(x - other.x);
	double b = (y - other.y)*(y - other.y);
	double c = (z - other.z)*(z - other.z);
	return std::sqrt(a + b + c);
}

bool Point3D::operator==(const Point3D &rhs)
{
	return (x == rhs.x) &&
		(y == rhs.y) &&
		(z == rhs.z);
}

Point3D &Point3D::operator+=(const Point3D &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Point3D &Point3D::operator-=(const Point3D &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
