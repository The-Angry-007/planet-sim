#include "parts/Thruster.hpp"
#include "Game.hpp"
#include "Main.hpp"
#include "utils.hpp"
Thruster::Thruster(int index, b2Vec2 pos)
{
	this->index = index;
	coneAngle = 0.f;
	InitSprites();
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
void Thruster::InitSprites()
{
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
	std::string conePath = "resources/textures/thruster" + std::to_string(index) + "cone.png";
	coneTexture = new sf::Texture();
	if (!coneTexture->loadFromFile(conePath))
	{
		window->close();
	}
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = texture->getSize();
	sprite->setScale(4.f, 4.f);
	sprite->setOrigin(size.x / 2, size.y / 2);
	ignitedSprite = new sf::Sprite(*ignitedTexture);
	ignitedSprite->setOrigin(size.x / 2.f, size.y / 2.f);
	ignitedSprite->setScale(4.f, 4.f);
	coneSprite = new sf::Sprite(*coneTexture);
	coneSprite->setScale(4.f, 4.f);
	coneSprite->setOrigin(size.x / 2.f, size.y / 2.f);
}

void Thruster::Render()
{
	//before, cone angle was relative to world. this meant that if whole thruster was rotating fast,
	//cone would lag behind, so instead now its relative.
	float worldConeAngle = coneAngle + body->GetAngle();
	b2Vec2 bpos = body->GetPosition();
	sf::Vector2f worldPos(bpos.x * 128.f, -bpos.y * 128.f);
	if (inp.keyDown(sf::Keyboard::Space))
	{
		ignitedSprite->setPosition(worldPos);
		ignitedSprite->setRotation(-worldConeAngle / b2_pi * 180.f);
		window->draw(*ignitedSprite);
	}
	coneSprite->setPosition(worldPos);
	coneSprite->setRotation(-worldConeAngle / b2_pi * 180.f);
	window->draw(*coneSprite);

	sprite->setPosition(worldPos);
	sprite->setRotation(-body->GetAngle() / b2_pi * 180.f);
	window->draw(*sprite);
}
void Thruster::Update(double dt)
{
	float targetAngle = 0.f;
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
			angle -= 0.1f;
			targetAngle -= 0.2f;
		}
		if (inp.keyDown(sf::Keyboard::Key::Right))
		{
			angle += 0.1f;
			targetAngle += 0.2f;
		}
		float mag = 150000.f;
		b2Vec2 force(mag * -sin(angle), mag * cos(angle));
		body->ApplyForce(force, point, true);
	}
	coneAngle = Lerp(coneAngle, targetAngle, dt * 10.f);
}