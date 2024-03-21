#include "include/Planet.hpp"
#include "PCH.hpp"
Planet::Planet(sf::Vector2f pos, double mass, sf::Color col, bool locked)
{
	this->color = col;
	this->locked = locked;
	this->paths.push_back(new Path());
	this->pos = pos;
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->mass = radius * radius * 3.14159265f;
	this->circle = new sf::CircleShape();
	this->circle->setFillColor(sf::Color::Red);
	this->circle->setRadius(radius);
	this->circle->setOrigin(radius, radius);
	this->SetMass(mass);
	id = planetId;
	planetId++;
}
void Planet::UpdateVel(std::vector<Planet*> planets, float dt)
{
	if (this->locked)
	{
		return;
	}
	sf::Vector2f accel;
	for (int i = 0; i < (int)planets.size(); i++)
	{
		Planet* other = planets[i];

		sf::Vector2f ds = other->pos - this->pos;
		float sDist = ds.x * ds.x + ds.y * ds.y;
		if (sDist == 0)
		{
			continue;
		}
		float mag = G * other->mass / sDist;

		float dist = sqrt(sDist);

		accel += sf::Vector2f(mag * ds.x / dist, mag * ds.y / dist);
	}
	this->velocity += accel * dt;
	//do collision checking
}

// void Planet::calcGravity(Planet* other, float dt)
// {
// 	sf::Vector2f accel;

// 		sf::Vector2f ds = other->pos - this->pos;
// 		float sDist = ds.x * ds.x + ds.y * ds.y;
// 		float dist = sqrt(sDist);
// 		float mag = G * other->mass / sDist;
// 		accel += sf::Vector2f(mag * ds.x / dist, mag * ds.y / dist);
// 	this->velocity += accel * dt;
// }
void Planet::UpdatePos(float dt)
{
	if (locked)
	{
		return;
	}
	this->pos += this->velocity * dt;
}

void Planet::Render()
{
	this->circle->setRadius(this->radius * scale);
	this->circle->setPointCount(this->circle->getRadius() * 2 * 3.14159f / 3.f);
	this->circle->setFillColor(this->color);

	this->circle->setOrigin(this->radius * scale, this->radius * scale);
	this->circle->setPosition(this->pos * scale + offset);
	window->draw(*this->circle);
	this->paths[0]->AddPoint(this->pos);
	for (uint i = 0; i < this->paths.size(); i++)
	{
		this->paths[i]->DeleteOldPaths();
	}
}
void Planet::UpdateRadius(float newRadius)
{
	this->radius = newRadius;
	if (circle != nullptr)
	{
		this->circle->setRadius(newRadius);
		this->circle->setOrigin(newRadius, newRadius);
	}
}

void Planet::GiveRandomVelocity(float magnitude)
{
	float dir = ((float)rand() / (float)RAND_MAX) * 2 * 3.14159f;
	sf::Vector2f vel = sf::Vector2f(sin(dir), cos(dir)) * magnitude;
	this->velocity += vel;
}

void Planet::SetMass(float mass)
{
	this->mass = mass;
	this->UpdateRadius(sqrt(this->mass / (universalDensity)));
}

Path* Planet::predictFuture(int stepsPerSec, float secs, std::vector<Planet*> planets)
{
	int totalSteps = stepsPerSec * secs;
	float dt = 1.f / (float)stepsPerSec;
	Path* path = new Path();
	sf::Vector2f startPos = pos;
	sf::Vector2f startVel = velocity;
	for (int i = 0; i < totalSteps; i++)
	{
		UpdateVel(planets, dt);
		UpdatePos(dt);
		path->AddPoint(pos);
		//check if collision occured, if so cut short
		bool collision = false;
		for (int i = 0; i < (int)planets.size(); i++)
		{
			if (planets[i] == this)
			{
				continue;
			}
			if (touchingPlanet(planets[i]))
			{
				collision = true;
				break;
			}
		}
		if (collision)
		{
			break;
		}
	}
	pos = startPos;
	velocity = startVel;
	return path;
}

bool Planet::touchingPlanet(Planet* other)
{
	float min = other->radius + this->radius;
	sf::Vector2f d = this->pos - other->pos;
	if (d.x * d.x + d.y * d.y < min * min)
	{
		return true;
	}
	return false;
}

void Planet::RenderPath()
{
	for (int i = 0; i < (int)paths.size(); i++)
	{
		paths[i]->Render();
	}
}
//implement that so it can be deep copied and then do the function in main to predict where everything is in the future
Planet::Planet(Planet* ref, bool minimal)
{
	if (!minimal)
	{
		for (int i = 0; i < (int)ref->paths.size(); i++)
		{
			this->paths.push_back(new Path(ref->paths[i]));
		}
		this->color = ref->color;
		this->circle = new sf::CircleShape();
		this->circle->setFillColor(this->color);
	}
	else
	{
		this->circle = nullptr;
	}
	this->locked = ref->locked;
	this->pos = ref->pos;
	this->velocity = ref->velocity;
	this->mass = ref->mass;

	this->SetMass(this->mass);
	id = planetId;
	planetId++;
}

Planet::~Planet()
{
	for (int i = 0; i < (int)paths.size(); i++)
	{
		delete (paths[i]);
	}
	delete (circle);
}