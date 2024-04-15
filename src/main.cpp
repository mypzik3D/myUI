#include <SFML/Graphics.hpp>
#include "draw.hpp"
#include "data.hpp"
#include <iostream>



std::vector<std::unique_ptr<object>> objects;

int main(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	object* canvas = new_object(objects,"canvas" , 0, 0, 0, 0, null, 10, 10,sf::Color::White);
	canvas->size = sf::Vector2f(200,200);

	old_size(window);

	object* obj = new_object(objects,"in" , 0, 0, 90, 90, canvas, 0, 0, sf::Color(222,255,111,200));
	obj->scale_pos = sf::Vector2i(0, 0);
	object* obj1 = new_object(objects,"in" , 0, 0, 40, 40, obj, -1, -1, sf::Color(222,0,111,200));
	obj1->scale_pos = sf::Vector2i(-1, 2);
	object* obj2 = new_object(objects,"in" , 0, 0, 40, 40, obj, 1, 1, sf::Color(222,0,111,200));
	obj2->scale_pos = sf::Vector2i(1, 2);
	object* obj3 = new_object(objects,"in" , 0, 0, 40, 40, obj, -1, 1, sf::Color(222,0,111,200));
	obj3->scale_pos = sf::Vector2i(4, 1);
	object* obj4 = new_object(objects,"in" , 0, 0, 40, 40, obj, 1, -1, sf::Color(222,0,111,200));
	obj4->scale_pos = sf::Vector2i(4, 1);





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
