#ifndef _INCLUDE_POINT3D_H_
#define _INCLUDE_POINT3D_H_

#include <iostream>

class Point3D
{
	public:
		Point3D(double x, double y, double z);
		~Point3D();

		double x;
		double y;
		double z;

		double getDistance(Point3D other);
		const std::string toString();
		bool operator==(const Point3D &rhs);
		Point3D &operator+=(const Point3D &rhs);
		Point3D &operator-=(const Point3D &rhs);

	private:
};

inline Point3D operator+(Point3D lhs, const Point3D &rhs)
{
	lhs += rhs;
	return lhs;
}

inline Point3D operator-(Point3D lhs, const Point3D &rhs)
{
	lhs -= rhs;
	return lhs;
}

#endif
