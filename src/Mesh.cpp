#include "Mesh.h"

void Mesh::LoadBruteForceOBJ(std::string filename, float scale, int xOffset, int yOffset, int zOffset)
{
	std::string err;
	tinyobj::LoadObj(&m_attrib, &m_shapes, &m_materials, &err, filename.c_str(), NULL, true);

	for (size_t i = 0; i < m_shapes.size(); i++) {
		size_t index_offset = 0;

		// For each face
		for (size_t f = 0; f < m_shapes[i].mesh.num_face_vertices.size(); f++) {
			size_t fnum = m_shapes[i].mesh.num_face_vertices[f];

			aml::Vector normal;
			float k;
			aml::Vector A;
			aml::Vector B;
			aml::Vector C;

			tinyobj::index_t idxA = m_shapes[i].mesh.indices[index_offset + 0];
			A.x = (m_attrib.vertices.at(3 * idxA.vertex_index + 0)*scale) + xOffset;
			A.y = (m_attrib.vertices.at(3 * idxA.vertex_index + 1)*scale) + yOffset;
			A.z = (m_attrib.vertices.at(3 * idxA.vertex_index + 2)*scale) + zOffset;

			tinyobj::index_t idxB = m_shapes[i].mesh.indices[index_offset + 1];
			B.x = (m_attrib.vertices.at(3 * idxB.vertex_index + 0)*scale) + xOffset;
			B.y = (m_attrib.vertices.at(3 * idxB.vertex_index + 1)*scale) + yOffset;
			B.z = (m_attrib.vertices.at(3 * idxB.vertex_index + 2)*scale) + zOffset;

			tinyobj::index_t idxC = m_shapes[i].mesh.indices[index_offset + 2];
			C.x = (m_attrib.vertices.at(3 * idxC.vertex_index + 0)*scale) + xOffset;
			C.y = (m_attrib.vertices.at(3 * idxC.vertex_index + 1)*scale) + yOffset;
			C.z = (m_attrib.vertices.at(3 * idxC.vertex_index + 2)*scale) + zOffset;

			normal = aml::Normalise(aml::CrossProduct((B - A), (C - A)));

			k = aml::DotProduct(normal, A);

			Face face(A, B, C, normal, k);

			faces.push_back(face);

			index_offset += fnum;

		}
	}
	
}

void Mesh::LoadMollerTrumboreOBJ(std::string filename, float scale, int xOffset, int yOffset, int zOffset)
{
	std::string err;
	tinyobj::LoadObj(&m_attrib, &m_shapes, &m_materials, &err, filename.c_str(), NULL, true);

	for (size_t i = 0; i < m_shapes.size(); i++) {
		size_t index_offset = 0;

		// For each face
		for (size_t f = 0; f < m_shapes[i].mesh.num_face_vertices.size(); f++) {
			size_t fnum = m_shapes[i].mesh.num_face_vertices[f];

			aml::Vector vert0;
			aml::Vector vert1;
			aml::Vector vert2;
			aml::Vector edge1;
			aml::Vector edge2;

			tinyobj::index_t idxA = m_shapes[i].mesh.indices[index_offset + 0];
			vert0.x = (m_attrib.vertices.at(3 * idxA.vertex_index + 0)*scale) + xOffset;
			vert0.y = (m_attrib.vertices.at(3 * idxA.vertex_index + 1)*scale) + yOffset;
			vert0.z = (m_attrib.vertices.at(3 * idxA.vertex_index + 2)*scale) + zOffset;

			tinyobj::index_t idxB = m_shapes[i].mesh.indices[index_offset + 1];
			vert1.x = (m_attrib.vertices.at(3 * idxB.vertex_index + 0)*scale) + xOffset;
			vert1.y = (m_attrib.vertices.at(3 * idxB.vertex_index + 1)*scale) + yOffset;
			vert1.z = (m_attrib.vertices.at(3 * idxB.vertex_index + 2)*scale) + zOffset;

			tinyobj::index_t idxC = m_shapes[i].mesh.indices[index_offset + 2];
			vert2.x = (m_attrib.vertices.at(3 * idxC.vertex_index + 0)*scale) + xOffset;
			vert2.y = (m_attrib.vertices.at(3 * idxC.vertex_index + 1)*scale) + yOffset;
			vert2.z = (m_attrib.vertices.at(3 * idxC.vertex_index + 2)*scale) + zOffset;

			edge1 = vert1 - vert0;
			edge2 = vert2 - vert0;

			MollerTrumboreFace face(vert0, edge1, edge2);

			MTFaces.push_back(face);

			index_offset += fnum;

		}
	}
}
