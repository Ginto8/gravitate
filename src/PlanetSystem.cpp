#include "PlanetSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

const float PlanetSystem::GRAVITY = 1.0f;

Vec2f PlanetSystem::calculateGravity(const Planet& a,
                                      const Planet& b) {
    return GRAVITY*a.mass*b.mass/(a.loc-b.loc).magSquared()
           *(b.loc-a.loc);
}

void PlanetSystem::addPlanet(Planet p) {
    _planets.push_back(p);
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
        _planets[i].loc += _planets[i].vel*dt;
        _planets[i].vel += forces[i]/_planets[i].mass*dt;
    }
    _consolidatePlanets();
}

void PlanetSystem::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
    for(size_t i=0;i<_planets.size();++i) {
        target.draw(_planets[i],states);
    }
}

void PlanetSystem::clear() {
    _planets.clear();
}
