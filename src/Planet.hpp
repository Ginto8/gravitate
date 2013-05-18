#ifndef PLANET_HPP
#define PLANET_HPP

#include <cmath>
#include <SFML/Graphics/Drawable.hpp>
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
        return SIZE_SCALAR*std::log10(mass);
    }

    void draw(sf::RenderTarget& target,sf::RenderStates states) const;
};

inline bool colliding(const Planet& a,const Planet& b) {
    float distSquared = (a.loc-b.loc).magSquared();
    float minDistance = a.radius()+b.radius();
    return distSquared < (minDistance*minDistance);
}

#endif
