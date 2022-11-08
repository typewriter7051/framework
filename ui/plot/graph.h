#include <vector>
#include "../ui.h"

template <class T>
class Graph : public Interactable {
public:


protected:

	std::vector<T> data;

	double[2] xDataBounds;
	double[2] yDataBounds;

	double[2] xScreenBounds;
	double[2] yScreenBounds;

	void drawGrid(double xWidth, double yWidth, std::shared_ptr<sf::RenderWindow> window);

	virtual void getInput(MouseState&, double, SceneInfo) = 0;

	virtual void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo) = 0;

private:

};