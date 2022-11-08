#include "../../ui.h"

class DefaultTextbox : public Interactable {
public:

	DefaultTextbox(Scene* scene);

	void getInput(MouseState& ms, double timePased, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

	void eventHandle(sf::Event& event) override;

private:

	int cursorPos;
	bool selected = false;

	sf::FloatRect bounds;

	sf::String enteredText;
	sf::Text text;
	sf::Font font;

	std::shared_ptr<sf::Event> event;

};