#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window.hpp>
class CustomShape: public sf::Shape
{
public: 
	virtual bool isCursorHovering(sf::Window window) = 0;
};

