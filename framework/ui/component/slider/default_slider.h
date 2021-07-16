#include "../../ui.h"

class DefaultSlider : public Interactable {
public:

	DefaultSlider() : knobRadius(50), s(0.001), clickLock(false), isLifted(false), value(0) {}

	DefaultSlider(Scene*);

	void setPos(sf::Vector2f p) { pos = p; }

	void setPos(float x, float y) { pos.x = x; pos.y = y; }

	void setLength(double l) { lineLength = l; s = 1 / lineLength; }

	void setKnobRadius(double r) { knobRadius = r; }

	void setOrientation(bool v) { isVertical = v; }

	void setLineThickness(double t) { lineThickness = t; }

	void setLineColor(sf::Color c) { lineColor = c; }

	void setKnobColor(sf::Color c) { knobColor = c; }

	double getValue() { return value; }

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

private:

	bool prevClickLock;
	bool clickLock;
	bool isLifted;
	bool prevLifted;
	bool isVertical;
	bool positionMouse = false;

	// Mouse related stuff.
	sf::Vector2i grabbedMousePos;
	sf::Vector2f prevMousePos;
	double s;

	double value; // Value of the knob between 0 and 1.

	// Knob stuff.
	sf::Color knobColor;
	double knobRadius;
	sf::Vector2f pos;

	//Line stuff.
	sf::Color lineColor;
	double lineThickness;
	double lineLength;

};