#pragma once
class Button;
class Label;
//in the load game menu, this is the object that represents
//each slot
class SaveSlot
{
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	Button* button;
	std::vector<Label*> labels;
	std::string path;
	SaveSlot(std::string path, sf::Vector2f pos, sf::Vector2f size);
	~SaveSlot();
	void Render();
	void Update();
	void Move(sf::Vector2f amt);
};