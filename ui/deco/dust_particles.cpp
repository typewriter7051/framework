#include "dust_particles.h"

DustParticles::DustParticles() {

    hideMouse = false;

    pos.resize(100);
    vel.resize(100);

    WIDTH = 1920;
    HEIGHT = 1080;

    randomize();

}

DustParticles::DustParticles(Scene* scene, int num) {

    scene->addUIElement(std::shared_ptr<Interactable>(this));

    hideMouse = false;

    pos.resize(num);
    vel.resize(num);

    WIDTH = 1920;
    HEIGHT = 1080;

    randomize();

}

void DustParticles::randomize() {

    for (int i = 0; i < pos.size(); i++) {

        srand(time(NULL) + i * 100);
        pos[i].x = rand() % WIDTH;
        pos[i].y = rand() % HEIGHT;
        pos[i].z = rand() % 19 + 1;

        vel[i].x = (rand() % 100 - 50) * 1;
        vel[i].y = (rand() % 100 - 50) * 1;
        vel[i].z = (rand() % 100 - 50) * 0.02;

    }

}

void DustParticles::move(double timePassed, double factor) {

    for (int i = 0; i < pos.size(); i++) {

        pos[i].x += vel[i].x / pos[i].z * timePassed * (factor);
        pos[i].y += vel[i].y / pos[i].z * timePassed * (factor);
        pos[i].z += vel[i].z * timePassed * (1 + factor);

        if (pos[i].z < 1) {

            pos[i].z = 2 - pos[i].z;
            vel[i].z = abs(vel[i].z);

        }
        else if (pos[i].z > 5) {

            pos[i].z = 10 - pos[i].z;
            vel[i].z = -1 * abs(vel[i].z);

        }
        if (pos[i].x > WIDTH) pos[i].x -= WIDTH + 5;
        if (pos[i].x < -5) pos[i].x += WIDTH + 5;
        if (pos[i].y > HEIGHT) pos[i].y -= HEIGHT + 5;
        if (pos[i].y < -5) pos[i].y += HEIGHT + 5;

    }

}

void DustParticles::getInput(MouseState& ms, double timePassed, SceneInfo info) {

    move(timePassed, 0.5);

}

void DustParticles::draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo info) {

    WIDTH  = window->getSize().x;
    HEIGHT = window->getSize().y;

    sf::CircleShape circle;
    circle.setPointCount(4);

    for (int i = 0; i < pos.size(); i++) {

        circle.setPosition(pos[i].x, pos[i].y);
        circle.setRadius(5 / pos[i].z);
        int c = 255 / pos[i].z;
        circle.setFillColor(sf::Color(255, 255, 255, c / 5));
        window->draw(circle);

    }

}