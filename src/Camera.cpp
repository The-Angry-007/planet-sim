#include "Camera.hpp"
#include "Main.hpp"
Camera::Camera(sf::Vector2f pos, float zoom)
{
	this->pos = pos;
	this->zoom = zoom;
	view = sf::View(toFloatRect());
	zoomRate = 0.05f;
	windowSize = sf::Vector2u(0, 0);
}
void Camera::Update()
{
	//fix window size
	if (window->getSize() != windowSize)
	{
		windowSize = window->getSize();
		width = windowSize.x;
		height = windowSize.y;
	}
	if (inp.mbDown(sf::Mouse::Button::Middle))
	{
		sf::Vector2f offset = (prevMousePos - inp.mousePos) * zoom;
		pos += offset;
	}
	if (inp.scroll.y != 0)
	{
		float oldZoom = zoom;
		zoom -= zoomRate * inp.scroll.y;
		// // Adjust camera position to keep the point under the mouse stationary
		// sf::Vector2f mousePosRelativeToView = window->mapPixelToCoords(static_cast<sf::Vector2i>(inp.mousePos));
		// sf::Vector2f adjustment = (mousePosRelativeToView - pos) * (1 - (zoom / oldZoom));
		// pos += adjustment;
		if (zoom < 0.1f)
		{
			zoom = 0.1f;
		}
	}
	view = sf::View(toFloatRect());
	window->setView(view);
	prevMousePos = inp.mousePos;
}
void Camera::RenderMenu(Menu menu, double dt)
{
	sf::View menuView(sf::FloatRect(0.f, 0.f, width, height));
	window->setView(menuView);
	menu.Render(dt);
}
sf::FloatRect Camera::toFloatRect()
{
	return sf::FloatRect(pos.x - width * zoom / 2.f, pos.y - height * zoom / 2.f, width * zoom, height * zoom);
}