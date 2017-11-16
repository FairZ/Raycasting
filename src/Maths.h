#ifndef _MATHS_H_
#define _MATHS_H_

namespace aml
{
	class Vector
	{
	public:
		float x;
		float y;
		float z;

		Vector();
		Vector(float _x, float _y, float _z);

		float Magnitude();

		Vector operator*(const float _mult);
		Vector operator/(const float _div);
		Vector operator-(const Vector& _sub);
		Vector operator+(const Vector& _add);
	};

	float DotProduct(Vector _a, Vector _b);
	float AngleBetween(Vector _a, Vector _b);
	float TripleProduct(Vector _a, Vector _v, Vector _c);
	float AntiClockwiseAngleBetween(Vector _a, Vector _b, Vector _viewingDirection);
	float ToDegrees(float _angleInRads);

	Vector CrossProduct(Vector _a, Vector _b);
	Vector Normalise(Vector _vec);

}

#endif