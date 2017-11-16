#include "Ray.h"
#include "Mesh.h"

bool Ray::calcHitPoint(Face _face, aml::Vector &hitPoint)
{
	
	bool RetVal = false;
	float t;

	//first calculate the denominator of the formula which finds t in order to check if it is less than 0
	//this will mean that no crashes occur from dividing by 0 and no faces which are facing away from the 
	//'camera' will not be hit (equivalent of backface culling)
	float denom = aml::DotProduct(_face.normal, direction);

	if (denom < 0.0f)
	{
		t = (_face.k - aml::DotProduct(_face.normal, origin)) / denom;
		//if t is less than 0 then the hitpoint is behind the 'camera' and if it is greater than 256 it is outside of the drawing volume
		//so should return a false hit
		if (t > 0 && t <= 256)
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