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

	object* canvas = new_object(objects,"canvas" , 0, 0, 0, 0, null, 10, 10,sf::Color::Black);
	canvas->size = sf::Vector2f(200,200);

	object* obj = new_object(objects,"center",0,0,120,50,canvas,-1,-1,sf::Color(120,100,200,100));
    obj->type = "round";
    obj->radius = 20;

	object* text = new_object(objects,"texte",0,0,30,0,obj,0,0,sf::Color::White);
    text->type = "text";
	text->text = "UwU";
	 
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
