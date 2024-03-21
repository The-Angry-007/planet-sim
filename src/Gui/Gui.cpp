#include "Gui/Gui.hpp"
#include "Main.hpp"
#include "inputHandler.hpp"
#include "utils.hpp"
Gui::Gui()
{
}

void Gui::Init()
{
	fpsLabel = new Label("", sf::FloatRect(0.f, 0.f, 0.1f, 0.05f), sf::Color::White);
}
void Gui::AddButton(Button button)
{
	buttons.push_back(button);
}
void Gui::Update()
{
	mouseBlockedByGui = false;
	//this is backwards because the buttons most visible should have priority, this was implemented because the moon in the background of the main menu is
	//actually a button (i got lazy)
	for (int i = (int)buttons.size() - 1; i >= 0; i--)
	{
		if (this->buttons[i].clicked())
		{
			inp.RemoveMouseButtonPressed(sf::Mouse::Button::Left);
			inp.RemoveMouseButtonDown(sf::Mouse::Button::Left);
		}
		if (this->buttons[i].mouseOverButton())
		{
			mouseBlockedByGui = true;
		}
	}
	for (uint i = 0; i < panels.size(); i++)
	{
		if (panels[i].MouseOver())
		{
			mouseBlockedByGui = true;
		}
	}
}
void Gui::Render(float dt)
{
	this->RenderFps(dt);
	for (uint i { 0 }; i < buttons.size(); i++)
	{
		buttons[i].Render();
	}
	for (uint i { 0 }; i < labels.size(); i++)
	{
		labels[i].Render();
	}
	for (uint i { 0 }; i < panels.size(); i++)
	{
		panels[i].Render();
	}
}
void Gui::RenderFps(float dt)
{
	dt = dt;
	int fps = 1.f / dt;
	fpsLabel->SetText(std::to_string(fps) + "fps");
	fpsLabel->Render();
}

Gui::~Gui()
{
}
void Gui::AddLabel(Label label)
{
	labels.push_back(label);
}
void Gui::AddPanel(Panel panel)
{
	panels.push_back(panel);
}