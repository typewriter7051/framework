#include "outline_button.h"

OutlineButton::OutlineButton() : clickLock(false) {

    idleColor = sf::Color(255, 255, 255);
    clickedColor = sf::Color::White;
    currentColor = sf::Color::White;

    hoverStr = 10;

    hideMouse = false;

}

OutlineButton::OutlineButton(Scene* scene, void(*func)()) : clickLock(false) {

    scene->addUIElement(std::shared_ptr<Interactable>(this));

    idleColor = sf::Color(230, 230, 230);
    clickedColor = sf::Color::White;
    currentColor = sf::Color::White;

    callWhenPressed = func;

    hoverStr = 15;

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

    // limit timePassed to be no more than 1/30 of a second.
    if (timePassed > 0.035) { timePassed = 0.035; }

    float difference = hoverTarget - hoverVal;

    if (difference * difference > 0.0001)
        hoverVal += difference * hoverStr * timePassed;

    else
        hoverVal = hoverTarget;

}

void OutlineButton::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;

    sf::VertexArray outerBox(sf::LineStrip, 5);
    sf::VertexArray innerBox(sf::LineStrip, 5);

    float currentScale = (scaleAmt - 1) * hoverVal + 1;

    float rix = locPos.x + dims.x * 0.5 + (dims.x * 0.5 / currentScale);
    float lix = locPos.x + dims.x * (0.5 - 0.5 / currentScale);
    float tiy = locPos.y + dims.y * (0.5 - 0.5 / currentScale);
    float biy = locPos.y + dims.y * 0.5 + (dims.y * 0.5 / currentScale);

    float rox = locPos.x + dims.x * 0.5 + dims.x * 0.5 * currentScale;
    float lox = locPos.x - dims.x * (0.5 - 0.5 / currentScale);
    float toy = locPos.y - dims.y * (0.5 - 0.5 / currentScale);
    float boy = locPos.y + dims.y * 0.5 + dims.y * 0.5 * currentScale;

    innerBox[0].position = sf::Vector2f(rix, tiy);
    innerBox[1].position = sf::Vector2f(lix, tiy);
    innerBox[2].position = sf::Vector2f(lix, biy);
    innerBox[3].position = sf::Vector2f(rix, biy);
    innerBox[4].position = sf::Vector2f(rix, tiy);

    outerBox[0].position = sf::Vector2f(rox, toy);
    outerBox[1].position = sf::Vector2f(lox, toy);
    outerBox[2].position = sf::Vector2f(lox, boy);
    outerBox[3].position = sf::Vector2f(rox, boy);
    outerBox[4].position = sf::Vector2f(rox, toy);

    /*sf::RectangleShape rect;
    rect.setSize(dims);
    rect.setPosition(locPos.x, locPos.y);
    rect.setFillColor(currentColor);

    window->draw(rect);*/

    window->draw(innerBox);
    window->draw(outerBox);

}