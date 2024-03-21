#include "include/Path.hpp"
#include "include/Main.hpp"
Path::Path()
{
}
void Path::AddPoint(sf::Vector2f point)
{
	this->points.push_back(point);
	this->timesAdded.push_back(timer->getElapsedTime().asMilliseconds());
}
void Path::Render(sf::Color col)
{
	if (this->points.size() < 2)
	{
		return;
	}
	sf::VertexArray lines(sf::LinesStrip, this->points.size());

	for (int i = 0; i < (int)this->points.size(); i++)
	{
		lines[i].position = this->points[i];
		lines[i].color = sf::Color(col.r, col.g, col.b, (1.f - (timer->getElapsedTime().asMilliseconds() - timesAdded[i]) / 7000.f) * 255);
	}
	window->draw(lines);
}
Path::Path(Path* path)
{
	for (int i = 0; i < (int)path->points.size(); i++)
	{
		this->points.push_back(path->points[i]);
		this->timesAdded.push_back(path->timesAdded[i]);
	}
}

Path::~Path()
{
}
void Path::DeleteOldPaths()
{
	if (timesAdded.size() == 0)
	{
		return;
	}
	while (timer->getElapsedTime().asMilliseconds() - timesAdded[0] > 7000)
	{
		timesAdded.erase(timesAdded.begin());
		points.erase(points.begin());
		if (timesAdded.size() == 0)
		{
			return;
		}
	}
}