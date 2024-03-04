#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class CustomRectangleShape : public sf::RectangleShape
{
public:
	CustomRectangleShape(sf::Vector2f size = {100, 100});
	bool isCursorHovering(const sf::Window& window);

};


