#include "Planet.hpp"
#include <SFML/Graphics.hpp>

const float Planet::SIZE_SCALAR = 1.5;

const int NUM_COLORS = 4;
const struct {
    float value;
    sf::Color color;
} colorScheme[NUM_COLORS] = {
    {      0,sf::Color::White  },
    {   1000,sf::Color::Yellow },
    {  10000,sf::Color(0xFF,0x33,0x00) },
    { 100000,sf::Color::Red    }
};

void Planet::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    sf::CircleShape shape(radius());
    shape.setPosition(loc[0],loc[1]);
    sf::Color color;
    if(mass <= colorScheme[0].value) {
        color = colorScheme[0].color;
    } else if(mass >= colorScheme[NUM_COLORS-1].value) {
        color = colorScheme[NUM_COLORS-1].color;
    } else {
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
                color = sf::Color(color1[0],color1[1],color1[2]);
                break;
            }
        }
    }
    shape.setOutlineColor(color);
    if(drawUnfilled) {
        shape.setFillColor(sf::Color::Transparent);
    } else {
        shape.setFillColor(color);
    }
    target.draw(shape,states);
}
