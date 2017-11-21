#include "Mesh.h"
#include "Ray.h"
#include "lodepng.h"
#include <chrono>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	//initialise image variables for drawing
	std::vector<unsigned char> img;
	img.resize(256 * 256 * 4);
	std::fill(img.begin(), img.end(), 255);

	//create timer for recording durations
	std::chrono::steady_clock timer;
	auto loadstart = timer.now();
	auto loadend = timer.now();
	auto end = timer.now();
	
	//parameters for use later in program
	int noOfIterations = 1;
	std::string fileName = "teapot.obj";
	float scale = 75.0f;
	int xOffset = 128;
	int yOffset = 10;
	int zOffset = 128;

	//read in data from a config file to give parameters different values
	std::fstream config;

	config.open("Config.txt", std::ios_base::in);

	if(config.is_open())
	{
		config >> noOfIterations;
		config >> fileName;
		config >> scale;
		config >> xOffset;
		config >> yOffset;
		config >> zOffset;
	}

	config.close();

	//open an output file to send analytic data to
	std::fstream outputFile;

	outputFile.open("BruteForce.csv", std::ios_base::out | std::ios_base::trunc);

	outputFile << "Iteration," << "Load Time(ms)," << "Raycast Time(ms)," << "Total Time(ms)," << std::endl;

	//repeat the raycast for a number of iterations
	for (int iterations = 0; iterations < noOfIterations; iterations++)
	{
		//initialise variables for use in raycasting
		Mesh mesh;
		std::vector<Ray> rays;

		//record the time before the precalculation / loading phase 
		loadstart = timer.now();

		mesh.LoadBruteForceOBJ(fileName, scale, xOffset, yOffset, zOffset);

		//generate all rays
		aml::Vector direction(1, 0, 0);
		for (int m = 0; m < 256; m++)
		{
			for (int n = 0; n < 256; n++)
			{
				rays.push_back(Ray(aml::Vector(0, m, n), direction));
			}
		}
		aml::Vector hitPoint;

		//record time once loading/precalculation has ended and raycasting begins
		loadend = timer.now();

		//for every ray, go through every face and check if they collide
		for (auto i : rays)
		{
			for (auto j : mesh.faces)
			{
				if (i.calcHitPoint(j, hitPoint))
				{
					//if the plane is hit calculate whether the hit point is within the triangle
					if (j.WithinTriangle(hitPoint))
					{
						//if it is draw a colour in the position of the ray
						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 0] = fabs(j.normal.x) * 255;
						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 1] = fabs(j.normal.y) * 255;
						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 2] = fabs(j.normal.z) * 255;

					}
				}
			}
		}

		//record the time once the rays have been cast
		end = timer.now();

		//output the individual and total durations
		outputFile << iterations  << "," 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(loadend - loadstart).count() << ","
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - loadend).count() << ","
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - loadstart).count() << "," << std::endl;

	}

	outputFile.close();

	outputFile.open("MollerTrumbore.csv", std::ios_base::out | std::ios_base::trunc);

	outputFile << "Iteration," << "Load Time(ms)," << "Raycast Time(ms)," << "Total Time(ms)," << std::endl;

	//repeat the raycast for a number of iterations
	for (int iterations = 0; iterations < noOfIterations; iterations++)
	{
		//initialise variables for use in raycasting
		Mesh mesh;
		std::vector<Ray> rays;

		//record the time before the precalculation / loading phase 
		loadstart = timer.now();

		mesh.LoadMollerTrumboreOBJ(fileName, scale, xOffset, yOffset, zOffset);

		//generate all rays
		aml::Vector direction(1, 0, 0);
		for (int m = 0; m < 256; m++)
		{
			for (int n = 0; n < 256; n++)
			{
				rays.push_back(Ray(aml::Vector(0, m, n), direction));
			}
		}

		float t;

		//record time once loading/precalculation has ended and raycasting begins
		loadend = timer.now();

		//for every ray, go through every face and check if they collide
		for (auto i : rays)
		{
			for (auto j : mesh.MTFaces)
			{
				if (i.MollerTrumboreIntersection(j, t))
				{
					img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 0] = t;
					img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 1] = i.origin.y;
					img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 2] = i.origin.z;
				}
			}
		}

		//record the time once the rays have been cast
		end = timer.now();

		//output the individual and total durations
		outputFile << iterations  << "," 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(loadend - loadstart).count() << ","
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - loadend).count() << ","
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - loadstart).count() << "," << std::endl;

	}

	outputFile.close();

	lodepng::encode("drawing.png", img, 256, 256);

	

	return 0;
}