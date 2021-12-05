#include "graph.h"

void Graph::drawGrid(double xWidth, double yWidth, std::shared_ptr<sf::RenderWindow> window) {

	double firstXData = xWidth * (int(xDataBounds[0] / xWidth) + 1);

	double xScale = (xScreenBounds[1] - xScreenBounds[0]) / (xDataBounds[1] - xDataBounds[0]);
	double yScale = (yScreenBounds[1] - yScreenBounds[0]) / (yDataBounds[1] - yDataBounds[0]);

	sf::VertexArray xLine(sf::LineStrip, 2);

	// Draw vertical lines.
	for (double xPos = firstXData; xPos < xDataBounds[1]; xPos += xWidth) {

		double screenXPos = (xPos - xDataBounds[0]) * xScale;
		
		xLine[0] = sf::Vector2f(screenXPos, yScreenBounds[0]);
		xLine[1] = sf::Vector2f(screenXPos, yScreenBounds[1]);

		window->draw(xLine);

	}

}