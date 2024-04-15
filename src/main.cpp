#include <SFML/Graphics.hpp>
#include "draw.hpp"
#include "data.hpp"
#include "easy_sfml.hpp"
#include <iostream>



std::vector<std::unique_ptr<object>> objects;

int main(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	object* canvas = new_object(objects,"canvas" , 0, 0, 0, 0, null, 10, 10,sf::Color::Black);
	canvas->size = sf::Vector2f(200,200);

	canvas->scale_pos.x = 0;
	canvas->scale_pos.y = 0;

	old_size(window);
	object* obj = new_object(objects,"in" , 20, 20, 10, 10, canvas, 0, 10, sf::Color::Magenta);
	obj->scale_pos = sf::Vector2i(0, 0);


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
		std::cout << "size_x: " << canvas->size.x << "; size_y: " << canvas->size.y << std::endl;
		std::cout << "real_size_x: " << canvas->real_size.x << "; real_size_y: " << canvas->real_size.y << std::endl;
		update_window(window,objects);	
    }

    return 0;
}
