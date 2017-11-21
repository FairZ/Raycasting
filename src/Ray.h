#ifndef _RAY_H_
#define _RAY_H_
#include "Maths.h"

struct Face;
struct MollerTrumboreFace;

class Ray
{
public:
	bool calcHitPoint(Face _face, aml::Vector &hitPoint);
	bool MollerTrumboreIntersection(MollerTrumboreFace _face, float &_t);
	Ray(aml::Vector _origin, aml::Vector _direction);
	aml::Vector origin;
	aml::Vector direction;
};


#endif