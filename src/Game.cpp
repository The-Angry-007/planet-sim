#include "Game.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
#include "inputHandler.hpp"
Game::Game()
{
	this->savePath = SaveHandler::workingDir;
	std::cout << "initialising game" << std::endl;
	std::cout << "save path is " << savePath << std::endl;
	paused = false;
}
void Game::Update(double dt)
{
	dt = dt;
	if (inp.keyPressed(sf::Keyboard::Key::Escape))
	{
		TogglePaused();
	}
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
}
Game::~Game()
{
}