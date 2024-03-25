#pragma once
#include "box2d/box2d.h"
class Game
{
public:
	std::string savePath;
	bool paused;
	void Update(double dt);
	void Render();
	void TogglePaused();
	b2World* world;
	b2Body* groundBody;
	std::vector<b2Body*> blocks;
	Game();
	~Game();
};
extern sf::RectangleShape box2dBodyToSFML(b2Body* body, const sf::Color& color);
