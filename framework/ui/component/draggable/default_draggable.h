#include "../../ui.h"

class DefaultDraggable : public Interactable {
public:

	DefaultDraggable();

	DefaultDraggable(Scene*);

	sf::Vector2f getPos() { return pos; }

	void setPos(sf::Vector2f p) { pos = p; }
	void setPos(float x, float y) { pos.x = x; pos.y = y; }

	void setRadius(float r) { radius = r; }

	void setRangeControl(void(*func)(sf::Vector2f&)) { rangeControl = func; }

	void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

	void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) override;

protected:

	sf::Vector2f pos;
	sf::Vector2f staticPos;
	sf::Vector2f mouseClickedPos;
	bool clickLock;
	float radius;

	void(*rangeControl)(sf::Vector2f&);

	bool isLifted;
	sf::Color color;

};