#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class CustomCircleShape: public sf::CircleShape
{
public:
	CustomCircleShape(float radius = 100);
	bool isCursorHovering(const sf::Window &window);

};

