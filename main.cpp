#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sharp edges");
    CustomCircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        sf::Time elapsedTime = clock.getElapsedTime();

        if (elapsedTime.asSeconds() >= 1.0f) {
            shape.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getRadius() / 2));
            clock.restart();
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