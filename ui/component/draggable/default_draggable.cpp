#include "default_draggable.h"

DefaultDraggable::DefaultDraggable() {

    clickLock = false;
    isLifted = false;
    color = sf::Color(255, 255, 255, 200);

    rangeControl = nullptr;

}



DefaultDraggable::DefaultDraggable(Scene* scene) {

    clickLock = false;
    isLifted = false;

    scene->addUIElement(this);

    color = sf::Color(255, 255, 255, 200);

    rangeControl = nullptr;

}



void DefaultDraggable::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    float dx = ms.pos.x - locPos.x;
    float dy = ms.pos.y - locPos.y;

    if (sqrt(dx * dx + dy * dy) < radius) {

        color = sf::Color(255, 255, 255, 255);

        if (ms.lButtonDown) {

            if (!clickLock) {

                staticPos = pos;
                mouseClickedPos = ms.pos;
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

        color = sf::Color(255, 255, 255, 200);

    }

    if (isLifted) {

        pos.x = staticPos.x + ms.pos.x - mouseClickedPos.x;
        pos.y = staticPos.y + ms.pos.y - mouseClickedPos.y;

        // If a range limiting function has been set, call it.
        if (rangeControl != nullptr)
            rangeControl(pos);

        hideMouse = true;

    }
    else {

        hideMouse = false;

    }

}



void DefaultDraggable::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::CircleShape c;
    c.setRadius(radius);
    c.setPosition(locPos.x - radius, locPos.y - radius);
    c.setFillColor(color);

    window->draw(c);

}