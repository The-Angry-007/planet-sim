#include "include/Main.hpp"
#include "PCH.hpp"
#include "Platform/Platform.hpp"
#include "include/Gui.hpp"
#include "include/Planet.hpp"
#include "include/inputHandler.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <math.h>

//for unique identification of each planet; gui class needs to keep track of a selected planet, and the pointer will change as planets are added and removed from the list.
//the alternative approach to this would be to never rearrange the vector - replace deleted planets with nullptrs, and keep track of which are removed.
//however, thats a lot of effort :/
int planetId = 0;
sf::RenderWindow* window = new sf::RenderWindow();

sf::Clock deltaClock;
float G = 10.f;
float scale = 1.f;
sf::Vector2f offset;
std::vector<Planet*> planets;
Planet* addingPlanet = nullptr;
Gui gui;
int stepsPerSec = 10 * 150;
float sinceUpdate;
float universalDensity = 25.f;
sf::Clock* timer;
InputHandler inp;
sf::Vector2u windowSize;

//this is probably a terrible way to do this, so much deep copying.
std::vector<Path*> getPosesInFuture(int stepsPerSec, float numSecs, std::vector<Planet*> planets, Planet* extraPlanet)
{
	std::vector<Planet*> newPlanets;
	if (extraPlanet != nullptr)
	{
		newPlanets.push_back(new Planet(extraPlanet, true));
	}
	std::vector<Path*> allPaths;
	std::vector<int> indices;
	for (int i = 0; i < (int)planets.size(); i++)
	{
		newPlanets.push_back(new Planet(planets[i], true));
	}
	for (int i = 0; i < (int)newPlanets.size(); i++)
	{
		indices.push_back(i);
		allPaths.push_back(new Path());
	}
	int totalSteps = stepsPerSec * numSecs;
	float dt = 1.f / stepsPerSec;
	for (int i = 0; i < totalSteps; i++)
	{

		SolvePlanetCollisions(newPlanets, false, &indices);
		for (int j = 0; j < (int)newPlanets.size(); j++)
		{
			newPlanets[j]->UpdateVel(newPlanets, dt);
		}
		for (int j = 0; j < (int)newPlanets.size(); j++)
		{
			newPlanets[j]->UpdatePos(dt);
			allPaths[indices[j]]->AddPoint(newPlanets[j]->pos);
		}
	}
	for (int i = 0; i < (int)newPlanets.size(); i++)
	{
		delete (newPlanets[i]);
	}
	return allPaths;
}

void SolvePlanetCollisions(std::vector<Planet*>& planets, bool joinPaths, std::vector<int>* indices)
{
	int size = planets.size();
	//if 2 planets touch, erase the smaller of the 2 and make the other bigger
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			Planet* obj1 = planets[i];
			Planet* obj2 = planets[j];
			float minDist = obj1->radius + obj2->radius;
			sf::Vector2f dist = obj1->pos - obj2->pos;
			float dist2 = (dist.x * dist.x) + (dist.y * dist.y);
			if (dist2 < minDist * minDist)
			{
				//planets are touching
				int smaller = i;
				int bigger = j;
				if (obj2->mass < obj1->mass)
				{
					smaller = j;
					bigger = i;
				}
				obj1 = planets[bigger];
				obj2 = planets[smaller];
				//conservation of momentum
				obj1->velocity = ((float)obj1->mass * obj1->velocity + (float)obj2->mass * obj2->velocity) / (float)(obj1->mass + obj2->mass);
				obj1->pos = (obj1->pos * (float)obj1->mass + obj2->pos * (float)obj2->mass) / (float)(obj1->mass + obj2->mass);
				if (joinPaths)
				{
					obj1->paths[0]->AddPoint(obj1->pos);

					obj2->paths[0]->AddPoint(obj1->pos);
					for (int i = 0; i < (int)obj2->paths.size(); i++)
					{
						obj1->paths.push_back(obj2->paths[i]);
					}
				}
				obj1->SetMass(obj1->mass + obj2->mass);
				//				delete planets[smaller];

				planets.erase(planets.begin() + smaller);
				if (indices->size() > 0)
				{
					indices->erase(indices->begin() + smaller);
				}
				size--;
			}
		}
	}
}
int main()
{
	timer = new sf::Clock();
	inp = InputHandler();
	// srand((unsigned)time(NULL));
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window->getSystemHandle());
	// Use the screenScalingFactor
	window->create(sf::VideoMode(800.0f * screenScalingFactor, 500.0f * screenScalingFactor), "Planet Sim");
	window->setVerticalSyncEnabled(false);
	int width = window->getSize().x;
	int height = window->getSize().y;
	sf::Image icon;
	icon.loadFromFile("src/images/icon.png");
	window->setIcon(110, 110, icon.getPixelsPtr());

	offset = sf::Vector2f(width * 0, height * 0);
	srand(0);
	// for (int i = 0; i < 50; i++)
	// {
	// 	planets.push_back(new Planet(sf::Vector2f(rand() % width, rand() % height), 800, sf::Color::Red));
	// }
	//recreate solar system but first implement density
	//planets.push_back(new Planet(sf::Vector2f(0,0),1989000))
	planets.push_back(new Planet(sf::Vector2f(width / 2.f, height / 2.f), 200000, sf::Color(255, 255, 100), true));
	//orbital velocity formula: v=sqrt(G * m / r)
	planets.push_back(new Planet(sf::Vector2f(width * 3.f / 4.f, height / 2.f), 100, sf::Color::Red, false));
	planets[1]->velocity = sf::Vector2f(0, -sqrt(G * planets[0]->mass / (width / 4.f)));
	planets.push_back(new Planet(sf::Vector2f(width * 1.f / 3.f, height / 2.f), 100, sf::Color::Red, false));
	planets[2]->velocity = sf::Vector2f(0, -sqrt(G * planets[0]->mass / (width / 6.f)));
	float dtPerStep = 1.f / stepsPerSec;
	gui.Init();

	deltaClock.restart();
	while (window->isOpen())
	{
		//fix window size
		if (window->getSize() != windowSize)
		{
			windowSize = window->getSize();
			sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
			window->setView(view);
		}
		inp.ProcessEvents();
		gui.Update();
		double dt = deltaClock.restart().asSeconds();
		if (inp.mbPressed(sf::Mouse::Button::Left))
		{

			if (addingPlanet != nullptr)
			{
				addingPlanet->velocity = inp.mousePos - addingPlanet->pos;
				planets.push_back(addingPlanet);
				addingPlanet = nullptr;
			}
			else
			{
				addingPlanet = new Planet(inp.mousePos, 100, sf::Color::Blue);
			}
			//std::cout << "test" << std::endl;
		}
		if (inp.mbPressed(sf::Mouse::Button::Right))
		{
			planets.push_back(new Planet(inp.mousePos, 100000, sf::Color(255, 255, 100), true));
		}

		window->clear(sf::Color(8, 0, 20));
		int size = planets.size();
		float speed = 50.f;
		float speeddt = dtPerStep * speed;
		sinceUpdate += dt;
		while (sinceUpdate > dtPerStep)
		{
			sinceUpdate -= dtPerStep;
			SolvePlanetCollisions(planets, true);
			for (int i = 0; i < size; i++)
			{
				planets[i]->UpdateVel(planets, speeddt);
			}
			for (int i = 0; i < size; i++)
			{
				planets[i]->UpdatePos(speeddt);
			}
		}

		for (int i = 0; i < (int)planets.size(); i++)
		{
			planets[i]->RenderPath();
		}
		for (int i = 0; i < (int)planets.size(); i++)
		{
			planets[i]->Render();
		}
		// std::cout << planets[0]->circle->getPosition().x << std::endl;
		// std::cout << planets[1]->circle->getPosition().x << std::endl;

		if (addingPlanet != nullptr)
		{
			addingPlanet->Render();
			addingPlanet->velocity = inp.mousePos - addingPlanet->pos;
			std::vector<Path*> allPaths = getPosesInFuture(100, 10, planets, addingPlanet);
			allPaths[0]->Render(sf::Color::Red);
			for (int i = 0; i < (int)allPaths.size(); i++)
			{
				delete allPaths[i];
			}
		}
		gui.Render(dt);
		window->display();
	}
	return 0;
}

//setup solution to 3 body problem
// Planet* p = new Planet(sf::Vector2f(0.9700436f, -0.24308753f), 1.f, 10.f);
// p->velocity = sf::Vector2f(0.466203685f, 0.43236573f);
// p->SetMass(1);
// planets.push_back(p);
// p = new Planet(-sf::Vector2f(0.9700436f, -0.24308753f), 1.f, 10.f);
// p->velocity = sf::Vector2f(0.466203685f, 0.43236573f);
// p->SetMass(1);

// planets.push_back(p);
// p = new Planet(sf::Vector2f(0.f, 0.f), 1.f, 10.f);
// p->velocity = -2.f * sf::Vector2f(0.466203685f, 0.43236573f);
// p->SetMass(1);
//planets.push_back(p);
// planets.push_back(new Planet(sf::Vector2f(-0.5f, 0), 0.1f, 10));
// planets.push_back(new Planet(sf::Vector2f(0.f, 0), 0.1f, 10));
// planets.push_back(new Planet(sf::Vector2f(0.5f, 0), 0.1f, 10));
// for (int i = 0; i < 0; i++)
// {
// 	planets.push_back(new Planet(sf::Vector2f(rand() % width, rand() % height), rand() % 3 + 5));
// 	planets[i]->GiveRandomVelocity(10);
// }