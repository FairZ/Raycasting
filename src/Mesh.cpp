#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

//Heavily edited from code originally by Leigh Mcloughlin. Original file can be found in Documentation folder of the hand in titled "OBJLOADER.cpp".
void Mesh::LoadOBJ(std::string filename, float scale)
{
	// Find file
	std::ifstream inputFile(filename);

	if (inputFile.is_open())
	{
		std::vector<aml::Vector> rawPositionData;

		std::string currentLine;

		while (std::getline(inputFile, currentLine))
		{
			std::stringstream currentLineStream(currentLine);

			if (!currentLine.substr(0, 2).compare(0, 1, "v"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawPositionData.push_back(aml::Vector((x*scale)+128, y*scale+128, (z*scale)+128));
			}
			//OBJLoader does precalculation of all data needed from faces, this will speed up program if run in real time
			else if (!currentLine.substr(0, 2).compare(0, 1, "f"))
			{
				std::string junk;
				int verts[3];
				aml::Vector normal;
				float k;
				aml::Vector A;
				aml::Vector B;
				aml::Vector C;

				currentLineStream >> junk >> verts[0] >> verts[1] >> verts[2];

				A = rawPositionData[verts[0] - 1];
				B = rawPositionData[verts[2] - 1];
				C = rawPositionData[verts[1] - 1];

				//normalise( (B-A) x (C-A) )
				normal = aml::Normalise(aml::CrossProduct((B - A), (C - A)));

				k = aml::DotProduct(normal, A);

				Face face(A, B, C, normal, k);

				faces.push_back(face);
			}
		}
	}
}
//end of function