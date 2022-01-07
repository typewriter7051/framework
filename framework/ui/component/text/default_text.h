#ifndef default_text

#include "../../ui.h"

struct TextState {

	sf::Font font;
	unsigned int charSize;
	sf::Color color;
	sf::Vector2f locPos;
	bool centered;

	TextState() {

		color = sf::Color::White;
		charSize = 14;
		centered = false;

	}

	void setup(sf::Font f, int s, sf::Color c, sf::Vector2f p, bool t) {

		font = f;
		charSize = s;
		color = c;
		locPos = p;
		centered = t;

	}

};

class DefaultText : public Interactable {
public:

	TextState state;
	sf::Text text;

	DefaultText() {

		text.setCharacterSize(14);
		text.setFillColor(sf::Color::White);
		state.locPos = sf::Vector2f(5, 10);
		text.setString("default string");
		state.centered = false;

	}

	DefaultText(Scene* scene) {

		scene->addUIElement(std::shared_ptr<Interactable>(this));

	}

	void setup(TextState* s, sf::String st) {

		state = *s;
		text.setFont(state.font);
		text.setCharacterSize(s->charSize);
		text.setFillColor(s->color);
		text.setString(st);

	}

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:


};

#endif