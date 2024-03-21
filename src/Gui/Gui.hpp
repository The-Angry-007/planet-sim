#pragma once
#include "Gui/Button.hpp"
#include "Gui/Label.hpp"
#include "Gui/Panel.hpp"
void AddClicked();
void SelectClicked();
void DeleteClicked();
class Gui
{
public:
	Label* fpsLabel;

	void Render(float dt);
	void Update();

	//whenever the mouse is over a button, it shouldnt select a planet behind the button or otherwise.
	bool mouseBlockedByGui;
	//to prevent weird sfml glitch where textures cause errors before renderwindow handle generated.
	void Init();

	void AddButton(Button button);
	void AddLabel(Label label);
	void AddPanel(Panel panel);
	void RenderFps(float dt);
	Gui();
	~Gui();

private:
	std::vector<Button> buttons;
	std::vector<Label> labels;
	std::vector<Panel> panels;
};