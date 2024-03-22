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
	menu.OpenMenu(1);
}
void ClickFuncs::Quit()
{
	window->close();
}
void ClickFuncs::GoBack()
{
	menu.GoBack();
}