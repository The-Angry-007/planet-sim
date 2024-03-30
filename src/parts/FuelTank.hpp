#pragma once
#include "parts/Part.hpp"
class FuelTank : public Part
{
public:
	float capacity;
	float maxCapacity;
	void SetCapacity();
	FuelTank(int index, b2Vec2 pos);
	void UpdateDensity();
	void Update(double dt);
	void Render();
	FuelTank(std::string saveString);
	std::string toString();
};