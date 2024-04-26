#pragma once
#include <SFML/Graphics.hpp>
#include "data.hpp"


void update_window(sf::RenderWindow& window,std::vector<std::unique_ptr<object>>& objects){
	window.clear();
	int a = 0;
	int count = 0;
    while(true){
		for(const auto & i : objects){
		    if(i->layer == a){
				object* obj = i.get();
				obj->draw(window);
				count++; 
		    }
		}
		a++;
		if(count >= objects.size())
		    break;
	}
	window.display();
}
