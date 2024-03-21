#pragma once
#include "Gui/Gui.hpp"
class Menu
{
public:
	Menu();
	void OpenMenu(int menu);
	void AddGui(Gui gui);
	void Update();
	void Render(float dt);
	sf::Color bgColor;

private:
	int openMenu;
	std::vector<Gui> guis;
};

extern Menu InitMainMenu();