#include "PlanetSystem.hpp"
#include <ctime>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const float FPS = 60;
const float DT  = 1/FPS;

const float MASS = 100;

Vec2f randomVec(float maxMag) {
    float angle = std::rand()/(float)RAND_MAX*2*M_PI;
    Vec2f norm = {std::cos(angle),std::sin(angle)};
    return std::rand()/(float)RAND_MAX*maxMag*norm;
}

int main() {
    PlanetSystem system;
    sf::RenderWindow window(sf::VideoMode(640,480),"Gravity");

    window.setFramerateLimit(FPS);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized: {
                sf::View v(sf::FloatRect(0,0,event.size.width,
                                             event.size.height));
                window.setView(v);
                break;
            }
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Middle) {
                    system.clear();
                }
                break;
            default:
                break;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouseLoc = sf::Mouse::getPosition(window);
            Vec2f loc = { mouseLoc.x,
                          mouseLoc.y };
            Vec2f vel = { 0,0 };
            system.addPlanet(Planet(MASS,
                                    loc,
                                    vel));
        }
        system.tick(DT);
        window.clear(sf::Color::Black);
        window.draw(system);

        window.display();
    }
}
