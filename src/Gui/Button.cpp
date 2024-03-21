#include "Gui/Button.hpp"
#include "Main.hpp"
#include "PCH.hpp"
#include "inputHandler.hpp"
#include "utils.hpp"
Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, std::string label, sf::Color labelCol, std::function<void()> onClick)
{
	hasImageLabel = false;
	this->pos = pos;
	this->size = size;
	bg = new sf::RectangleShape();
	bg->setFillColor(col);
	textLabel = sf::Text();
	textLabel.setFont(*defaultFont);
	textLabel.setString(label);
	textLabel.setFillColor(labelCol);
	onClickFunction = onClick;
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, sf::Texture image, std::function<void()> onClick)
{
	hasImageLabel = true;
	this->pos = pos;
	this->size = size;
	bg = new sf::RectangleShape();
	bg->setFillColor(col);
	imageLabel = image;
	imageSprite = sf::Sprite(imageLabel);
	onClickFunction = onClick;
}
void Button::Render()
{
	sf::Vector2f adjustedPos(pos.x * width, pos.y * height);
	sf::Vector2f adjustedSize(size.x * width, size.y * height);
	bg->setPosition(adjustedPos);
	bg->setSize(adjustedSize);
	bg->setOrigin(adjustedSize / 2.f);
	window->draw(*bg);
	if (hasImageLabel)
	{
		imageSprite.setTexture(imageLabel);
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
		sf::Vector2f padding(0.01f * width, 0.01f * height);
		textLabel.setPosition((int)adjustedPos.x, (int)adjustedPos.y);
		//binary search to find text size that fits within bounds
		GetMaxFontSize(&textLabel, sf::Vector2f(adjustedSize.x - padding.x, adjustedSize.y - padding.y));
		sf::FloatRect bounds = textLabel.getLocalBounds();
		textLabel.setOrigin((int)((bounds.width + bounds.left) / 2.f), (int)((bounds.height + bounds.top) / 2.f));
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
	//delete this->bg;
}
void DefaultClickFunc()
{}

bool Button::mouseOverButton()
{
	sf::Vector2f topLeft((pos.x - size.x / 2.f) * width, (pos.y - size.y / 2.f) * height);
	sf::Vector2f bottomRight((pos.x + size.x / 2.f) * width, (pos.y + size.y / 2.f) * height);
	return (inp.mousePos.x >= topLeft.x && inp.mousePos.x <= bottomRight.x && inp.mousePos.y >= topLeft.y && inp.mousePos.y <= bottomRight.y);
}