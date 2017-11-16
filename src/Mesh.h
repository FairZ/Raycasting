#ifndef _MESH_H_
#define _MESH_H_
#include "Maths.h"
#include <vector>

struct Face
{
	aml::Vector verts[3];
	aml::Vector normal;
	float k;
	
	Face(aml::Vector _vert1, aml::Vector _vert2, aml::Vector _vert3, aml::Vector _normal, float _k)
	{
		verts[0] = _vert1;
		verts[1] = _vert2;
		verts[2] = _vert3;
		normal = _normal;
		k = _k;
	}

	bool WithinTriangle(aml::Vector hitPoint)
	{
		bool RetVal = true;
		if (aml::DotProduct(aml::CrossProduct(verts[1] - verts[0], hitPoint - verts[0]), normal) <= 0)
		{
			RetVal = false;
		}
		else if (aml::DotProduct(aml::CrossProduct(verts[2] - verts[1], hitPoint - verts[1]), normal) <= 0)
		{
			RetVal = false;
		}
		else if (aml::DotProduct(aml::CrossProduct(verts[0] - verts[2], hitPoint - verts[2]), normal) <= 0)
		{
			RetVal = false;
		}
		return RetVal;
	}
};

class Mesh
{
public:
	void LoadOBJ(std::string filename, float scale);
	std::vector<Face> faces;
};


#endif