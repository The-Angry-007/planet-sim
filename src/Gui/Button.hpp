#pragma once
class Button
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, sf::Texture image);
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, std::string label);
	void Render();
	bool clicked();
	void AssignOnClick(std::function<void()> func);
	bool mouseOverButton();
	~Button();

private:
	std::function<void()> onClickFunction;

	//between 0 and 1, where 0 is left of screen and 1 is right
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape* bg;
	sf::Text textLabel;
	sf::Texture imageLabel;
	sf::Sprite imageSprite;
	bool hasImageLabel;
};
void DefaultClickFunc();