#ifndef PLANETSYSTEM_HPP
#define PLANETSYSTEM_HPP

#include <vector>

#include "Planet.hpp"

class PlanetSystem : public sf::Drawable {
    static const float GRAVITY;
    static Vec2f calculateGravity(const Planet& a,const Planet& b);

    std::vector<Planet> _planets;

    void _consolidatePlanets();
    
public:
    void addPlanet(Planet p);
    void tick(float dt);
    void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    void clear();
};

#endif
