#include "Gui/Label.hpp"
#include "Main.hpp"
#include "utils.hpp"
Label::Label(std::string text, sf::FloatRect bounds, sf::Color col)
{
	this->text = text;
	this->bounds = bounds;
	this->col = col;
	label.setFont(*gui.defaultFont);
	label.setString(text);
}
Label::Label(std::string text, sf::Vector2f pos, sf::Vector2f size, sf::Color col)
{
	this->text = text;
	this->bounds = sf::FloatRect(pos.x - size.x / 2.f, pos.y - size.y / 2.f, pos.x + size.x / 2.f, pos.y + size.y / 2.f);
	this->col = col;
	label.setFont(*gui.defaultFont);
	label.setString(text);
}
void Label::SetText(std::string text)
{
	label.setString(text);
}
void Label::SetCol(sf::Color col)
{
	label.setFillColor(col);
}
void Label::Render()
{
	GetMaxFontSize(label, sf::Vector2f(bounds.width * gui.width, bounds.height * gui.height));
	sf::FloatRect tBounds = label.getLocalBounds();
	label.setOrigin((tBounds.left + tBounds.width) / 2.f, (tBounds.top + tBounds.height) / 2.f);
	label.setPosition((bounds.left + bounds.width / 2.f) * gui.width, (bounds.top + bounds.height / 2.f) * gui.height);
	window->draw(label);
}