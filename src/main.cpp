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
	canvas->scale_pos = sf::Vector2i(1,1);

    object* cent1 = new_object(objects, "b", 10,0,180,180,canvas,-1,0,sf::Color::White);
	cent1->scale_pos = sf::Vector2i(1,1);
    object* cent2 = new_object(objects, "b", 5,0,160,170,cent1,-1,0,sf::Color::Red);
	cent2->scale_pos = sf::Vector2i(2,1);
    object* cent3 = new_object(objects, "b", 5,0,140,160,cent2,-1,0,sf::Color::Green);
	cent3->scale_pos = sf::Vector2i(1,2);
	object* cent4 = new_object(objects, "b", 5,0,120,150,cent3,-1,0,sf::Color::Blue);
	cent4->scale_pos = sf::Vector2i(2,1);
	object* cent5 = new_object(objects, "b", 5,0,100,140,cent4,-1,0,sf::Color::Cyan);
	cent5->scale_pos = sf::Vector2i(1,2);
    object* cent6 = new_object(objects, "b", 5,0,80,130,cent5,-1,0,sf::Color::Green);
	cent6->scale_pos = sf::Vector2i(2,1);

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
