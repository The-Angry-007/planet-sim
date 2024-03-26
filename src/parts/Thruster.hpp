#pragma once
#include "parts/Part.hpp"

class Thruster : Part
{
public:
	Thruster(int index, b2Vec2 pos);
	sf::Texture* ignitedTexture;
	void Update(double dt);
	void Render();
};