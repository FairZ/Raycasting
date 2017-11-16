#include "Ray.h"
#include "Mesh.h"

bool Ray::calcHitPoint(Face _face, aml::Vector &hitPoint)
{
	bool RetVal = false;
	float t;

	float denom = aml::DotProduct(_face.normal, direction);

	if (denom < 0.0f)
	{
		t = (_face.k - aml::DotProduct(_face.normal, origin)) / denom;
		if (t > 0)
		{
			hitPoint = origin + (direction*t);
			RetVal = true;
		}
	}

	return RetVal;
}

Ray::Ray(aml::Vector _origin, aml::Vector _direction)
{
	origin = _origin;
	direction = _direction;
}