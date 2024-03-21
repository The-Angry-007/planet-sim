#include "ClickFuncs.hpp"
#include "Main.hpp"
void ClickFuncs::NewGame()
{
	std::cout << "New Game Clicked" << std::endl;
}
void ClickFuncs::LoadGame()
{
	std::cout << "Load Game Clicked" << std::endl;
}
void ClickFuncs::Options()
{
	std::cout << "Options Clicked" << std::endl;
}
void ClickFuncs::Quit()
{
	window->close();
}