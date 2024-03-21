#pragma once
#include "include/Button.hpp"
void AddClicked();
void SelectClicked();
void DeleteClicked();
class Gui
{
public:
	sf::Font* defaultFont;
	int width;
	int height;
	std::vector<Button*> buttons;
	//maybe switch this to enum when i figure out how it works
	int mode;
	void Render(float dt);
	void Update();
	//whenever the mouse is over a button, it shouldnt select a planet behind the button or otherwise.
	bool mouseBlockedByGui;
	//to prevent weird sfml glitch where textures cause errors before renderwindow handle generated.
	void Init();
	int selectedPlanet;
	Gui();
	~Gui();

private:
	//returns the index of the planet being hovered over, -1 if none
	int HoveringOverPlanet();
};