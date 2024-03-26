#include "parts/Thruster.hpp"
#include "Game.hpp"
#include "Main.hpp"
Thruster::Thruster(int index, b2Vec2 pos)
{
	this->index = index;
	texture = new sf::Texture();
	std::string path = "resources/textures/thruster" + std::to_string(index) + ".png";
	if (!texture->loadFromFile(path))
	{
		window->close();
	}
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = texture->getSize();
	sprite->setOrigin(size.x / 2, size.y / 2);
	//box2d setup
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	body = game->world->CreateBody(&bodyDef);
	b2PolygonShape poly;
	//each square is 0.5m, and this is 4x6
	b2Vec2 verts[4] = {
		b2Vec2(-1.f, 1.5f),
		b2Vec2(1.f, 1.5f),
		b2Vec2(1.f, -1.5f),
		b2Vec2(-1.f, -1.5f)
	};
	poly.Set(verts, 4);
	body->CreateFixture(&poly, 1.f);
}
void Thruster::Render()
{
	b2Vec2 bpos = body->GetPosition();
	sprite->setPosition(bpos.x * 128, -bpos.y * 128);
	sprite->setRotation(-body->GetAngle() / 3.14159f * 180.f);
	window->draw(*sprite);
}
void Thruster::Update(double dt)
{
}