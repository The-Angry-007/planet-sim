#pragma once
#include "PCH.hpp"
#include "include/Main.hpp"
#include "include/Path.hpp"
class Path;
class Planet
{
public:
	std::vector<Path*> paths;
	int id;
	sf::Vector2f pos;
	double radius;
	double mass;
	sf::Vector2f velocity;
	sf::CircleShape* circle;
	sf::Color color;
	bool locked;
	void UpdateVel(std::vector<Planet*> planets, float dt);
	void UpdatePos(float dt);
	void Render();
	void calcGravity(Planet* other, float dt);
	void UpdateRadius(float newRadius);
	void SetMass(float mass);
	void GiveRandomVelocity(float magnitude);
	Path* predictFuture(int stepsPerSec, float secs, std::vector<Planet*> planets);
	bool touchingPlanet(Planet* other);
	void RenderPath();

	Planet(sf::Vector2f pos, double radius, sf::Color col, bool locked = false);
	Planet(Planet* ref, bool minimal);
	~Planet();
};