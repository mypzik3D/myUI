#pragma once
#include <SFML/Graphics.hpp>
#define spr "sprite"
#define txt "text"

sf::Color background = sf::Color(57, 59, 68, 255);
sf::Color foreground = sf::Color(82, 87, 93, 255);
sf::Color button = sf::Color(0, 173, 181, 255);
sf::Color text = sf::Color(238, 238, 238, 255);
sf::Color red = sf::Color(214, 66, 53, 255);
sf::Color green = sf::Color(81, 152, 114, 255);

sf::Font betterVCR;

void get_files(){
    betterVCR.loadFromFile("../fnt/BetterVCR_6.1.ttf");
    //betterVCR.loadFromFile("Arial.ttf");
}
