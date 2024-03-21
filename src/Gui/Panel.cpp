#include "gui/Panel.hpp"
#include "Main.hpp"
Panel::Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color col)
{
	this->col = col;
	sf::Vector2f hs = size / 2.f;
	this->bounds = sf::FloatRect(pos.x - hs.x, pos.y - hs.y, pos.x + hs.x, pos.y + hs.y);
	panel.setFillColor(col);
}
Panel::Panel(sf::FloatRect bounds, sf::Color col)
{
	this->col = col;
	this->bounds = bounds;
	panel.setFillColor(col);
}
void Panel::Render()
{
	panel.setPosition(bounds.left * gui.width, bounds.top * gui.height);
	panel.setSize(sf::Vector2f(bounds.width * gui.width, bounds.height * gui.height));
	window->draw(panel);
}