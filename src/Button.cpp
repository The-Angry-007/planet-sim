#include "include/Button.hpp"
#include "PCH.hpp"
#include "include/Main.hpp"
#include "include/inputHandler.hpp"
Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, std::string label)
{
	hasImageLabel = false;
	this->pos = pos;
	this->size = size;
	bg = new sf::RectangleShape();
	bg->setFillColor(col);
	textLabel = sf::Text();
	textLabel.setFont(*gui.defaultFont);
	textLabel.setString(label);
	textLabel.setFillColor(sf::Color::Black);
	onClickFunction = DefaultClickFunc;
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, sf::Texture image)
{
	hasImageLabel = true;
	this->pos = pos;
	this->size = size;
	bg = new sf::RectangleShape();
	bg->setFillColor(col);
	imageLabel = image;
	imageSprite = sf::Sprite(imageLabel);
	onClickFunction = DefaultClickFunc;
}
void Button::Render()
{
	sf::Vector2f adjustedPos(pos.x * gui.width, pos.y * gui.height);
	sf::Vector2f adjustedSize(size.x * gui.width, size.y * gui.height);
	bg->setPosition(adjustedPos);
	bg->setSize(adjustedSize);
	bg->setOrigin(adjustedSize / 2.f);
	window->draw(*bg);
	if (hasImageLabel)
	{
		imageSprite.setPosition(adjustedPos);
		float vert = adjustedSize.y / imageLabel.getSize().y;
		float horiz = adjustedSize.x / imageLabel.getSize().x;
		float scale = std::min(vert, horiz);
		sf::Vector2f size(scale * imageLabel.getSize().x, scale * imageLabel.getSize().y);

		imageSprite.setScale(sf::Vector2f(size.x / imageLabel.getSize().x, size.y / imageLabel.getSize().y));
		imageSprite.setOrigin(imageSprite.getLocalBounds().width / 2.f, imageSprite.getLocalBounds().height / 2.f);
		window->draw(imageSprite);
	}
	else
	{
		sf::Vector2f padding(0.01f * gui.width, 0.01f * gui.height);
		textLabel.setPosition(adjustedPos);
		//binary search to find text size that fits within bounds
		int min = 1;
		int max = 100;
		while (true)
		{
			if (min == max)
			{
				break;
			}
			int guess = (min + max) / 2;
			textLabel.setCharacterSize(guess);
			sf::FloatRect size = textLabel.getLocalBounds();
			if (size.width + size.left > adjustedSize.x - padding.x || size.height + size.top > adjustedSize.y - padding.y)
			{
				max = guess;
			}
			else
			{
				min = guess + 1;
			}
		}
		sf::FloatRect bounds = textLabel.getLocalBounds();
		textLabel.setOrigin((bounds.width + bounds.left) / 2.f, (bounds.height + bounds.top) / 2.f);
		window->draw(textLabel);
	}
}

bool Button::clicked()
{
	if (inp.mbPressed(sf::Mouse::Button::Left) && mouseOverButton())
	{
		onClickFunction();
		return true;
	}
	return false;
}
void Button::AssignOnClick(std::function<void()> func)
{
	onClickFunction = func;
}
Button::~Button()
{
	delete bg;
}
void DefaultClickFunc()
{}

bool Button::mouseOverButton()
{
	sf::Vector2f topLeft((pos.x - size.x / 2.f) * gui.width, (pos.y - size.y / 2.f) * gui.height);
	sf::Vector2f bottomRight((pos.x + size.x / 2.f) * gui.width, (pos.y + size.y / 2.f) * gui.height);
	return (inp.mousePos.x >= topLeft.x && inp.mousePos.x <= bottomRight.x && inp.mousePos.y >= topLeft.y && inp.mousePos.y <= bottomRight.y);
}