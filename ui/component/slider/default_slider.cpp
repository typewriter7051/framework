#include "default_slider.h"

DefaultSlider::DefaultSlider(Scene* scene) {

    // Defaults
    clickLock = false;
    isLifted = false;
    value = 0;

    // Appearance
    knobRadius = 50;
    s = 0.001;
    lineThickness = 2;
    knobRadius = 10;
    lineLength = 400;
    lineColor = sf::Color(150, 150, 150);

    scene->addUIElement(this);

    knobColor = sf::Color(255, 255, 255, 200);
    lineColor = sf::Color(150, 180, 255);

}



void DefaultSlider::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    prevLifted = isLifted;
    prevClickLock = clickLock;

    sf::Vector2f locPos = info.pos + pos;

    bool withinWidth = (ms.pos.x > locPos.x) && (ms.pos.x < locPos.x + lineLength);
    bool withinHeight = (ms.pos.y > locPos.y - knobRadius) && (ms.pos.y < locPos.y + knobRadius);

    if (withinWidth && withinHeight) {

        knobColor = sf::Color(255, 255, 255);

        if (ms.lButtonDown) {

            if (!clickLock) {

                prevMousePos = ms.pos;
                clickLock = true;

            }

            isLifted = true;

        }
        else {

            isLifted = false;
            clickLock = false;

        }

    }
    else {

        if (!ms.lButtonDown) {

            isLifted = false;

        }

        knobColor = sf::Color(200, 200, 200);

    }

    if (isLifted) {

        if (isVertical) {

            value += (ms.pos.y - prevMousePos.y) * s;

        }
        else {

            value += (ms.pos.x - prevMousePos.x) * s;

        }
        prevMousePos = ms.pos;

        if (value < 0) value = 0;
        if (value > 1) value = 1;

        hideMouse = true;

    }
    else {

        hideMouse = false;

    }

    if (prevLifted && !isLifted) {

        positionMouse = true;

    }

}



void DefaultSlider::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::RectangleShape rect;
    sf::CircleShape knobCircle;

    if (isVertical) {

        rect.setPosition(locPos.x - lineThickness / 2.0f, locPos.y);
        rect.setSize(sf::Vector2f(lineThickness, lineLength));

        double xPos = locPos.x;
        double yPos = locPos.y;
        knobCircle.setPosition(xPos - knobRadius, yPos + value * lineLength - knobRadius);

    }
    else {

        rect.setPosition(locPos.x, locPos.y - lineThickness / 2.0f);
        rect.setSize(sf::Vector2f(lineLength, lineThickness));

        double xPos = locPos.x;
        double yPos = locPos.y;
        knobCircle.setPosition(xPos + value * lineLength - knobRadius, yPos - knobRadius);

    }

    if (clickLock && !prevClickLock) {

        grabbedMousePos = sf::Mouse::getPosition(*window);

    }

    if (positionMouse) {

        sf::Mouse::setPosition(grabbedMousePos, *window);
        positionMouse = false;

    }

    rect.setFillColor(lineColor);

    knobCircle.setRadius(knobRadius);
    knobCircle.setFillColor(knobColor);

    window->draw(rect);
    window->draw(knobCircle);

}