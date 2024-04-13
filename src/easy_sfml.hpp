#pragma once
#include <SFML/Graphics.hpp>
#include "data.hpp"

sf::Vector2i Vector2i(int x, int y){
    return sf::Vector2i(x, y);
}

sf::Vector2f Vector2(int x, int y){
    return sf::Vector2f(x, y);
}

sf::Vector2u Vector2u(int x, int y){
    return sf::Vector2u(x, y);
}
