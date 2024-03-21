#include "include/utils.hpp"
#include "PCH.hpp"
#include "include/Main.hpp"
#include <cmath>
void drawLine(sf::Vector2f point1, sf::Vector2f point2, float thickness, sf::Color col)
{
	sf::Vector2f dir = point2 - point1;
	float length = std::hypot(dir.x, dir.y);
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(length, thickness));
	line.setFillColor(col);
	line.setOrigin(0, thickness / 2.f);
	float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;
	line.setRotation(angle);
	line.setPosition(point1);
	window->draw(line);
}
Planet* getPlanet(int id)
{
	for (uint i { 0 }; i < planets.size(); i++)
	{
		if (planets[i]->id == id)
		{
			return planets[i];
		}
	}
	return nullptr;
}