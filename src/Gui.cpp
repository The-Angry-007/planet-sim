#include "include/Gui.hpp"
#include "include/Button.hpp"
#include "include/Main.hpp"
#include "include/inputHandler.hpp"
#include "include/utils.hpp"
void AddClicked()
{
}
void SelectClicked()
{
}
void DeleteClicked()
{
}
Gui::Gui()
{
}

void Gui::Init()
{
	this->defaultFont = new sf::Font();
	if (!this->defaultFont->loadFromFile("src/fonts/NotoSansMono-Regular.ttf"))
	{
		std::cout << "failed to load" << std::endl;
	}
}

void Gui::Update()
{
	mouseBlockedByGui = false;
	for (uint i = 0; i < buttons.size(); i++)
	{
		if (this->buttons[i]->clicked())
		{
			inp.RemoveMouseButtonPressed(sf::Mouse::Button::Left);
			inp.RemoveMouseButtonDown(sf::Mouse::Button::Left);
		}
		if (this->buttons[i]->mouseOverButton())
		{
			mouseBlockedByGui = true;
		}
	}
}
void Gui::Render(float dt)
{
	this->width = window->getSize().x;
	this->height = window->getSize().y;
	int fps = 1.f / dt;
	sf::Text text;
	text.setFont(*this->defaultFont);
	text.setString(std::to_string(fps) + "fps");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);
	window->draw(text);
	for (uint i { 0 }; i < buttons.size(); i++)
	{
		buttons[i]->Render();
	}
}

Gui::~Gui()
{
	delete defaultFont;
	for (uint i { 0 }; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}
