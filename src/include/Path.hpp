#pragma once
class Path
{
public:
	std::vector<sf::Vector2f> points;
	std::vector<long> timesAdded;
	void AddPoint(sf::Vector2f point);
	void Render(sf::Color col = sf::Color::White);
	void DeleteOldPaths();
	Path();
	Path(Path*);
	~Path();
};