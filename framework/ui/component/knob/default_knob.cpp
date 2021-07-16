#include "default_knob.h"

DefaultKnob::DefaultKnob(Scene* scene) {

    // Defaults
    clickLock = false;
    isLifted = false;
    value = 0;

    // Appearance
    radius = 50;
    s = 0.01;

    scene->addUIElement(this);

    pointerColor = sf::Color(255, 255, 255, 200);
    outlineColor = sf::Color(150, 180, 255);

}



void DefaultKnob::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    float dx = ms.pos.x - locPos.x;
    float dy = ms.pos.y - locPos.y;

    if (sqrt(dx * dx + dy * dy) < radius) {

        pointerColor = sf::Color(255, 255, 255, 255);

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

        pointerColor = sf::Color(255, 255, 255, 200);

    }

    if (isLifted) {

        value += (ms.pos.y - prevMousePos.y) * s;
        prevMousePos = ms.pos;

        if (value < 0) value = 0;
        if (value > 1) value = 1;

        hideMouse = true;

    }
    else {

        hideMouse = false;

    }

}



void DefaultKnob::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::CircleShape c;
    c.setRadius(radius);
    c.setOutlineThickness(20 * value + 5);
    c.setPosition(locPos.x - radius, locPos.y - radius);
    c.setFillColor(outlineColor);

    window->draw(c);

}