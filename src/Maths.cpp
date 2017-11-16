#include "Maths.h"
#include <math.h>


aml::Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

aml::Vector::Vector(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

float aml::Vector::Magnitude()
{
	return sqrtf((x*x) + (y*y) + (z*z));
}

aml::Vector aml::Vector::operator*(const float _mult)
{
	Vector result;

	result.x = this->x * _mult;
	result.y = this->y * _mult;
	result.z = this->z * _mult;

	return result;
}

aml::Vector aml::Vector::operator/(const float _div)
{
	Vector result;

	result.x = this->x / _div;
	result.y = this->y / _div;
	result.z = this->z / _div;

	return result;
}

aml::Vector aml::Vector::operator-(const Vector& _sub)
{
	Vector result;

	result.x = this->x - _sub.x;
	result.y = this->y - _sub.y;
	result.z = this->z - _sub.z;

	return result;
}

aml::Vector aml::Vector::operator+(const Vector & _add)
{
	Vector result;

	result.x = this->x + _add.x;
	result.y = this->y + _add.y;
	result.z = this->z + _add.z;

	return result;
}

float aml::DotProduct(Vector _a, Vector _b)
{
	return (_a.x*_b.x) + (_a.y*_b.y) + (_a.z*_b.z);
}

float aml::AngleBetween(Vector _a, Vector _b)
{
	return acosf(aml::DotProduct(_a, _b) / (_a.Magnitude()*_b.Magnitude()));
}

float aml::TripleProduct(Vector _a, Vector _b, Vector _c)
{
	float result;

	Vector V1xV2 = CrossProduct(_a, _b);
	result = DotProduct(_c, V1xV2);

	return result;
}

float aml::AntiClockwiseAngleBetween(Vector _a, Vector _b, Vector _viewingDirection)
{
	float result = AngleBetween(_a, _b);

	if (TripleProduct(_a, _b, _viewingDirection) < 0)
	{
		result = (2 * 3.14159265358979f) - result;
	}

	return result;
}

float aml::ToDegrees(float _angleInRads)
{
	return _angleInRads * (180.0f / 3.14159265358979f);
}

aml::Vector aml::CrossProduct(Vector _a, Vector _b)
{
	Vector RetVal(((_a.y*_b.z) - (_a.z*_b.y)), ((_a.z*_b.x) - (_a.x*_b.z)), ((_a.x*_b.y) - (_a.y*_b.x)));

	return RetVal;
}

aml::Vector aml::Normalise(Vector _vec)
{
	Vector result;

	result = _vec / _vec.Magnitude();

	return result;
}