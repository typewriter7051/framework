#include "../../ui.h"

class DefaultTextbox : public Interactable {
public:

	void getInput(MouseState& ms, double timePased, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:

	sf::String enteredText;

	std::shared_ptr<sf::Event> event;

};