#ifndef _MESH_H_
#define _MESH_H_
#include "Maths.h"
#include "tinyobjloader/tiny_obj_loader.h"
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
		if (aml::DotProduct(aml::CrossProduct(verts[1] - verts[0], hitPoint - verts[0]), normal) < 0.0f)
		{
			return false;
		}
		else if (aml::DotProduct(aml::CrossProduct(verts[2] - verts[1], hitPoint - verts[1]), normal) < 0.0f)
		{
			return false;
		}
		else if (aml::DotProduct(aml::CrossProduct(verts[0] - verts[2], hitPoint - verts[2]), normal) < 0.0f)
		{
			return false;
		}
		return true;
	}
};

struct MollerTrumboreFace
{
	aml::Vector vert0;
	aml::Vector edge1;
	aml::Vector edge2;

	MollerTrumboreFace(aml::Vector _vert0, aml::Vector _edge1, aml::Vector _edge2)
	{
		vert0 = _vert0;
		edge1 = _edge1;
		edge2 = _edge2;
	}
};

class Mesh
{
private:
	tinyobj::attrib_t m_attrib;
	std::vector<tinyobj::shape_t> m_shapes;
	std::vector<tinyobj::material_t> m_materials;
public:
	void LoadBruteForceOBJ(std::string filename, float scale, int xOffset, int yOffset, int zOffset);
	void LoadMollerTrumboreOBJ(std::string filename, float scale, int xOffset, int yOffset, int zOffset);
	std::vector<Face> faces;
	std::vector<MollerTrumboreFace> MTFaces;
};


#endif