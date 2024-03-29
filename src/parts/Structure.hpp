#pragma once
#include "box2d/box2d.h"
#include "parts/Part.hpp"
class Structure
{
public:
	std::vector<Part*> parts;
	std::vector<std::vector<int>> connections;
	std::vector<b2WeldJoint> joints;
	Structure();
	void AddPart(Part* part);
	void Update(double dt);
	void Render();
};