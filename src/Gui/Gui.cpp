#include "Gui/Gui.hpp"
#include "Main.hpp"
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
	fpsLabel = new Label("", sf::FloatRect(0.f, 0.f, 0.1f, 0.05f), sf::Color::White);
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
	Panel panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(100, 100, 100));
	panel.Render();
	Label testLabel("behind this text is a grey panel", sf::Vector2f(0.5f, 0.5f), sf::Vector2f(1.f, 1.f), sf::Color::White);
	testLabel.Render();
	this->width = window->getSize().x;
	this->height = window->getSize().y;
	this->RenderFps(dt);
	for (uint i { 0 }; i < buttons.size(); i++)
	{
		buttons[i]->Render();
	}
}
void Gui::RenderFps(float dt)
{
	int fps = 1.f / dt;
	fpsLabel->SetText(std::to_string(fps) + "fps");
	fpsLabel->Render();
}
Gui::~Gui()
{
	delete defaultFont;
	for (uint i { 0 }; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}
