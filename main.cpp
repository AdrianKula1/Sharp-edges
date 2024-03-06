#include <SFML/Graphics.hpp>
#include "Resources/Classes/CustomCircleShape.h"
#include "Resources/Classes/CustomRectangleShape.h"

#include <unordered_set>
#include <memory>
#include <random>
#include <iostream>

#define SHAPE_UPOINTER_TYPE std::unique_ptr<sf::Shape>
#define SHAPE_SIZE 100

enum shapeType {
    NONE = 0,
    CIRCLE,
    RECTANGLE
};

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

void drawAllShapes(sf::RenderWindow &window, std::unordered_set<SHAPE_UPOINTER_TYPE> &shapes) {
    for (const SHAPE_UPOINTER_TYPE &shape : shapes) {
        window.draw(*shape);
    }
}

void makeAllShapesFall(std::unordered_set<SHAPE_UPOINTER_TYPE>& shapes) {
    for (const SHAPE_UPOINTER_TYPE& shape : shapes) {
        shape->setPosition(shape->getPosition().x, shape->getPosition().y + (SHAPE_SIZE / 2));
    }    
}

void eraseShape(std::unordered_set<SHAPE_UPOINTER_TYPE>& shapes, std::unordered_set<SHAPE_UPOINTER_TYPE>::iterator shapeToErase) {
    shapes.erase(shapeToErase);
}

shapeType shapeClickedEvent(const sf::RenderWindow &window, std::unordered_set<SHAPE_UPOINTER_TYPE> &shapes) {
    std::unordered_set<SHAPE_UPOINTER_TYPE>::iterator shapeToErase = shapes.end();
    shapeType typeOfShape = NONE;
    for (const SHAPE_UPOINTER_TYPE& shape : shapes) {

        CustomRectangleShape* square = dynamic_cast<CustomRectangleShape*>(shape.get());
        CustomCircleShape* circle = dynamic_cast<CustomCircleShape*>(shape.get());

        if (square) {
            if (square->isCursorHovering(window)) {
                shapeToErase = shapes.find(shape);
                typeOfShape = RECTANGLE;
                break;
            }
        }
        else if (circle) {
            if (circle->isCursorHovering(window)) {
                shapeToErase = shapes.find(shape);
                typeOfShape = CIRCLE;
                break;
            }
        } 
    }

    if (shapeToErase != shapes.end()) {
        eraseShape(shapes, shapeToErase);
    }

    return typeOfShape;
}

void addNewShape(const sf::RenderWindow& window, std::unordered_set<SHAPE_UPOINTER_TYPE>& shapes) {
    int shapeToAdd = rand() % 2;
    std::unique_ptr<sf::Shape> newShape;
    if (shapeToAdd) {
        newShape = std::make_unique<CustomCircleShape>();
    }
    else {
        newShape = std::make_unique<CustomRectangleShape>();
    }
    sf::Color randomColor = sf::Color(
        std::rand() % 256, //Red
        std::rand() % 256, //Green
        std::rand() % 256  //Blue
    );
    newShape->setFillColor(randomColor);

    int StartPositionX = rand() % (window.getSize().x - SHAPE_SIZE);
    int StartPositionY = 0;
    newShape->setPosition(StartPositionX, StartPositionY);

    shapes.insert(std::move(newShape));
}

void checkAndEraseShapesAtBottom(const sf::RenderWindow& window, std::unordered_set<SHAPE_UPOINTER_TYPE>& shapes) {
    std::unordered_set<SHAPE_UPOINTER_TYPE>::iterator shapeToErase = shapes.end();
    for (const SHAPE_UPOINTER_TYPE& shape : shapes) {
        if (shape->getPosition().y >= (window.getSize().y - SHAPE_SIZE)) {
            shapeToErase = shapes.find(shape);
            break;
        }
    }

    if (shapeToErase != shapes.end()) {
        eraseShape(shapes, shapeToErase);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sharp edges");

    sf::Clock clock1s;
    sf::Clock clock3s;

    std::unordered_set<SHAPE_UPOINTER_TYPE> shapes;


    // Create text object for counter
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font " << std::endl;
    }

    sf::Text counterText;
    counterText.setFont(font); // Using default font
    counterText.setCharacterSize(30);
    counterText.setFillColor(sf::Color::White);
    counterText.setPosition(0, 0);
    int counter = 0;


    while (window.isOpen())
    {
        //New shape appears every 3 seconds
        if (threeSecondsPassed(clock3s)) {
            addNewShape(window, shapes);
        }

        //All shapes fall each second
        if (oneSecondPassed(clock1s)) {
            makeAllShapesFall(shapes);
        }

        //See if any shape reached the bottom. If so, erase it
        checkAndEraseShapesAtBottom(window, shapes);


        //Detect user action
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if ( (event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)){
                shapeType clickedShapeType = shapeClickedEvent(window, shapes);
                if (clickedShapeType == RECTANGLE) {
                    counter--;
                }
                else if (clickedShapeType == CIRCLE) {
                    counter++;
                }
            }   
        }

      
        
        //Set the string of score
        counterText.setString("Score: " + std::to_string(counter));


        window.clear();
        window.draw(counterText);
        drawAllShapes(window, shapes);
        window.display();
    }

    return 0;
}