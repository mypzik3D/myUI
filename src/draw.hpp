#pragma once
#include <SFML/Graphics.hpp>
#include "data.hpp"


void update_window(sf::RenderWindow& window,std::vector<object>& objects){
	window.clear();
	for(int i = 0; i < objects.size(); i++){
		object obj = objects.at(i);
		obj.draw(window);
	}
	window.display();
}
