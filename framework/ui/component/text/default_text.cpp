#include "default_text.h"

void DefaultText::getInput(MouseState& ms, double timePassed, SceneInfo info) {

}

void DefaultText::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::FloatRect textBounds = text.getGlobalBounds();

    sf::Vector2f globalPos = state.locPos;
    globalPos += info.pos;
    text.setPosition(globalPos);

    if (state.centered) {

        text.setOrigin(sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));

    }
    else {

        text.setOrigin(sf::Vector2f(0, textBounds.height / 2.0f));

    }

    window->draw(text);

}