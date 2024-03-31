#include "Gui/Slider.hpp"
#include "Main.hpp"
Slider::Slider(sf::Vector2f pos, sf::Vector2f size, float dir, sf::Color bgCol, sf::Color filledCol, sf::Color knobCol)
{
	this->pos = pos;
	this->size = size;
	this->dir = dir;
	//clockwise from upwards
	this->dirVec = sf::Vector2f(cos(dir), sin(dir));
	bgRect = new sf::RectangleShape();
	bgRect->setFillColor(bgCol);
	knob = new sf::RectangleShape();
	knob->setFillColor(knobCol);
	filledRect = new sf::RectangleShape();
	filledRect->setFillColor(filledCol);
	value = 0.f;
	selected = false;
}
void Slider::Update()
{
	// std::cout << value << std::endl;
	if (inp.mbPressed(sf::Mouse::Button::Left))
	{
		//translate mouse pos so that rect is at origin
		sf::Vector2f t = inp.mousePos - sf::Vector2f(pos.x * width, pos.y * height);
		/*
		2d rotation matrix:
		cos x      - sin x
		sin x      cos x
		use this to rotate mouse by direction
		*/
		sf::Vector2f s(size.x * width, size.y * height);
		sf::Vector2f r(t.x * dirVec.x + t.y * dirVec.y, t.x * dirVec.y - t.y * dirVec.x);

		//sf::Vector2f r(t.x * dirVec.y - t.y * dirVec.x, t.x * dirVec.x + t.y * dirVec.y);
		sf::FloatRect bounds(0.f, -s.y / 2.f, s.x, s.y);
		if (r.x > bounds.left && r.x < bounds.width && r.y > bounds.top && r.y < bounds.height)
		{
			//mouse pos is in slider
			std::cout << "slider selected" << std::endl;
			selected = true;
			menu.getOpenGui()->mouseBlockedByGui = true;
			inp.RemoveMouseButtonPressed(sf::Mouse::Button::Left);
			inp.RemoveMouseButtonDown(sf::Mouse::Button::Left);
		}
	}
	if (selected)
	{
		sf::Vector2f screenPos = sf::Vector2f(pos.x * width, pos.y * height);
		sf::Vector2f v = inp.mousePos - screenPos;
		float dist = v.x * dirVec.x + v.y * dirVec.y;
		value = (float)dist / (size.x * width);
		if (inp.mbReleased(sf::Mouse::Button::Left))
		{
			selected = false;
		}
	}
}

void Slider::Render()
{
	sf::Vector2f sPos(pos.x * width, pos.y * height);
	sf::Vector2f sSize(size.x * width, size.y * height);
	bgRect->setPosition(sPos);
	bgRect->setRotation(dir * 180.f / b2_pi);
	bgRect->setSize(sSize);
	bgRect->setOrigin(0.f, sSize.y / 2.f);
	window->draw(*bgRect);
	filledRect->setPosition(sPos);
	filledRect->setRotation(dir * 180.f / b2_pi);
	filledRect->setSize(sf::Vector2f(sSize.x * value, sSize.y));
	filledRect->setOrigin(0.f, sSize.y / 2.f);
	window->draw(*filledRect);
	knob->setPosition(sPos + dirVec * value * sSize.x);
	knob->setRotation(dir * 180.f / b2_pi);
	knob->setSize(sf::Vector2f(sSize.y * 1.1f, sSize.y * 1.1f));
	knob->setOrigin(knob->getSize().x / 2.f, knob->getSize().y / 2.f);
	window->draw(*knob);
	// sf::Vector2f t = inp.mousePos - sf::Vector2f(pos.x * width, pos.y * height);
	// /*
	// 	2d rotation matrix:
	// 	cos x      - sin x
	// 	sin x      cos x
	// 	use this to rotate mouse by direction
	// 	*/
	// sf::Vector2f s(size.x * width, size.y * height);

	// sf::Vector2f r(t.x * dirVec.x + t.y * dirVec.y, t.x * dirVec.y - t.y * dirVec.x);
	// filledRect->setOrigin(0, 0);
	// filledRect->setSize(sf::Vector2f(3.f, 3.f));
	// filledRect->setPosition(r);
	// filledRect->setFillColor(sf::Color::White);
	// window->draw(*filledRect);
}