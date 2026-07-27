#include "Application.h"

int main()
{
    Application application;
    if (application.Initialize("Creajeux Engine", sf::VideoMode(sf::Vector2u(1280, 720)), 60))
        application.Run();
    return 0;
}
