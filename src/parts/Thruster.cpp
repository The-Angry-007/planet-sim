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
	ignitedTexture = new sf::Texture();
	std::string ignitedPath = "resources/textures/thruster" + std::to_string(index) + "ignited.png";
	if (!ignitedTexture->loadFromFile(ignitedPath))
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
	body->CreateFixture(&poly, 7850.f);
}
void Thruster::Render()
{
	if (inp.keyDown(sf::Keyboard::Space))
	{
		sprite->setTexture(*ignitedTexture);
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(ignitedTexture->getSize())));
		window->draw(*sprite);
		sprite->setTexture(*texture);
		sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(texture->getSize())));
	}
	b2Vec2 bpos = body->GetPosition();
	sprite->setPosition(bpos.x * 128, -bpos.y * 128);
	sprite->setRotation(-body->GetAngle() / 3.14159f * 180.f);
	window->draw(*sprite);
}
void Thruster::Update(double dt)
{
	if (inp.keyDown(sf::Keyboard::Key::Space))
	{
		b2Vec2 centre = body->GetPosition();
		float angle = body->GetAngle();

		b2Vec2 offset(0.f, -1.5f);
		b2Vec2 worldOffset;
		worldOffset.x = offset.x * cos(angle) - offset.y * sin(angle);
		worldOffset.y = offset.x * sin(angle) + offset.y * cos(angle);
		b2Vec2 point = worldOffset + centre;
		if (inp.keyDown(sf::Keyboard::Key::Left))
		{
			angle -= 0.03f;
		}
		if (inp.keyDown(sf::Keyboard::Key::Right))
		{
			angle += 0.03f;
		}
		float mag = 150000.f;
		b2Vec2 force(mag * -sin(angle), mag * cos(angle));
		body->ApplyForce(force, point, true);
	}
}