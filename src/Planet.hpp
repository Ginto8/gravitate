#ifndef PLANET_HPP
#define PLANET_HPP

#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

struct Planet : public sf::Drawable {
    static const float SIZE_SCALAR;

    float mass;
    Vec2f loc;
    Vec2f vel;
    bool drawUnfilled;

    Planet(float _mass,Vec2f _loc,Vec2f _vel) :
        mass(_mass),loc(_loc),vel(_vel),drawUnfilled(false) {}

    float radius() const {
        return SIZE_SCALAR*std::max(1.0f,std::log(mass));
    }

    sf::Color color() const;

    void draw(sf::RenderTarget& target,sf::RenderStates states) const;
};

inline bool colliding(const Planet& a,const Planet& b) {
    float distSquared = (a.loc-b.loc).magSquared();
    float minDistance = a.radius()+b.radius();
    return distSquared < (minDistance*minDistance);
}

#endif
