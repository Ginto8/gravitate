#ifndef PLANETSYSTEM_HPP
#define PLANETSYSTEM_HPP

#include <vector>

#include "Planet.hpp"
#include <SFML/Graphics.hpp>

class PlanetSystem : public sf::Drawable {
    static const float GRAVITY;
    static Vec2f calculateGravity(const Planet& a,const Planet& b);

    std::vector<size_t> _trailIndices;
    std::vector<sf::VertexArray> _trails;
    bool _drawTrails;

    void _consolidatePlanets();
    
public:
    std::vector<Planet> _planets;
    void addPlanet(Planet p);
    void tick(float dt);
    void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    void clear();
    bool drawingTrails() const;
    void setDrawingTrails(bool drawTrails);
};

#endif
