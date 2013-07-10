#include "Planet.hpp"
#include <SFML/Graphics.hpp>

const float Planet::SIZE_SCALAR = 1;

const int NUM_COLORS = 4;
const struct {
    float value;
    sf::Color color;
} colorScheme[NUM_COLORS] = {
    {     0,sf::Color::White  },
    {   100,sf::Color::Yellow },
    {  1000,sf::Color(0xFF,0x33,0x00) },
    { 10000,sf::Color::Red    }
};

sf::Color Planet::color() const {
    if(mass <= colorScheme[0].value) {
        return colorScheme[0].color;
    } 
    if(mass >= colorScheme[NUM_COLORS-1].value) {
        return colorScheme[NUM_COLORS-1].color;
    }
    for(int i=NUM_COLORS-1;i>=0;--i) {
        if(mass >= colorScheme[i].value) {
            float diff = (colorScheme[i+1].value
                          -colorScheme[i].value);
            float factor = (mass-colorScheme[i].value)/diff;
            float color1[] = { colorScheme[i].color.r,
                               colorScheme[i].color.g,
                               colorScheme[i].color.b },
                  color2[] = { colorScheme[i+1].color.r,
                               colorScheme[i+1].color.g,
                               colorScheme[i+1].color.b };
            for(int j=0;j<3;++j) {
                color1[j] += factor*(color2[j]-color1[j]);
            }
            return sf::Color(color1[0],color1[1],color1[2]);
        }
    }
    return colorScheme[NUM_COLORS-1].color;
}

void Planet::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    sf::CircleShape shape(radius());
    shape.setPosition(loc[0]-shape.getRadius(),
                      loc[1]-shape.getRadius());
    sf::Color drawnColor = color();
    shape.setOutlineColor(drawnColor);
    if(drawUnfilled) {
        shape.setOutlineThickness(1);
        shape.setFillColor(sf::Color::Transparent);
    } else {
        shape.setOutlineThickness(0);
        shape.setFillColor(drawnColor);
    }
    target.draw(shape,states);
}
