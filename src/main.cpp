#include <SFML/Graphics.hpp>
#include "data-files.hpp"
#include "draw.hpp"
#include "data.hpp"
#include <iostream>



std::vector<std::unique_ptr<object>> objects;

int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings); 	old_size(window); get_files();

	object* canvas = new_object(objects,spr , 0, 0, 0, 0, null, 10, 10,sf::Color::Black);
	canvas->size = sf::Vector2f(200,200);
	canvas->scale_pos = sf::Vector2i(1,1);

    object* cent1 = new_object(objects, spr, 10,10,180,180,canvas,-1,-1, background);
	cent1->scale_pos = sf::Vector2i(1,1);
	cent1->radius = 10;



	window.setFramerateLimit(75);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::Resized){
				sf::FloatRect visible(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visible));
			}
		}
		update_window(window,objects);
    }

    return 0;
}
