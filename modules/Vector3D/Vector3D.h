#ifndef _INCLUDE_VECTOR3D_H_
#define _INCLUDE_VECTOR3D_H_

class Vector3D
{
	public:
		Vector3D();
		Vector3D(double x, double y, double z);
		~Vector3D();

		double x;
		double y;
		double z;

		double getDistance(const Vector3D &other);
		Vector3D crossProduct(const Vector3D &other);
		double dotProduct(const Vector3D &other);
		bool operator==(const Vector3D &rhs);
		Vector3D &operator+=(const Vector3D &rhs);
		Vector3D &operator-=(const Vector3D &rhs);

	private:
};

inline Vector3D operator+(Vector3D lhs, const Vector3D &rhs)
{
	lhs += rhs;
	return lhs;
}

inline Vector3D operator-(Vector3D lhs, const Vector3D &rhs)
{
	lhs -= rhs;
	return lhs;
}

#endif
