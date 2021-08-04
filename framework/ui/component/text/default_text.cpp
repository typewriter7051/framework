#include "default_text.h"

void DefaultText::addText(textInfo ti) {

    ti.text.setFont(font);
    texts.push_back(ti);

}

void DefaultText::getInput(MouseState& ms, double timePassed, SceneInfo info) {

}

void DefaultText::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    for (textInfo ti : texts) {

        sf::FloatRect textBounds = ti.text.getGlobalBounds();

        sf::Vector2f thang = ti.scenePos;
        thang += info.pos;
        ti.text.setPosition(thang);

        if (ti.centered) {

            ti.text.setOrigin(sf::Vector2f(textBounds.width / 2.0f, textBounds.height / 2.0f));

        }
        else {

            ti.text.setOrigin(sf::Vector2f(0, textBounds.height / 2.0f));

        }

        window->draw(ti.text);

    }

}