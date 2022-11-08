#include "default_textbox.h"

DefaultTextbox::DefaultTextbox(Scene* scene) {

    scene->addUIElement(std::shared_ptr<Interactable>(this));
	font.loadFromFile("../../../framework/fonts/yahei base.otf");
	text.setFont(font);

}

//===============================================================================

void DefaultTextbox::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;



}

//===============================================================================

void DefaultTextbox::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    sf::Vector2f locPos = info.pos + pos;
	
	sf::View ogView = window->getView();
	sf::View textView = window->getView();
	//textView.setScissor(bounds);
	// https://github.com/SFML/SFML/pull/1451


	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setPosition(0, 0);

	window->draw(text);

}

//===============================================================================

void DefaultTextbox::eventHandle(sf::Event& event) {

	if (event.type == sf::Event::TextEntered) {

		// chars are represented by their ascii value.
		if (event.text.unicode != '\b' && event.text.unicode >= 32) {

			enteredText += event.text.unicode;

		}

	}

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::BackSpace) {

			if (enteredText != "")
				enteredText.erase(enteredText.getSize() - 1, 1);

		}

		if (event.key.code == sf::Keyboard::Enter) {

			enteredText += "\n";

		}

		if (event.key.control && event.key.code == sf::Keyboard::V) {

			enteredText += sf::Clipboard::getString();

		}

		if (event.key.control && event.key.code == sf::Keyboard::C)
			sf::Clipboard::setString(enteredText);

	}

	//std::cout << string.toAnsiString() << std::endl;

	text.setString(enteredText);

}