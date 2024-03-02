#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"

#include <unordered_set>
#include <memory>

#define ShapeUPointer std::unique_ptr<sf::Shape>

bool secondPassed(sf::Clock &clock) {
    bool result = false;
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asSeconds() >= 1.0f) {
        clock.restart();
        result = true;
    }
    return result;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sharp edges");
    CustomCircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;

    std::unordered_set<ShapeUPointer> shapes;

    while (window.isOpen())
    {
        sf::Event event;

        if (secondPassed(clock)) {
            shape.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getRadius() / 2));
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                shape.isCursorHovering(window) && 
                (event.mouseButton.button == sf::Mouse::Left)) {
                if (shape.getFillColor() == sf::Color::Green) {
                    shape.setFillColor(sf::Color::Blue);
                }
                else {
                    shape.setFillColor(sf::Color::Green);
                }
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}