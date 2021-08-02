#include "default_button.h"

OutlineButton::OutlineButton() : clickLock(false) {

    idleColor = sf::Color(255, 255, 255);
    clickedColor = sf::Color::White;
    currentColor = sf::Color::White;

    hoverStr = 10;

    hideMouse = false;

}



OutlineButton::OutlineButton(Scene* scene, void(*func)()) : clickLock(false) {

    scene->addUIElement(this);

    idleColor = sf::Color(230, 230, 230);
    clickedColor = sf::Color::White;
    currentColor = sf::Color::White;

    callWhenPressed = func;

    hoverStr = 10;

    hideMouse = false;

}



void OutlineButton::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    if (ms.pos.x > locPos.x && ms.pos.x < locPos.x + dims.x &&
        ms.pos.y > locPos.y && ms.pos.y < locPos.y + dims.y) {

        hoverTarget = 1;

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

        hoverTarget = 0;

    }

    hoverVal += (hoverTarget - hoverVal) * hoverStr * timePassed;

}



sf::RenderWindow* Window::getPointer() { return window; }



void OutlineButton::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::VertexArray outerBox(sf::LineStrip, 4);
    sf::VertexArray innerBox(sf::LineStrip, 4);

    float lix = locPos.x + dims.x / scaleAmt;
    float rix = locPos.x + dims.x * (0.5 - 1 / scaleAmt);
    float tiy = locPos.y + dims.y * (0.5 - 1 / scaleAmt);
    float biy = locPos.y + dims.y / scaleAmt;

    innerBox[0].position = sf::Vector2f(rix, tiy);
    innerBox[1].position = sf::Vector2f(lix, tiy);
    innerBox[2].position = sf::Vector2f(lix, biy);
    innerBox[3].position = sf::Vector2f(rix, biy);

    outerBox[0].position = sf::Vector2f(10, 0);
    outerBox[1].position = sf::Vector2f(20, 0);
    outerBox[2].position = sf::Vector2f(30, 5);
    outerBox[3].position = sf::Vector2f(40, 2);

    /*sf::RectangleShape rect;
    rect.setSize(dims);
    rect.setPosition(locPos.x, locPos.y);
    rect.setFillColor(currentColor);

    window->draw(rect);*/

    window->draw(innerBox);
    window->draw(outerBox);

}