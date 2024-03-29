#include "parts/Structure.hpp"
#include "Main.hpp"
Structure::Structure()
{
}
void Structure::AddPart(Part* part)
{
	parts.push_back(part);
	connections.push_back(std::vector<int> {});
}
void Structure::ResetCOM()
{
	float total = 0.f;
	com = b2Vec2(0, 0);
	for (uint i = 0; i < parts.size(); i++)
	{
		b2Vec2 bodyCom = parts[i]->body->GetWorldCenter();
		float mass = parts[i]->body->GetMass();
		bodyCom *= mass;
		com += bodyCom;
		total += mass;
	}
	com *= 1.f / total;
}
void Structure::AddConnection(int part1, int part2)
{
	connections[part1].push_back(part2);
	b2Body* b1 = parts[part1]->body;
	b2Body* b2 = parts[part2]->body;
	b2Vec2 point = b1->GetPosition() + b2->GetPosition();
	point *= 0.5f;
	b2WeldJointDef def;
	def.Initialize(b1, b2, point);
	game->world->CreateJoint(&def);
}
void Structure::AddConnection(Part* part1, Part* part2)
{
	int i1, i2;
	for (uint i = 0; i < parts.size(); i++)
	{
		if (parts[i] == part1)
		{
			i1 = i;
		}
		else if (parts[i] == part2)
		{
			i2 = i;
		}
	}
	AddConnection(i1, i2);
}
void Structure::Update(double dt)
{
	ResetCOM();

	for (uint i = 0; i < parts.size(); i++)
	{
		parts[i]->Update(dt);
	}
}
void Structure::Render()
{
	if (focused)
	{
		CentreCamera();
	}
	for (uint i = 0; i < parts.size(); i++)
	{
		parts[i]->Render();
	}
}
void Structure::CentreCamera()
{
	camera.pos = sf::Vector2f(com.x * 128.f, -com.y * 128.f);
}