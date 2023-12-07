#include "Color.hpp"
#include "Config.h"
#include "Library.hpp"
#include "Caster.cpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

#define PROJECT_DATA_DIR "../data/"
#define PROJECT_OUTPUT_DIR "../"

int main(int argc, char* argv[]) // arg1 is text source, arg2 is image target
{
	// End early if not enough arguments were passed
	if (argc != 3) { std::cout << "incorrect # of arguments passed. Using Defaults balls3-color.ray and ballstrace.ppm"; return 3; }

	// Assign arguments to correctly typed and named variables
	std::string source = argv[1];
	std::string target = argv[2];

	// Varaibles for storing parsed information
	coord eyep = {0, -8, 0};
	coord lookp = {0, 0, 0};
	coord up = {0, 0, 1};
	fColor background = { 0, 0, 0 };
	double fov[] = { 45, 45 };
	int screen[] = { 512, 512 };
	std::vector<light> lights;
	std::vector<surface> surfaces;
	std::vector<sphere> spheres;


	// platform-independent timing
	auto startTime = std::chrono::high_resolution_clock::now();

	// Initialtize File
	std::ifstream file(std::string(PROJECT_DATA_DIR) + source);
	if (!file) {
		std::cout << "File failed to open";
		return 1;
	}

	// Parse for relevent data
	std::string in = "";
	file >> in;
	while (!file.eof())
	{
		// Check to see if it's any of the revelent types. If so, save the data for easy use later.
		if (in.compare("background") == 0) {
			double bgD[] = {0, 0, 0};
			file >> bgD[0] >> bgD[1] >> bgD[2];

			// assign background
			background.r = bgD[0];
			background.g = bgD[1];
			background.b = bgD[2];
			file >> in;
		}
		else if (in.compare("eyep") == 0) {
			file >> eyep.x >> eyep.y >> eyep.z;
			file >> in;
		}
		else if (in.compare("lookp") == 0) {
			file >> lookp.x >> lookp.y >> lookp.z;
			file >> in;
		}
		else if (in.compare("up") == 0) {
			file >> up.x >> up.y >> up.z;
			file >> in;
		}
		else if (in.compare("fov") == 0) {
			file >> fov[0] >> fov[1];

			// Convert to radians
			fov[0] *= PI / 180;
			fov[1] *= PI / 180;
			file >> in;
		}
		else if (in.compare("screen") == 0) {
			file >> screen[0] >> screen[1];
			file >> in;
		}
		else if (in.compare("light") == 0) {
			light light;
			file >> light.intensity;
			file >> in; // Skip "point" label
			file >> light.pos.x;
			file >> light.pos.y;
			file >> light.pos.z;
			file >> in;
			
			lights.push_back(light);
		}
		else if (in.compare("surface") == 0) {
			surface surfTemp; // Holds surface info to push into surfaces array later
			double ambient[] = { 0, 0, 0 };
			double colors[] = { 0, 0, 0 };
			double specular[] = { 0, 0, 0 };
			surfTemp.specPower = 0;
			surfTemp.reflect = 0;

			file >> surfTemp.name; // Store Name for temp surface
			file >> in;

			while (in.compare("ambient") == 0 
				|| in.compare("diffuse") == 0
				|| in.compare("specular") == 0
				|| in.compare("specpow") == 0
				|| in.compare("reflect") == 0)
			{
				// Read ambient
				if (in.compare("ambient") == 0)
				{
					file >> ambient[0];
					file >> ambient[1];
					file >> ambient[2];
				}

				// Read Diffuse
				if (in.compare("diffuse") == 0)
				{
					file >> colors[0];
					file >> colors[1];
					file >> colors[2];
				}

				// Read specular (If it exists)
				if (in.compare("specular") == 0) {
					file >> specular[0];
					file >> specular[1];
					file >> specular[2];
				}
				if (in.compare("specpow") == 0) {
					file >> surfTemp.specPower;
				}
				if (in.compare("reflect") == 0) {
					file >> surfTemp.reflect;
				}
				file >> in;
			}

			// fill in surface struct
			surfTemp.ambient.r = ambient[0];
			surfTemp.ambient.g = ambient[1];
			surfTemp.ambient.b = ambient[2];
			surfTemp.diffuse.r = colors[0];
			surfTemp.diffuse.g = colors[1];
			surfTemp.diffuse.b = colors[2];
			surfTemp.specColor.r = specular[0];
			surfTemp.specColor.g = specular[1];
			surfTemp.specColor.b = specular[2];

			// Store the temp surface
			surfaces.push_back(surfTemp);
		}
		else if (in.compare("sphere") == 0) {
			sphere sphTemp; // Holds sphere info to push into spheres later

			file >> sphTemp.name; // Store Name for corresponding surface for sphere

			// Read in the 4 values
			file >> sphTemp.radius;
			file >> sphTemp.pos.x;
			file >> sphTemp.pos.y;
			file >> sphTemp.pos.z;

			int c = 0;
			while (surfaces[c].name.compare(sphTemp.name) != 0)
				c++;
			sphTemp.surf = surfaces[c];
			file >> in;

			// Store the temp sphere
			spheres.push_back(sphTemp);
		}

		// Reset input test character
		else file >> in;
	}
	std::cout << "Finished Parsing" << std::endl;


	// Distance from eyep to lookp
	coord dv;
	dv.x = lookp.x-eyep.x;
	dv.y = lookp.y-eyep.y;
	dv.z = lookp.z-eyep.z;
	double d = sqrt(pow(dv.x, 2) + pow(dv.y, 2) + pow(dv.z, 2)); // Distance from eye to center of the screen


	// edges of the screen in space
	double right = d * tan(fov[0] / 2); // Rightmost side of the screen
	double left = -right; // Leftmost side of the screen

	double top = d * tan(fov[1] / 2); // Top side of the screen
	double bottom = -top; // Bottom of the screen

	// Get coordianates of fractional pixel centers in real space
	std::vector<coord> centers;
	for (int j = 0; j < screen[0]; j++)
	{
		for (int i = 0; i < screen[1]; i++)
		{
			coord pixel;
			pixel.x = left + (right - left) * (i + 0.5) / screen[0];
			pixel.y = top - (top - bottom) * (j + 0.5) / screen[1];
			pixel.z = 0; // This wont matter for a lot of steps if (i'm doing this right)
			centers.push_back(pixel);
		}
	}
	std::cout << "Finished Getting Pixel Screen Locations" << std::endl;


	// Get w, u, and v vectors
	// Get w
	coord w;
	w.x = eyep.x - lookp.x;
	w.y = eyep.y - lookp.y;
	w.z = eyep.z - lookp.z;
	// Normalize w
	w = normalize(w);

	// Get u
	coord u;
	u = crossProduct(up, w);
	double ulen = sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));

	// Get v
	coord v;
	v = crossProduct(w, u);

	std::cout << "Finished w, u, and v calculations" << std::endl;


	// Screen Position (calculating the s vector)
	for (int i = 0; i < centers.size(); i++)
	{
		coord e = eyep;

		coord dw;
		dw.x = d * w.x;
		dw.y = d * w.y;
		dw.z = d * w.z;

		coord uu;
		uu.x = centers.at(i).x * u.x;
		uu.y = centers.at(i).x * u.y;
		uu.z = centers.at(i).x * u.z;

		coord vv;
		vv.x = centers.at(i).y * v.x;
		vv.y = centers.at(i).y * v.y;
		vv.z = centers.at(i).y * v.z;

		centers.at(i).x = e.x - dw.x + uu.x + vv.x;
		centers.at(i).y = e.y - dw.y + uu.y + vv.y;
		centers.at(i).z = e.z - dw.z + uu.z + vv.z;

		// if (i == 256*256) std::cout << "[" << centers.at(i).x << ", " << centers.at(i).y << ", " << centers.at(i).z << "]" << std::endl;
	}
	std::cout << "Finished calculating the s vector" << std::endl;

	// Calculating d vector
	for (int i = 0; i < centers.size(); i++)
	{
		centers.at(i).x = centers.at(i).x - eyep.x;
		centers.at(i).y = centers.at(i).y - eyep.y;
		centers.at(i).z = centers.at(i).z - eyep.z;
	}
	std::cout << "Finished Calculaing d vector" << std::endl;

	// REMOVE THIS WHEN RUNNING FOR REAL
	//return 0;
	
	// Calculate Ray-Sphere Intersections
	// For each ray, go through every sphere and see if we hit it.
	std::vector<uColor> picture;
	picture.resize(centers.size());

	for (int i = 0; i < picture.size(); i++)
	{
		fColor finalPixel = cast(spheres, lights, centers[i], eyep, 0, 1, background);

		// Do all the stuff to get the pixel ready to insert
		// Clamp
		if (finalPixel.r > 1) finalPixel.r = 1;
		if (finalPixel.g > 1) finalPixel.g = 1;
		if (finalPixel.b > 1) finalPixel.b = 1;

		// Gamma Correct
		finalPixel.r = pow(finalPixel.r, 1/2.2);
		finalPixel.g = pow(finalPixel.g, 1/2.2);
		finalPixel.b = pow(finalPixel.b, 1/2.2);
		// Scale
		finalPixel = finalPixel * 255;

		// Cast and insert into picture array
		picture[i].r = (unsigned char)finalPixel.r;
		picture[i].g = (unsigned char)finalPixel.g;
		picture[i].b = (unsigned char)finalPixel.b;
		
		if ((i % (screen[1]*16)) == 0) std::cout << "Line " << i / screen[1] << " Complete" << std::endl;
	}

	// open ppm output file in trace directory
	std::string ppmname = std::string(PROJECT_OUTPUT_DIR + target);
	std::fstream ppmfile(ppmname, std::ios::out | std::ios::binary);
	if (ppmfile.fail()) {
		std::cerr << "Error opening " << ppmname << '\n';
		return 2;
	}

	// Write to the file
	ppmfile << "P6\n" << screen[0] << " " << screen[1] << "\n255\n";
	ppmfile.write((char *)(&picture[0]), screen[0] * screen[1] * sizeof(uColor));

	// report final timing
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = endTime - startTime;
	std::cout << elapsed.count() << " seconds\n";
	return 0;
}