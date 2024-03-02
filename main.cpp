#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"

#include <unordered_set>
#include <memory>
#include <random>

#define ShapeUPointer std::shared_ptr<sf::Shape>
#define ShapeSize 100


bool oneSecondPassed(sf::Clock &clock) {
    bool result = false;
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asSeconds() >= 1.0f) {
        clock.restart();
        result = true;
    }
    return result;
}
bool threeSecondsPassed(sf::Clock &clock) {
    bool result = false;
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asSeconds() >= 3.0f) {
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

void makeAllShapesFall(std::unordered_set<ShapeUPointer>& shapes) {
    for (const ShapeUPointer& shape : shapes) {
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + (ShapeSize / 2));
    }    
}


void shapeClicked(const sf::RenderWindow &window, std::unordered_set<ShapeUPointer> &shapes) {
    std::unordered_set<ShapeUPointer>::iterator shapeToErase;
    for (const ShapeUPointer& shape : shapes) {
        auto customCircleShape = std::dynamic_pointer_cast<CustomCircleShape>(shape);
        if (customCircleShape->isCursorHovering(window)) {
            shapeToErase = shapes.find(shape);
        }
    }

    shapes.erase(shapeToErase);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sharp edges");
    CustomCircleShape shape(100.0f);
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock1s;
    sf::Clock clock3s;

    std::unordered_set<ShapeUPointer> shapes;

    while (window.isOpen())
    {
        sf::Event event;

        if (oneSecondPassed(clock1s)) {
            shape.setPosition(shape.getPosition().x, shape.getPosition().y + (ShapeSize / 2));
            makeAllShapesFall(shapes);
        }

        if (threeSecondsPassed(clock3s)) {
            std::unique_ptr<CustomCircleShape> newShape = std::make_unique<CustomCircleShape>(100);
            sf::Color randomColor = sf::Color(
                std::rand() % 256, //Red
                std::rand() % 256, //Green
                std::rand() % 256  //Blue
            );
            newShape->setFillColor(randomColor);
            int StartPositionX = rand() % (window.getSize().x - ShapeSize);
            int StartPositionY = 0;
            newShape->setPosition(StartPositionX, StartPositionY);
            shapes.insert(std::move(newShape));
        }

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if ( (event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)){
                shapeClicked(window, shapes);
            }   
        }
        
        window.clear();
        window.draw(shape);
        drawAllShapes(window, shapes);
        window.display();
    }

    return 0;
}