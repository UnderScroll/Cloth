#include "Core.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Cloth Simulation");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    Core application = Core(window);
    application.run();
    
    return 0;
}