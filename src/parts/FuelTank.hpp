#pragma once
#include "parts/Part.hpp"
class FuelTank : Part
{
public:
	float capacity;
	void SetCapacity();
	FuelTank(int index, b2Vec2 pos);
	void UpdateDensity();
	void Update(double dt);
	void Render();
};