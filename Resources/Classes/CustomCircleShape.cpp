#include "CustomCircleShape.h"
#include <SFML/Window/Mouse.hpp>

CustomCircleShape::CustomCircleShape(float radius) : CircleShape(radius) {}

bool CustomCircleShape::isCursorHovering(const sf::Window &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    //sf::CircleShape::getPosition() returns uper right corner of the shape
    sf::Vector2f circlePosition = sf::CircleShape::getPosition();
    //Since we want the middle of the shape for calculations, we move the position x and y by the value of radius
    sf::Vector2f circleMiddlePosition = {circlePosition.x + sf::CircleShape::getRadius(), circlePosition.y + sf::CircleShape::getRadius() };
    float circleRadius = sf::CircleShape::getRadius();

    float distanceSquared = (mousePosition.x - circleMiddlePosition.x) * (mousePosition.x - circleMiddlePosition.x) +
        (mousePosition.y - circleMiddlePosition.y) * (mousePosition.y - circleMiddlePosition.y);

    return (distanceSquared <= circleRadius * circleRadius);
}
