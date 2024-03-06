#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"
#include "Resources/Classes/CustomRectangleShape.h"

#include <unordered_set>
#include <memory>
#include <random>
#include <iostream>

#define ShapeUPointer std::unique_ptr<sf::Shape>
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

void eraseShape(std::unordered_set<ShapeUPointer>& shapes, std::unordered_set<ShapeUPointer>::iterator shapeToErase) {
    shapes.erase(shapeToErase);
}

void shapeClicked(const sf::RenderWindow &window, std::unordered_set<ShapeUPointer> &shapes) {
    std::unordered_set<ShapeUPointer>::iterator shapeToErase = shapes.end();
    for (const ShapeUPointer& shape : shapes) {

        CustomRectangleShape* square = dynamic_cast<CustomRectangleShape*>(shape.get());
        CustomCircleShape* circle = dynamic_cast<CustomCircleShape*>(shape.get());

        if (square) {
            if (square->isCursorHovering(window)) {
                shapeToErase = shapes.find(shape);
                break;
            }
        }
        else if (circle) {
            if (circle->isCursorHovering(window)) {
                shapeToErase = shapes.find(shape);
                break;
            }
        } 
    }


    if (shapeToErase != shapes.end()) {
        eraseShape(shapes, shapeToErase);
    }
    
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
            int shapeToAdd = rand() % 2;
            std::unique_ptr<sf::Shape> newShape;
            if (shapeToAdd) {
                newShape = std::make_unique<CustomCircleShape>();
            }else {
                newShape = std::make_unique<CustomRectangleShape>();
            }
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

        std::unordered_set<ShapeUPointer>::iterator shapeToErase = shapes.end();
        for (const ShapeUPointer& shape : shapes) {
            if (shape->getPosition().y >= (window.getSize().y - ShapeSize)) {
                shapeToErase = shapes.find(shape);
                break;
            }   
        }
        if (shapeToErase != shapes.end()) {
            eraseShape(shapes, shapeToErase);
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