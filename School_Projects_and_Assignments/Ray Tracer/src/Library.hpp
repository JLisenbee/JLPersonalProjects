// This file holds any extra values, structs, or functions that i'm likey to use later, and keeps them out of the main files.
#pragma once
#ifndef CUSTOM_LIBRARY
#define CUSTOM_LIBRARY
#include "Color.hpp"
#include "Config.h"

#include <vector>
#include <string>


// Pi out to more than enough positions to matter
const double PI = 3.14159265358979323846264;

// Useful values to be shared between different files
const double minContrib = 0.002;
const int maxDepth = 15;
const double epsilon = 0.0000001;

// Struct to hold coordinates, or any other x y z value
struct coord {
	double x;
	double y;
	double z;
};

// Structs to hold differnt types of objects in the scene
struct surface {
	std::string name;
	fColor ambient;
	fColor diffuse;
	fColor specColor = { NULL, NULL, NULL };
	double specPower = NULL;
	double reflect = NULL;
};
struct sphere {
	std::string name;
	double radius;
	coord pos;
	surface surf;
};
struct light {
	double intensity;
	coord pos;
};

// Cross Product Calculator
static coord crossProduct(coord a, coord b)
{
	coord product;

	product.x = (a.y * b.z) - (a.z * b.y);
	product.y = (a.z * b.x) - (a.x * b.z);
	product.z = (a.x * b.y) - (a.y * b.x);

	return product;
}

// Normalize a vector
static coord normalize(coord v)
{
	double l = sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) );

	v.x = v.x / l;
	v.y = v.y / l;
	v.z = v.z / l;

	return v;
}

// Vector Length
static double length(coord v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

// Dot product calculator
static double operator*(coord lhs, coord rhs)
{
	double total = 0;

	total += lhs.x * rhs.x;
	total += lhs.y * rhs.y;
	total += lhs.z * rhs.z;

	return total;
}

// Scalar Multiplying
static coord operator*(coord lhs, double rhs)
{
	coord product;

	product.x = lhs.x * rhs;
	product.y = lhs.y * rhs;
	product.z = lhs.z * rhs;

	return product;
}

// Vector Adding
static coord operator+(coord lhs, coord rhs)
{
	coord sum;

	sum.x = lhs.x + rhs.x;
	sum.y = lhs.y + rhs.y;
	sum.z = lhs.z + rhs.z;

	return sum;
}

// Vector subtracting
static coord operator-(coord lhs, coord rhs)
{
	coord diff;

	diff.x = lhs.x - rhs.x;
	diff.y = lhs.y - rhs.y;
	diff.z = lhs.z - rhs.z;

	return diff;
}

// Color Adding
static fColor operator+(fColor lhs, fColor rhs)
{
	fColor c;

	c.r = rhs.r + lhs.r;
	c.g = rhs.g + lhs.g;
	c.b = rhs.b + lhs.b;

	return c;
}

// Color Multiplying by a scalar with Overflow Protection
static fColor operator*(fColor lhs, double rhs)
{
	fColor c;

	c.r = rhs * lhs.r;
	c.g = rhs * lhs.g;
	c.b = rhs * lhs.b;

	return c;
}

// Debug function for printing a color
static std::string printColor(fColor c)
{
	std::string o = "";
	
	o.append("[");
	o.append(std::to_string(c.r));
	o.append(", ");
	o.append(std::to_string(c.g));
	o.append(", ");
	o.append(std::to_string(c.b));
	o.append("]");

	return o;
}

#endif