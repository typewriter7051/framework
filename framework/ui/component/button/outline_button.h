#include "../../ui.h"

class OutlineButton : public Interactable {
public:

	OutlineButton();

	OutlineButton(Scene*, void(*func)());

	void setPos(sf::Vector2f p) { pos = p; }
	void setPos(float x, float y) { pos.x = x; pos.y = y; }

	void setDims(sf::Vector2f d) { dims = d; }
	void setDims(float x, float y) { dims.x = x; dims.y = y; }

	void setIdleColor(sf::Color c) { idleColor = c; }
	void setClickedColor(sf::Color c) { clickedColor = c; }

	void getInput(MouseState& ms, double timePased, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

protected:

	bool clickLock;

	float hoverVal;
	float hoverTarget;
	float hoverStr;sldkfj
	float scaleAmt = 1.2;

	sf::Vector2f pos;
	sf::Vector2f dims;

	sf::Color idleColor;
	sf::Color clickedColor;
	sf::Color currentColor;

	void(*callWhenPressed)();

};