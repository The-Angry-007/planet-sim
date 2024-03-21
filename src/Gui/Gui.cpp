#include "Gui/Gui.hpp"
#include "Gui/Button.hpp"
#include "Main.hpp"
#include "gui/Label.hpp"
#include "inputHandler.hpp"
#include "utils.hpp"
Gui::Gui()
{
}

void Gui::Init()
{
	this->defaultFont = new sf::Font();
	if (!this->defaultFont->loadFromFile("resources/fonts/NotoSansMono-Regular.ttf"))
	{
		std::cout << "failed to load" << std::endl;
	}
}
void Gui::AddButton(Button* button)
{
	buttons.push_back(button);
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
	Label testLabel("testing", sf::Vector2f(0.5f, 0.5f), sf::Vector2f(1.f, 1.f), sf::Color::White);
	testLabel.Render();
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
