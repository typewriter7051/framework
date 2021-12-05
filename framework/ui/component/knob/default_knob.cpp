#include "default_knob.h"

DefaultKnob::DefaultKnob(Scene* scene) {

    // Defaults
    clickLock = false;
    isLifted = false;
    value = 0;

    // Appearance
    radius = 20;
    sensitivity = 0.005;
    thickness = 1;
    dashLength = 3;
    angleWidth = 0.75; // 75% of the full circle is used.

    scene->addUIElement(std::shared_ptr<Interactable>(this));

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

                clickPos = ms.pos;
                clickLock = true;

            }

            if (!prevLButtonState) isLifted = true;

        }
        else {

            isLifted = false;
            clickLock = false;

        }

    }
    else {

        if (!ms.lButtonDown) isLifted = false;

        pointerColor = sf::Color(255, 255, 255, 200);

    }

    if (isLifted) {

        value -= (ms.pos.y - clickPos.y) * sensitivity;
        //prevMousePos = ms.pos;

        if (value < 0) value = 0;
        if (value > 1) value = 1;

        hideMouse = true;
        positionMouse = true;

    }
    else {

        hideMouse = false;
        positionMouse = false;

    }

    prevLButtonState = ms.lButtonDown;

}



void DefaultKnob::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    if (positionMouse)
    sf::Mouse::setPosition(sf::Vector2i(clickPos.x, clickPos.y), *window);

    sf::Vector2f locPos = info.pos + pos;

    sf::CircleShape c;
    c.setPointCount(64);
    c.setRadius(radius);
    c.setOutlineThickness(thickness);
    c.setPosition(locPos.x - radius, locPos.y - radius);
    c.setOutlineColor(outlineColor);
    c.setFillColor(sf::Color(0, 0, 0, 0));

    double pi = 3.14159265358979323;

    float shit = pi * (0.5 + angleWidth);
    //            -value * 2 * pi * angleWidth + 3 * pi / 2 - pi * (1 - angleWidth);
    float angle = pi * (0.5 + angleWidth - value * 2 * angleWidth);

    sf::Vector2f point(radius * cos(angle) + locPos.x, radius * -sin(angle) + locPos.y);

    sf::Vector2f slope(cos(angle) * dashLength, -sin(angle) * dashLength);

    sf::VertexArray dash(sf::LineStrip, 2);
    dash[0] = point + slope;
    dash[1] = point - slope;

    window->draw(c);
    window->draw(dash);

}