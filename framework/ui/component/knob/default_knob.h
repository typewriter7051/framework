#include "../../ui.h"

class DefaultKnob : public Interactable {
public:

	DefaultKnob() : radius(50), sensitivity(0.01), clickLock(false), isLifted(false), value(0) {}

	DefaultKnob(Scene*);

	void setPos(sf::Vector2f p) { pos = p; }

	void setPos(float x, float y) { pos.x = x; pos.y = y; }

	double getValue() { return value; }

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:

	bool clickLock;
	bool prevLButtonState;
	bool isLifted;
	bool positionMouse;
	sf::Vector2f clickPos;
	double sensitivity;

	double value; // Value of the knob between 0 and 1.

	float radius;
	float thickness;
	float dashLength;
	float angleWidth;
	sf::Vector2f pos;

	sf::Color pointerColor;
	sf::Color outlineColor;

};