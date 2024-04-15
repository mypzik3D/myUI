#pragma once
#include <SFML/Graphics.hpp>
#include "data.hpp"


void update_window(sf::RenderWindow& window,std::vector<std::unique_ptr<object>>& objects){
	window.clear();
	for(const auto & i : objects){
		object* obj = i.get();
		obj->draw(window);
	}
	window.display();
}
