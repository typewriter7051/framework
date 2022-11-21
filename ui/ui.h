#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory> // for smart pointers
#include "../fonts/Montserrat-Light.h"
//#include "../fonts/Montserrat-SemiBold.h"
//#include "../fonts/NotoSansSC-Bold.h"
//#include "../fonts/NotoSansTC-Light.h"
//#include "../fonts/NotoSansSC-Light.h"

struct MouseState {

	bool lButtonDown;
	bool rButtonDown;

	int wheelDelta; // Scroll wheel ticks, positive is up direction.

	sf::Vector2f pos; // XY pos of the mouse.

};

//===============================================================================

struct SceneInfo {

	double age = 0;
	double opacity = 1;
	sf::Vector2f pos;
	sf::String id;

};

// Base class for all things interactable on the screen.
class Interactable {
protected:

	sf::Vector2f pos;

	bool hideMouse;

public:

	Interactable() {}

	bool shouldHideMouse() { return hideMouse; }

	virtual void getInput(MouseState&, double, SceneInfo) {}

	virtual void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo) {}

	virtual void eventHandle(sf::Event& event) {}

};

//===============================================================================

class Scene;

class Window {
private:

	sf::Event event;
	int WIDTH, HEIGHT;

	sf::String windowTitle;

	double timePassed;
	std::chrono::steady_clock::time_point time;

	sf::ContextSettings settings;
	std::shared_ptr<sf::RenderWindow> window;
	bool isFullScreen = false;

	void(*drawBehindComponents)(std::shared_ptr<sf::RenderWindow>);
	void(*drawAheadComponents)(std::shared_ptr<sf::RenderWindow>);

	MouseState mouseState;

	std::vector<std::shared_ptr<Scene>> scenes;

	sf::String* textInput;

public:

	Window();

	bool isOpen();

	void windowFunctions();

	void getInput();

	void switchScene(sf::String);

	std::shared_ptr<sf::RenderWindow> getPointer();

	void setDrawBehindComponents(void(*f)(std::shared_ptr<sf::RenderWindow>)) { drawBehindComponents = f; }
	void setDrawAheadComponents(void(*f)(std::shared_ptr<sf::RenderWindow>)) { drawAheadComponents = f; }

	// bool pollEvent(sf::Event event) { return window->pollEvent(event); }

	void drawWindow();

	void addScene(std::shared_ptr<Scene>);

	void start(sf::String);

};

//===============================================================================

// A Scene is comprised of a list of "elements" of type Interactable.
class Scene {
protected:

	std::vector<std::shared_ptr<Interactable>> elements;
	std::vector<std::shared_ptr<Scene>> nestedScenes;

	SceneInfo info;

	bool hide;

	friend class Window;
	Window* parentWindow;

public:

	Scene() : hide(false) {}

	void addUIElement(std::shared_ptr<Interactable> i) {

		elements.push_back(i);

	}

	void switchScene(sf::String name) {

		parentWindow->switchScene(name);

	}

	sf::Vector2f getPos() { return info.pos; }

	void movePos(double x, double y) { info.pos.x += x; info.pos.y += y; }
	void movePos(sf::Vector2f p) { info.pos += p; }

	void setPos(double x, double y) { info.pos.x = x; info.pos.y = y; }
	void setPos(sf::Vector2f p) { info.pos = p; }

	void updateTime(double d) { info.age += d; }

	void hideScene() { hide = true; }
	void unhideScene() { hide = false; }

	//--------------------------------------------------------------------------------

	bool shouldHideMouse() {

		if (hide) return false;

		for (std::shared_ptr<Interactable> i : elements) {

			if (i->shouldHideMouse())
				return true;

		}

		// Checks within nested scenes.
		for (std::shared_ptr<Scene> s : nestedScenes) {

			s->shouldHideMouse();

		}

		return false;

	}

	//--------------------------------------------------------------------------------

	void getInput(sf::Event event, MouseState& ms, double timePassed) {

		if (!hide) {

			for (std::shared_ptr<Interactable> i : elements) {

				i->getInput(ms, timePassed, info);

			}

			// Nested scenes.
			for (std::shared_ptr<Scene> s : nestedScenes) {

				s->getInput(event, ms, timePassed);

			}

		}

		process(ms, timePassed);

	}

	//--------------------------------------------------------------------------------

	void draw(std::shared_ptr<sf::RenderWindow> window) {

		if (hide) return;

		drawBehindUI(window);

		for (std::shared_ptr<Interactable> i : elements) {

			i->draw(window, info);

		}

		// Draw nested scenes.
		for (std::shared_ptr<Scene> s : nestedScenes) {

			s->draw(window);

		}

		drawAheadUI(window);

	}

	//--------------------------------------------------------------------------------

	virtual void drawBehindUI(std::shared_ptr<sf::RenderWindow> window) {



	}

	virtual void drawAheadUI(std::shared_ptr<sf::RenderWindow> window) {



	}

	virtual void process(MouseState& ms, double timePassed) {



	}

	virtual void eventHandle(sf::Event& event) {



	}

};