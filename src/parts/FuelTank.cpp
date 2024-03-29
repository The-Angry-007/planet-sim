#include "parts/FuelTank.hpp"
#include "Main.hpp"
FuelTank::FuelTank(int index, b2Vec2 pos)
{
	this->index = index;
	SetCapacity();
	texture = new sf::Texture();
	std::string path = "resources/textures/fuelTank" + std::to_string(index) + ".png";
	if (!texture->loadFromFile(path))
	{
		window->close();
	}
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = texture->getSize();
	sprite->setScale(4.f, 4.f);
	sprite->setOrigin(size.x / 2, size.y / 2);
	//box2d setup
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	body = game->world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(1.f, 0.5f);
	body->CreateFixture(&shape, capacity + 100.f);
}
void FuelTank::Update(double dt)
{
	UpdateDensity();
}
void FuelTank::Render()
{
	b2Vec2 bpos = body->GetPosition();
	sprite->setPosition(bpos.x * 128, -bpos.y * 128);
	sprite->setRotation(-body->GetAngle() / 3.14159f * 180.f);
	window->draw(*sprite);
}
void FuelTank::UpdateDensity()
{
	body->GetFixtureList()->SetDensity(capacity + 100.f);
}
void FuelTank::SetCapacity()
{
	switch (index)
	{
		case 0:
			//this is the number of litres in a cylinder height 0.5m radius 0.5m
			capacity = 785.f;
	}
}