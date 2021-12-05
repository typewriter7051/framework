#include "ui.h"

// Barebones default constructor for a Window class.
// Most of the time the user will initialize this to something else in Window::Start(sf::String).
Window::Window() : WIDTH(1000), HEIGHT(500) {

    

}



bool Window::isOpen() { return window->isOpen(); }

void Window::switchScene(sf::String name) {

    for (std::shared_ptr<Scene> s : scenes) {

        if (s->info.id == name) {

            if (!s->hide) s->hide = true;
            else s->hide = false;

        }

    }

}

void Window::addScene(std::shared_ptr<Scene> s) {

    scenes.push_back(s);
    s->parentWindow = this;

}

std::shared_ptr<sf::RenderWindow> Window::getPointer() { return window; }

//int Window::getUIListNum() { return UIElements.size(); }

void Window::getInput() {

    while (window->pollEvent(event)) {

        //--------------------------------------------------------------------------------
        // Typical cases such as closing the window, resizing, etc...

        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Escape) window->close();

        }

        if (event.type == sf::Event::MouseWheelMoved) {

            mouseState.wheelDelta = event.mouseWheel.delta;

        }

        if (event.type == sf::Event::Resized) {

            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            WIDTH = event.size.width;
            HEIGHT = event.size.height;
            window->setView(sf::View(visibleArea));

        }

        //--------------------------------------------------------------------------------
        // Iterates through all existing scenes and elements, and calls eventHandle function.

        for (std::shared_ptr<Scene> s : scenes) {

            s->eventHandle(event);

            for (std::shared_ptr<Interactable> i : s->elements) {

                i->eventHandle(event);

            }

        }

    }

    //--------------------------------------------------------------------------------
    // Fullscreen support.

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {

        if (!isFullScreen) {

            isFullScreen = true;
            window.reset(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), windowTitle, sf::Style::Fullscreen, settings));

        }
        else {

            isFullScreen = false;
            window.reset(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), windowTitle, sf::Style::Default, settings));

        }

    }

    //--------------------------------------------------------------------------------
    // Updating mouse info.

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mouseState.lButtonDown = true;
    else
        mouseState.lButtonDown = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        mouseState.rButtonDown = true;
    else
        mouseState.rButtonDown = false;

    mouseState.pos = sf::Vector2f(sf::Mouse::getPosition(*window));

    //--------------------------------------------------------------------------------
    // Process inputs for all existing scenes.

    for (std::shared_ptr<Scene> s : scenes) {

        s->updateTime(timePassed);
        s->getInput(event, mouseState, timePassed);

    }

}

//===============================================================================

void Window::drawWindow() {

    window->clear();

    //--------------------------------------------------------------------------------
    // Background drawing.

    if (drawBehindComponents != nullptr) {

        drawBehindComponents(window);

    }

    //--------------------------------------------------------------------------------
    // Actual scene drawing, and decides whether to hide mouse or not.

    int elementsThatHideMouse = 0;

    for (int i = 0; i < scenes.size(); i++) {

        scenes[i]->draw(window);

        if (scenes[i]->shouldHideMouse())
            elementsThatHideMouse++;

    }

    if (elementsThatHideMouse > 0) {
        window->setMouseCursorVisible(false);
    }
    else {
        window->setMouseCursorVisible(true);
    }

    //--------------------------------------------------------------------------------
    // Foreground drawing.

    if (drawAheadComponents != nullptr) {

        drawAheadComponents(window);

    }

    window->display();

}

//===============================================================================

void Window::windowFunctions() {

    auto newTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeElapsed = newTime - time;
    timePassed = timeElapsed.count();
    time = newTime;

    getInput();

    drawWindow();

}

//===============================================================================

void Window::start(sf::String title) {

    windowTitle = title;

    settings.antialiasingLevel = 8;
    window.reset(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), windowTitle, sf::Style::Default, settings));

    window->setFramerateLimit(60);

    time = std::chrono::high_resolution_clock::now();

    while (isOpen()) {

        windowFunctions();

    }

}