#include "include/Gui.hpp"
#include "include/Button.hpp"
#include "include/Main.hpp"
#include "include/inputHandler.hpp"
#include "include/utils.hpp"
void AddClicked()
{
	gui.mode = 0;
}
void SelectClicked()
{
	gui.mode = 1;
}
void DeleteClicked()
{
	gui.mode = 2;
}
Gui::Gui()
{
}

void Gui::Init()
{
	selectedPlanet = -1;
	this->defaultFont = new sf::Font();
	if (!this->defaultFont->loadFromFile("src/fonts/NotoSansMono-Regular.ttf"))
	{
		std::cout << "failed to load" << std::endl;
	}
	buttons.push_back(new Button(sf::Vector2f(0.2f, 0.9f), sf::Vector2f(0.2f, 0.08f), sf::Color::White, "Add Planet"));
	buttons[0]->AssignOnClick(AddClicked);
	buttons.push_back(new Button(sf::Vector2f(0.5f, 0.9f), sf::Vector2f(0.2f, 0.08f), sf::Color::White, "Select Planet"));
	buttons[1]->AssignOnClick(SelectClicked);
	buttons.push_back(new Button(sf::Vector2f(0.8f, 0.9f), sf::Vector2f(0.2f, 0.08f), sf::Color::White, "Delete Planet"));
	buttons[2]->AssignOnClick(DeleteClicked);
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
	if (mode == 1)
	{
		int hovering = HoveringOverPlanet();
		if (hovering != -1)
		{
			Planet* target = planets[hovering];
			sf::Vector2f pos = target->pos;
			float radius = target->radius;
			float thickness = 3.f;
			float len = 0.3f;
			sf::Color col = sf::Color::White;
			sf::Vector2f directions[4] = {
				{ -1, -1 }, // Top left
				{ 1, -1 },	// Top right
				{ -1, 1 },	// Bottom left
				{ 1, 1 }	// Bottom right
			};

			for (auto& dir : directions)
			{
				// Calculate the starting point for the lines at each corner
				sf::Vector2f cornerStart(pos.x + radius * dir.x, pos.y + radius * dir.y);

				// Draw the horizontal line for this corner
				drawLine(cornerStart, sf::Vector2f(cornerStart.x, cornerStart.y - radius * dir.y * len), thickness, col);

				// Draw the vertical line for this corner
				drawLine(cornerStart, sf::Vector2f(cornerStart.x - radius * dir.x * len, cornerStart.y), thickness, col);
			}
		}
	}
	//drawLine(sf::Vector2f(0, 0), sf::Vector2f(width, height), 3.f, sf::Color::White);
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
	if (selectedPlanet != -1)
	{
		//then draw some stats here, maybe velocity, etc etc idk what else :|
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

int Gui::HoveringOverPlanet()
{
	for (uint i { 0 }; i < planets.size(); i++)
	{
		sf::Vector2f d = inp.mousePos - planets[i]->pos;
		if (d.x * d.x + d.y * d.y <= planets[i]->radius * planets[i]->radius)
		{
			return i;
		}
	}
	return -1;
}