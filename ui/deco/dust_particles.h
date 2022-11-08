#include "../ui.h"
#include <vector>

class DustParticles : public Interactable {
public:

    std::vector<sf::Vector3f> pos;
    std::vector<sf::Vector3f> vel;

    unsigned int WIDTH, HEIGHT;

    DustParticles();
    DustParticles(Scene* scene, int num);

    void randomize();

    void move(double timePassed, double factor);

    void getInput(MouseState& ms, double timePassed, SceneInfo info) override;

    void draw(std::shared_ptr<sf::RenderWindow> window, SceneInfo) override;

};