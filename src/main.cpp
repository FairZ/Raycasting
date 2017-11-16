#include "Mesh.h"
#include "Ray.h"
#include "lodepng.h"
#include <chrono>
#include <iostream>

int main(int argc, char* argv[])
{
	

	
	std::vector<unsigned char> img;
	img.resize(256 * 256 * 4);
	std::fill(img.begin(), img.end(), 255);

	std::chrono::high_resolution_clock timer;

	for (int iterations = 0; iterations < 50; iterations++)
	{
		Mesh mesh;
		std::vector<Ray> rays;

		auto loadstart = timer.now();

		//pass in the fileName and scale of whatever triangulated OBJ you like as the command line arguments
		if (argc == 3)
		{
			mesh.LoadOBJ(argv[1], atof(argv[2]));
		}
		else
		{
			//if no parameters are passed in load a default model
			mesh.LoadOBJ("gourd.obj", 75.0f);
		}

		auto loadend = timer.now();

		aml::Vector direction(1, 0, 0);
		for (int m = 0; m < 256; m++)
		{
			for (int n = 0; n < 256; n++)
			{
				rays.push_back(Ray(aml::Vector(0, m, n), direction));
			}
		}

		aml::Vector hitPoint;
		for (auto j : mesh.faces)
		{
			for (auto i : rays)
			{
				if (i.calcHitPoint(j, hitPoint))
				{
					if (j.WithinTriangle(hitPoint))
					{

						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 0] = fabs(j.normal.x) * 255;
						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 1] = fabs(j.normal.y) * 255;
						img[4 * 256 * (255 - i.origin.y) + 4 * (i.origin.z) + 2] = fabs(j.normal.z) * 255;

					}
				}
			}
		}

		auto end = timer.now();

		std::cout << "Load time: " << std::chrono::duration_cast<std::chrono::milliseconds>(loadend - loadstart).count() << "ms" << std::endl;
		std::cout << "Raycast time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - loadend).count() << "ms" << std::endl;
		std::cout << "Total time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - loadstart).count() << "ms" << std::endl;

	}

	lodepng::encode("drawing.png", img, 256, 256);

	

	return 0;
}