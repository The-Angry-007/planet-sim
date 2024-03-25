#include "Game.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
#include "box2d/box2d.h"
#include "inputHandler.hpp"
Game::Game()
{
	this->savePath = SaveHandler::workingDir;
	std::cout << "initialising game" << std::endl;
	std::cout << "save path is " << savePath << std::endl;
	paused = false;
	b2Vec2 gravity(0.f, 0.f);
	world = new b2World(gravity);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}
void Game::Update(double dt)
{
	dt = dt;
	if (inp.keyPressed(sf::Keyboard::Key::Escape))
	{
		TogglePaused();
		if (paused)
		{
			return;
		}
	}
	if (inp.mbDown(sf::Mouse::Button::Left))
	{
		float power = 300.f;
		b2Vec2 pos((inp.mousePos.x - width / 2) / 10.f, (inp.mousePos.y - height / 2) / -10.f);
		b2Vec2 offset = pos - body->GetPosition();
		float distance = offset.LengthSquared();
		offset.Normalize();
		b2Vec2 repulsion = -power / distance * offset;
		body->ApplyForceToCenter(repulsion, true);
	}
	//update box2d world
	world->Step(dt, 6, 2);
}
void Game::TogglePaused()
{
	if (!paused)
	{
		paused = true;
		menu.OpenMenu(5);
	}
	else
	{
		paused = false;
		menu.OpenMenu(4);
	}
}
void Game::Render()
{
	sf::RectangleShape rect = box2dBodyToSFML(body, sf::Color::Red);
	window->draw(rect);
}
Game::~Game()
{
}

sf::RectangleShape box2dBodyToSFML(b2Body* body, const sf::Color& color)
{
	float SCALE = 10.f;
	// Assuming the body has a polygon shape fixture
	b2Fixture* fixture = body->GetFixtureList();
	if (!fixture)
		return sf::RectangleShape();

	b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>(fixture->GetShape());
	if (!polygonShape)
		return sf::RectangleShape();

	// Get the size of the Box2D "box" shape
	b2Vec2 size = polygonShape->m_vertices[2]; // Assuming the first vertex is at the bottom-left

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.x * 2.0f * SCALE, size.y * 2.0f * SCALE)); // Box2D's size is half-width and half-height
	rectangle.setOrigin(size.x * SCALE, size.y * SCALE);						   // Set origin to center for proper rotation
	rectangle.setPosition(SCALE * body->GetPosition().x + width / 2, -SCALE * body->GetPosition().y + height / 2);
	rectangle.setRotation(body->GetAngle() * 180.0f / b2_pi); // Convert radians to degrees
	rectangle.setFillColor(color);

	return rectangle;
}