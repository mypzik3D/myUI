#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

sf::Vector2u old_size_window;

void old_size(sf::RenderWindow& window){
    old_size_window = window.getSize();
}

class object;

void rectangle_draw(sf::RenderWindow& window, object& obj);

class object{
public:
    std::string name;
	sf::Color color;
	
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f real_size=sf::Vector2f(0,0), real_pos=sf::Vector2f(0,0);
	std::string type = "sprite";
    bool isActive, isInput, statusInput, isWisible;
	sf::Vector2i stick_pos;
	sf::Vector2i origin_pos;
	sf::Vector2i scale_pos;
	float rotate_angle = 0;
	int layer;

	object* stick_object;

	void draw(sf::RenderWindow& window){
		if(type == "sprite")
		rectangle_draw(window, *this);
	}
};
	
object* null;

void rectangle_draw(sf::RenderWindow& window, object& obj){
	sf::RectangleShape shape;

    float psX=obj.position.x;
	float psY=obj.position.y;
    float spX=obj.size.x;
    float spY=obj.size.y;

    if(obj.scale_pos.x == 1 || obj.scale_pos.x == -1){
		spX = obj.size.x+(float)window.getSize().x/2-(float)old_size_window.x/2;
	}
    if(obj.scale_pos.y == 1 || obj.scale_pos.y == -1){
		spY = obj.size.y+(float)window.getSize().y/2-(float)old_size_window.y/2;
	}
    if(obj.scale_pos.x == 0){
		spX = obj.size.x+(float)window.getSize().x-(float)old_size_window.x;
	}
    if(obj.scale_pos.y == 0){
	    spY = obj.size.y+(float)window.getSize().y-(float)old_size_window.y;		
	}
		
    obj.real_size.x = spX;
	obj.real_size.y = spY;
		
    if(obj.stick_object != null){
		if(obj.stick_pos.x == 0){
			psX = ((float)obj.stick_object->real_size.x)/2-obj.real_size.x/2+obj.position.x+(float)obj.stick_object->real_pos.x;
		}
		if(obj.stick_pos.x == 1){
			psX = ((float)obj.stick_object->real_size.x)-obj.real_size.x-obj.position.x+(float)obj.stick_object->real_pos.x;
		}
		if(obj.stick_pos.x == -1){
			psX = (float)obj.position.x+obj.stick_object->real_pos.x;
		}

		if(obj.stick_pos.y == 0){
			psY = ((float)obj.stick_object->real_size.y)/2-obj.real_size.y/2+obj.position.y+(float)obj.stick_object->real_pos.y;
		}
		if(obj.stick_pos.y == 1){
			psY = ((float)obj.stick_object->real_size.y)-obj.real_size.y-obj.position.y+(float)obj.stick_object->real_pos.y;
		}
		if(obj.stick_pos.y == -1){
			psY = (float)obj.position.y+obj.stick_object->real_pos.y;
		}
	}
	obj.real_pos.x = psX;
	obj.real_pos.y = psY;

	shape.setSize(sf::Vector2f(spX, spY));
	shape.setPosition(sf::Vector2f(psX,psY));
	shape.setFillColor(obj.color);
	window.draw(shape);
}

object* new_object(std::vector<std::unique_ptr<object>>& massive,std::string name, float pos_x, float pos_y, float size_x, float size_y, object* obj_stick = null,int st_x=2,int st_y=0, sf::Color color=sf::Color::White){
	auto obj = std::make_unique<object>();
	obj->name = name;
	obj->position.x = pos_x;
	obj->position.y = pos_y;
	obj->size.x = size_x;
	obj->size.y = size_y;
	obj->color = color;
	obj->stick_pos.x = st_x;
	obj->stick_pos.y = st_y;
	obj->stick_object = obj_stick;
	massive.push_back(std::move(obj));
	return massive.back().get();
}


