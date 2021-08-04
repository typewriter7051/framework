#ifndef default_text

#include "../../ui.h"

struct textInfo {

	sf::Text text;

	sf::Vector2f scenePos;
	bool centered = false;

	void setup(int s, sf::Color c, sf::Vector2f p, sf::String st, bool t) {

		text.setCharacterSize(s);
		text.setFillColor(c);
		scenePos = p;
		text.setString(st);
		centered = t;

	}

	textInfo() {

		text.setCharacterSize(14);
		text.setFillColor(sf::Color::White);
		scenePos = sf::Vector2f(5, 10);
		text.setString("default string");
		centered = false;

	}

};

class DefaultText : public Interactable {
public:

	sf::Font font;

	DefaultText() {

	}

	DefaultText(Scene* scene) {

		font.loadFromMemory(Montserrat_Light_ttf, Montserrat_Light_ttf_len);
		scene->addUIElement(std::shared_ptr<Interactable>(this));

	}

	void addText(textInfo ti);

	void loadFont(const void* data, size_t size) { font.loadFromMemory(data, size); }

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:

	std::vector<textInfo> texts;

};

#endif