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
	void Render(float dt);
	void Update();
	//whenever the mouse is over a button, it shouldnt select a planet behind the button or otherwise.
	bool mouseBlockedByGui;
	//to prevent weird sfml glitch where textures cause errors before renderwindow handle generated.
	void Init();
	Gui();
	~Gui();
};