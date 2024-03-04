#include "CustomRectangleShape.h"
#include <SFML/Window/Mouse.hpp>

CustomRectangleShape::CustomRectangleShape(sf::Vector2f size) : RectangleShape(size) {}

bool CustomRectangleShape::isCursorHovering(const sf::Window& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f rectPosition = sf::RectangleShape::getPosition();
    //sf::Vector2f actualRectPosition = rectPosition + sf::Vector2f(100, 100);
    sf::Vector2f rectSize = sf::RectangleShape::getSize();

    float rectLeft = rectPosition.x;
    float rectRight = rectPosition.x + rectSize.x;
    float rectTop = rectPosition.y;
    float rectBottom = rectPosition.y + rectSize.y;

    return (mousePosition.x >= rectLeft && mousePosition.x <= rectRight &&
        mousePosition.y >= rectTop && mousePosition.y <= rectBottom);
}