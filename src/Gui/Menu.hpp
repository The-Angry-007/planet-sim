#pragma once
#include "Gui/Gui.hpp"
class Menu
{
public:
	Menu();
	void OpenMenu(int menu);

private:
	int openMenu;
	std::vector<Gui> guis;
};