#include "utils.hpp"
#include "Main.hpp"
#include "PCH.hpp"
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

void GetMaxFontSize(sf::Text* text, sf::Vector2f bounds)
{
	int min = 0;
	int max = std::max(bounds.x, bounds.y);
	while (true)
	{
		if (min == max)
		{
			break;
		}
		int guess = (min + max) / 2;
		text->setCharacterSize(guess);
		sf::FloatRect size = text->getLocalBounds();
		if (size.width > bounds.x || size.height + size.top > bounds.y)
		{
			max = guess;
		}
		else
		{
			min = guess + 1;
		}
	}
}

float Lerp(float a, float b, float c)
{
	return a + (b - a) * c;
}

std::vector<std::string> split(std::string str, char splitter)
{
	std::vector<std::string> list;
	std::string current = "";
	for (uint i = 0; i < str.size(); i++)
	{
		if (str[i] == splitter)
		{
			list.push_back(current);
			current = "";
		}
		else
		{
			current += str[i];
		}
	}
	if (current != "")
	{
		list.push_back(current);
	}
	return list;
}