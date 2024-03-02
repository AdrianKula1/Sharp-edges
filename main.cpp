#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"

#include <unordered_set>
#include <memory>
#include <random>

#define ShapeUPointer std::unique_ptr<sf::Shape>
#define ShapeSize 100


bool secondPassed(sf::Clock &clock) {
    bool result = false;
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asSeconds() >= 1.0f) {
        clock.restart();
        result = true;
    }
    return result;
}

void drawAllShapes(sf::RenderWindow &window, std::unordered_set<ShapeUPointer> &shapes) {
    for (const ShapeUPointer &shape : shapes) {
        window.draw((*shape));
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sharp edges");
    CustomCircleShape shape(100.0f);
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;

    std::unordered_set<ShapeUPointer> shapes;

    while (window.isOpen())
    {
        sf::Event event;



        if (secondPassed(clock)) {
            shape.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getRadius() / 2));

            std::unique_ptr<CustomCircleShape> newShape = std::make_unique<CustomCircleShape>(100);
            newShape->setFillColor(sf::Color::Red);
            int StartPositionX = rand() % (window.getSize().x - ShapeSize);
            int StartPositionY = 0;
            newShape->setPosition(StartPositionX, StartPositionY);
            shapes.insert(std::move(newShape));
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
        drawAllShapes(window, shapes);
        window.display();
    }

    return 0;
}