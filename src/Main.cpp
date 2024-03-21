#include "include/Main.hpp"
#include "PCH.hpp"
#include "Platform/Platform.hpp"
#include "include/Gui.hpp"
#include "include/inputHandler.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <math.h>

sf::RenderWindow* window = new sf::RenderWindow();

sf::Clock deltaClock;
Gui gui;
InputHandler inp;
int main()
{
	util::Platform platform;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window->getSystemHandle());
	// Use the screenScalingFactor
	window->create(sf::VideoMode(800.0f * screenScalingFactor, 500.0f * screenScalingFactor), "Planet Sim");
	window->setVerticalSyncEnabled(false);
	sf::Vector2u windowSize = window->getSize();
	sf::Image icon;
	icon.loadFromFile("src/images/icon.png");
	window->setIcon(110, 110, icon.getPixelsPtr());
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

		window->clear(sf::Color(8, 0, 20));
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