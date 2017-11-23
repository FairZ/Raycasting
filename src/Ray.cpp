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

bool Ray::MollerTrumboreIntersection(MollerTrumboreFace _face, float &_t)
{
	//calculate and store P for later use in the algorithm
	aml::Vector P = aml::CrossProduct(direction, _face.edge2);
	
	//calculate and store the determinant for use in back face culling and divide by zero error checking
	float determinant = aml::DotProduct(_face.edge1, P);

	//if the determinant is less than or equal to zero the ray is either parallel to or facing the back of
	//the triangle face so exit the function and return no hit
	if(determinant <= 0.0f)
		return false;

	float inverseDeterminant = 1/determinant;

	aml::Vector T = origin - _face.vert0;
	float u = aml::DotProduct(T, P) * inverseDeterminant;
	//if u is less than 0 or greater than 1 the hit point is not contained within the triangle
	//so exit the funciton and return no hit
	if (u < 0 || u > 1)
		return false;

	aml::Vector Q = aml::CrossProduct(T, _face.edge1);
	float v = aml::DotProduct(direction, Q) * inverseDeterminant;
	//if v is less than 0 or u+v is greater than 1 the hit point is not contained within the triangle
	//so exit the funciton and return no hit
	if (v < 0 || (u + v) > 1)
		return false;

	//calculate t and check whether it is within the rendering cube otherwise discard the hit
	_t = aml::DotProduct(_face.edge2, Q) * inverseDeterminant;
	if (_t < 0 || _t > 256)
		return false;

	return true;
}

Ray::Ray(aml::Vector _origin, aml::Vector _direction)
{
	origin = _origin;
	direction = _direction;
}
