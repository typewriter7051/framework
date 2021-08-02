#include "default_button.h"

DefaultButton::DefaultButton() : clickLock(false) {

    idleColor = sf::Color(255, 255, 255, 200);
    clickedColor = sf::Color::White;

    hideMouse = false;

}



DefaultButton::DefaultButton(Scene* scene, void(*func)()) : clickLock(false) {

    scene->addUIElement(std::shared_ptr<Interactable>(this));

    idleColor = sf::Color(230, 230, 230, 200);
    clickedColor = sf::Color::White;

    callWhenPressed = func;

    hideMouse = false;

}



void DefaultButton::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    if (ms.pos.x > locPos.x && ms.pos.x < locPos.x + dims.x &&
        ms.pos.y > locPos.y && ms.pos.y < locPos.y + dims.y) {

        sf::Color mouseOverColor = idleColor;
        mouseOverColor.r += 25;
        mouseOverColor.g += 25;
        mouseOverColor.b += 25;

        currentColor = mouseOverColor;

        if (ms.lButtonDown && !clickLock) {

            callWhenPressed();
            clickLock = true;

        }
        if (!ms.lButtonDown) {

            clickLock = false;

        }

    }
    else {

        currentColor = idleColor;

    }

}

void DefaultButton::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::RectangleShape rect;
    rect.setSize(dims);
    rect.setPosition(locPos.x, locPos.y);
    rect.setFillColor(currentColor);

    window->draw(rect);

}