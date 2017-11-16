#include "Mesh.h"
#include "Ray.h"
#include "lodepng.h"
#include <chrono>
#include <iostream>

int main(int argc, char* argv[])
{
	//initialise image variables for drawing
	std::vector<unsigned char> img;
	img.resize(256 * 256 * 4);
	std::fill(img.begin(), img.end(), 255);

	//create timer for recording durations
	std::chrono::high_resolution_clock timer;

	//repeat the raycast for a number of iterations
	for (int iterations = 0; iterations < 1; iterations++)
	{
		//initialise variables for use in raycasting
		Mesh mesh;
		std::vector<Ray> rays;

		//record the time before the precalculation / loading phase 
		auto loadstart = timer.now();

		//pass in the fileName and scale of whatever triangulated OBJ you like as the command line arguments
		if (argc == 3)
		{
			mesh.LoadOBJ(argv[1], atof(argv[2]));
		}
		else
		{
			//if no parameters are passed in load a default model and scale
			mesh.LoadOBJ("gourd.obj", 75.0f);
		}

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
		auto loadend = timer.now();

		//for every face, go through every ray check if it hits the plane
		for (auto j : mesh.faces)
		{
			for (auto i : rays)
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
		auto end = timer.now();

		//output the individual and total durations
		std::cout << "Load time: " << std::chrono::duration_cast<std::chrono::milliseconds>(loadend - loadstart).count() << "ms" << std::endl;
		std::cout << "Raycast time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - loadend).count() << "ms" << std::endl;
		std::cout << "Total time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - loadstart).count() << "ms" << std::endl;

	}

	lodepng::encode("drawing.png", img, 256, 256);

	

	return 0;
}