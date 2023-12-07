#pragma once
#include "Color.hpp"
#include "Library.hpp"

#include <vector>
#include <iostream>


// This function checks to see if a sphere ever is intersected between two points
static bool shadowCheck(std::vector<sphere>& spheres, coord target, coord eyep, double maxDist)
{
	for (int j = 0; j < spheres.size(); j++)
	{
		double r = spheres[j].radius;
		coord g;
		g.x = eyep.x - spheres[j].pos.x;
		g.y = eyep.y - spheres[j].pos.y;
		g.z = eyep.z - spheres[j].pos.z;

		double a = target * target;
		double b = target * g;
		double c = (g * g) - (r * r);

		// Calculate discriminate first to see if we even need to do further calculation
		double descriminate = pow(b, 2) - (a * c);

		if (descriminate > 0) {
			// A hit was detected with another sphere. 
			// If that hit occured before the max distance (perhaps the distance to a light) return that this pixel is in shade
			double t = -1 * (target * g);
			t -= sqrt(descriminate);
			t /= (target * target);
			if (t < maxDist && t > 0) return true;
		}
	}
	return false;
}

// Loops through each sphere to get the pixel intersection, Then goes through each light to get the contribution of those lights
static fColor cast(std::vector<sphere>& spheres, std::vector<light>& lights, coord target, coord eyep, int depth, double contrib, fColor background)
{
	fColor color = { 0, 0, 0 };
	sphere nearest; // Nearest Sphere
	double lowT = INFINITY; // Nearest T, starts at inf
	bool hit = false; // Set to true if there's a hit

	// If the contribution is lower than the lowest possible, just shortcut to zero
	if (depth > maxDepth || contrib < minContrib) return color;

	// Check all the spheres to get the closest one
	for (int j = 0; j < spheres.size(); j++)
	{
		double r = spheres[j].radius;
		coord g;
		g.x = eyep.x - spheres[j].pos.x;
		g.y = eyep.y - spheres[j].pos.y;
		g.z = eyep.z - spheres[j].pos.z;

		double a = target * target;
		double b = target * g;
		double c = (g * g) - (r * r);

		// Calculate discriminate first to see if we even need to do further calculation
		double descriminate = pow(b, 2) - (a * c);

		// If you have a Hit, calculate the T
		if (descriminate > 0) {
			
			// Finish the Formula
			double t = -1 * (target * g);
			t -= sqrt(descriminate);
			t /= (target * target);
			if (t < lowT && t > epsilon) { // If that hit is the lowest T value calculated, fill in it's information
				lowT = t;
				nearest = spheres[j];
				hit = true;
			}
		}
	}

	//if (depth > 0 && hit)
		//std::cout << "check" << std::endl;

	if (!hit) 
		return background;

	// If we got here, that means that a sphere was intersected and we have the nearest one.
	// All of this info is on slide 42
	coord p = (eyep + (target * lowT));// Position = pVec = (eyep + t*dVec) [dVec is "Target"]
	coord n = normalize(p - nearest.pos); // Normal (Surface Normal) = Position intersected - Center of Sphere
	// S = Sphere information (Represented here by "nearest")
	coord v = normalize(target * -1);

	for (int i = 0; i < lights.size(); i++)
	{
		color = color + (nearest.surf.ambient * lights[i].intensity);
		coord l = normalize(lights[i].pos - p);
		coord h = normalize(l + v);
		if (n * l > 0 && !shadowCheck(spheres, l, p, length(lights[i].pos - p)))
		{
			double intense = lights[i].intensity * (n * l);
			color = color + (nearest.surf.diffuse * intense);
			if (n * h > 0) color = color + (nearest.surf.specColor * intense * pow((n * h), nearest.surf.specPower));
		}
	}

	// Calcualte reflection direction
	coord vn = n * (n * v);
	coord vm = v - vn;
	coord rn = vn;
	coord rm = vm * -1;
	coord reflect = (v * -1) + (n * (2 * (n * v)));

	color = color + (cast(spheres, lights, reflect, p, ++depth, contrib * nearest.surf.reflect, background) * nearest.surf.reflect);

	return color; // Return the color of the pixel
}