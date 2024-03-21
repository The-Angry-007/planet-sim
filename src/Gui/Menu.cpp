#include "Gui/Menu.hpp"
#include "Gui/ClickFuncs.hpp"
#include "Main.hpp"
Menu::Menu()
{
	openMenu = 0;
	bgColor = sf::Color::Transparent;
}
void Menu::AddGui(Gui gui)
{
	guis.push_back(gui);
}
void Menu::OpenMenu(int menu)
{
	openMenu = menu;
}
void Menu::Render(float dt)
{
	sf::RectangleShape bg(sf::Vector2f(width, height));
	bg.setFillColor(bgColor);
	window->draw(bg);
	if (openMenu != -1 && guis.size() > (uint)openMenu)
	{
		guis[openMenu].Render(dt);
	}
}
void Menu::Update()
{
	if (openMenu != -1 && guis.size() > (uint)openMenu)
	{
		guis[openMenu].Update();
	}
}
Menu InitMainMenu()
{
	Menu m;
	m.bgColor = sf::Color(100, 100, 100);
	Gui mainMenu;
	mainMenu.Init();
	mainMenu.AddLabel(Label("Planet Sim", sf::Vector2f(0.5f, 0.2f), sf::Vector2f(0.7f, 0.2f), sf::Color::Black));
	sf::Texture moon;
	if (!moon.loadFromFile("resources/images/moon.png"))
	{
		std::cout << "did not open correctly" << std::endl;
	}
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 1.f), sf::Vector2f(1.f, 2.f), sf::Color::Transparent, moon));
	mainMenu.AddButton(Button(sf::Vector2f(0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "New Game", sf::Color::White, ClickFuncs::NewGame));
	mainMenu.AddButton(Button(sf::Vector2f(1 - 0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "Load Game", sf::Color::White, ClickFuncs::LoadGame));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Options", sf::Color::White, ClickFuncs::Options));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.7f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Quit", sf::Color::White, ClickFuncs::Quit));
	m.AddGui(mainMenu);
	return m;
}