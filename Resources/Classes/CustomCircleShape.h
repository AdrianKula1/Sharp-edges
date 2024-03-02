#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class CustomCircleShape: public sf::CircleShape
{
public:
	CustomCircleShape(float radius = 0);
	bool isCursorHovering(sf::Window &window);

};

