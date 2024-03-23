#include "Gui/ClickFuncs.hpp"
#include "Gui/Gui.hpp"
#include "Main.hpp"
Menu::Menu()
{
	openMenu = 0;
}
void Menu::AddGui(Gui gui)
{
	guis.push_back(gui);
}
void Menu::OpenMenu(int menu)
{
	openMenu = menu;
	openedGuis.push_back(menu);
}
void Menu::Render(float dt)
{
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
void Menu::GoBack()
{
	openedGuis.pop_back();
	OpenMenu(openedGuis[openedGuis.size() - 1]);
	openedGuis.pop_back();
}
Menu InitMenu()
{
	Menu m;
	Gui mainMenu;
	mainMenu.Init();
	mainMenu.AddLabel(Label("Planet Sim", sf::Vector2f(0.5f, 0.2f), sf::Vector2f(0.7f, 0.2f), sf::Color::Black));
	sf::Texture moon;
	if (!moon.loadFromFile("resources/images/moon.png"))
	{
		std::cout << "did not open correctly" << std::endl;
	}
	mainMenu.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(100, 100, 100)));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 1.f), sf::Vector2f(1.f, 2.f), sf::Color::Transparent, moon));
	mainMenu.AddButton(Button(sf::Vector2f(0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "New Game", sf::Color::White, ClickFuncs::NewGame));
	mainMenu.AddButton(Button(sf::Vector2f(1 - 0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "Load Game", sf::Color::White, ClickFuncs::LoadGame));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Options", sf::Color::White, ClickFuncs::Options));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.7f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Quit", sf::Color::White, ClickFuncs::Quit));
	m.AddGui(mainMenu);
	//options menu
	Gui options;
	options.Init();
	options.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(80, 80, 80)));
	options.AddButton(Button(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.15f, 0.1f), sf::Color(50, 50, 50), "go back", sf::Color::White, ClickFuncs::GoBack));
	m.AddGui(options);
	//new game menu
	Gui newGame;
	newGame.Init();
	newGame.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(80, 80, 80)));
	newGame.AddButton(Button(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.15f, 0.1f), sf::Color(50, 50, 50), "go back", sf::Color::White, ClickFuncs::GoBack));
	newGame.AddInpField(InputField(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), sf::Color(150, 150, 150), 20));
	m.AddGui(newGame);
	m.OpenMenu(0);
	return m;
}
Gui* Menu::getOpenGui()
{
	return &guis[openMenu];
}