#include "../../ui.h"

struct textInfo {

	sf::Text text;

	sf::Vector2f scenePos;
	bool centered = false;

	textInfo() {

		text.setCharacterSize(25);
		text.setFillColor(sf::Color::White);

	}

};

class DefaultText : public Interactable {
public:

	sf::Font font;

	DefaultText() {

	}

	DefaultText(Scene* scene) {

		font.loadFromMemory(Montserrat_Light_ttf, Montserrat_Light_ttf_len);
		scene->addUIElement(this);

	}

	void addText(textInfo ti);

	void loadFont(const void* data, size_t size) { font.loadFromMemory(data, size); }

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:

	std::vector<textInfo> texts;

};