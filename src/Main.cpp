#include "Main.hpp"
#include "Gui/Gui.hpp"
#include "Gui/Menu.hpp"
#include "PCH.hpp"
#include "Platform/Platform.hpp"
#include "SaveHandler.hpp"
#include "inputHandler.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <math.h>

sf::RenderWindow* window = new sf::RenderWindow();
sf::Clock deltaClock;
//Gui gui;
InputHandler inp;
sf::Font* defaultFont = new sf::Font();
int width, height;
Menu menu;
int main()
{
	SaveHandler::ResetDir();
	util::Platform platform;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window->getSystemHandle());
	// Use the screenScalingFactor
	window->create(sf::VideoMode(800.0f * screenScalingFactor, 500.0f * screenScalingFactor), "Planet Sim");
	window->setVerticalSyncEnabled(false);
	sf::Vector2u windowSize = window->getSize();
	width = windowSize.x;
	height = windowSize.y;
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());
	if (!defaultFont->loadFromFile("resources/fonts/Trispace-Regular.ttf"))
	{
		window->close();
	}
	//gui.Init();
	menu = InitMenu();
	deltaClock.restart();
	while (window->isOpen())
	{
		//fix window size
		if (window->getSize() != windowSize)
		{
			windowSize = window->getSize();
			sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
			window->setView(view);
			width = windowSize.x;
			height = windowSize.y;
		}
		inp.ProcessEvents();
		double dt = deltaClock.restart().asSeconds();
		menu.Update();
		window->clear(sf::Color(8, 0, 20));
		menu.Render(dt);
		window->display();
	}
	return 0;
}