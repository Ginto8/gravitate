#include "PlanetSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

const float PlanetSystem::GRAVITY = 5.0f;

Vec2f PlanetSystem::calculateGravity(const Planet& a,
                                     const Planet& b) {
    return GRAVITY*a.mass*b.mass/(a.loc-b.loc).magSquared()
           *norm(b.loc-a.loc);
}

void PlanetSystem::addPlanet(Planet p) {
    p.drawUnfilled = false;
    _planets.push_back(p);
    _trailIndices.push_back(_trails.size());
    sf::VertexArray array;
    array.setPrimitiveType(sf::LinesStrip);
    _trails.push_back(array);
}

void PlanetSystem::_consolidatePlanets() {
    for(size_t i=0;i<_planets.size()-1;++i) {
        for(size_t j=i+1;j<_planets.size();++j) {
            if(colliding(_planets[i],_planets[j])) {
                // New location is the center of mass
                _planets[i].loc = (_planets[i].mass*_planets[i].loc
                                   +_planets[j].mass*_planets[j].loc)
                                  /(_planets[i].mass+_planets[j].mass);
                // I remember this formula mostly from the ad that kept
                // playing at champs
                _planets[i].vel = (_planets[i].mass*_planets[i].vel
                                   +_planets[j].mass*_planets[j].vel)
                                  /(_planets[i].mass+_planets[j].mass);
                _planets[i].mass += _planets[j].mass;
                _planets.erase(_planets.begin()+j);
                _trailIndices.erase(_trailIndices.begin()+j);
                --j;
                break;
            }
        }
    }
}
void PlanetSystem::tick(float dt) {
    if(_planets.size() == 0) {
        return;
    }
    _consolidatePlanets();
    std::vector<Vec2f> forces(_planets.size());
    for(size_t i=0;i<_planets.size()-1;++i) {
        for(size_t j=i+1;j<_planets.size();++j) {
            Vec2f force = calculateGravity(_planets[i],_planets[j]);
            forces[i] += force;
            forces[j] -= force;
        }
    }
    for(size_t i=0;i<_planets.size();++i) {
        _planets[i].vel += forces[i]/_planets[i].mass*dt;
        _planets[i].loc += _planets[i].vel*dt;
        if(_drawTrails) {
            sf::Vertex newVertex;
            newVertex.color = _planets[i].color();
            newVertex.position.x = _planets[i].loc[0];
            newVertex.position.y = _planets[i].loc[1];
            _trails[_trailIndices[i]].append(newVertex);
        }
    }
    _consolidatePlanets();
}

void PlanetSystem::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
    for(size_t i=0;i<_trails.size();++i) {
        target.draw(_trails[i]);
    }
    for(size_t i=0;i<_planets.size();++i) {
        target.draw(_planets[i],states);
    }
}

void PlanetSystem::clear() {
    _planets.clear();
    _trailIndices.clear();
    _trails.clear();
}

bool PlanetSystem::drawingTrails() const {
    return _drawTrails;
}

void PlanetSystem::setDrawingTrails(bool drawTrails) {
    if(!drawTrails) {
        _trails.clear();
        _trailIndices.clear();
        for(size_t i=0;i<_planets.size();++i) {
            _trailIndices.push_back(i);
            sf::VertexArray array;
            array.setPrimitiveType(sf::LinesStrip);
            _trails.push_back(array);
        }
    }
    _drawTrails = drawTrails;
}

