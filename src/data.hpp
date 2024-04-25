#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "data-files.hpp"
#include <math.h>

sf::Vector2u old_size_window;
sf::Vector2f mouse_pos;

void old_size(sf::RenderWindow& window){
    old_size_window = window.getSize();
}

class object;

void RoundedRectangle(object& obj,sf::RenderWindow& window);
void rectangle_draw(sf::RenderWindow& window, object& obj);
void text_draw(sf::RenderWindow& window, object& obj);

class object{
public:
    std::string name;
	sf::Color color, outline_col;
	
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f real_size=sf::Vector2f(0, 0), real_pos=sf::Vector2f(0, 0);
	sf::Vector2f min_size, max_size;
	std::string type = "sprite";

	sf::Font* font = &betterVCR;
	sf::String text;

    bool isActive, isInput, statusInput, isWisible;
	sf::Vector2i stick_pos  = sf::Vector2i(0,0);
	sf::Vector2i origin_pos = sf::Vector2i(-1,-1);
	sf::Vector2i scale_pos  = sf::Vector2i(0,0);
	float rotate_angle = 0;
	int layer;
    float radius=10, outline;
	object* stick_object;

	void draw(sf::RenderWindow& window){
		if(type == "sprite")
			rectangle_draw(window, *this);
		if(type == "round")
			RoundedRectangle(*this, window);
		if(type == "text")
		    text_draw(window, *this);

	}
};
	
object* null;

sf::Vector2f set_pos(object obj){
    float psX=obj.position.x;
	float psY=obj.position.y;
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
    return sf::Vector2f(psX,psY);
}

sf::Vector2f set_size(object obj, sf::RenderWindow& window){
    float spX=obj.size.x;
    float spY=obj.size.y;
    
	if(obj.stick_object != null){
		if(obj.scale_pos.x > 0){
			spX = obj.size.x+obj.stick_object->real_size.x/(float)obj.scale_pos.x-obj.stick_object->size.x/(float)obj.scale_pos.x;
		}
		if(obj.scale_pos.y > 0){
			spY = obj.size.y+obj.stick_object->real_size.y/(float)obj.scale_pos.y-obj.stick_object->size.y/(float)obj.scale_pos.y;
		}	
    }else{
		if(obj.scale_pos.x > 0){
			spX = obj.size.x+(float)window.getSize().x/obj.scale_pos.x-(float)old_size_window.x/obj.scale_pos.x;
		}
		if(obj.scale_pos.y > 0){
			spY = obj.size.y+(float)window.getSize().y/obj.scale_pos.y-(float)old_size_window.y/obj.scale_pos.y;
		}
    }
	return sf::Vector2f(spX, spY);
}

void rectangle_draw(sf::RenderWindow& window, object& obj){
	sf::RectangleShape shape;
    
	sf::Vector2f size = set_size(obj, window);
    obj.real_size = size;

    sf::Vector2f pos = set_pos(obj);
	obj.real_pos = pos;

	shape.setOutlineThickness(obj.outline);
	shape.setOutlineColor(obj.outline_col);
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setFillColor(obj.color);
	window.draw(shape);
}


void RoundedRectangle(object& obj,sf::RenderWindow& window)
{
    int POINTS = obj.radius;

	sf::Vector2f size = set_size(obj, window);
    obj.real_size = size;

    sf::Vector2f pos = set_pos(obj);
	obj.real_pos = pos;
    
    float psX=pos.x;
	float psY=pos.y;
    float spX=size.x;
    float spY=size.y;

	/* https://en.sfml-dev.org/forums/index.php?topic=973.0 */
	sf::ConvexShape rrect;
	rrect.setPointCount(POINTS*4);
	rrect.setOutlineThickness(obj.outline);
	rrect.setOutlineColor(obj.outline_col);
	rrect.setFillColor(obj.color);
	float X=0,Y=0;
	int a = 0;
	for(int i=0; i<POINTS; i++)
	{
		X+=obj.radius/POINTS;
		Y=sqrt(obj.radius*obj.radius-X*X);
		rrect.setPoint(a, sf::Vector2f(X+psX+spX-obj.radius,psY-Y+obj.radius));
		a++;
	}
	Y=0;
	for(int i=0; i<POINTS; i++)
	{
		Y+=obj.radius/POINTS;
		X=sqrt(obj.radius*obj.radius-Y*Y);
		rrect.setPoint(a, sf::Vector2f(psX+spX+X-obj.radius,psY+spY-obj.radius+Y));
		a++;
	}
	X=0;
	for(int i=0; i<POINTS; i++)
	{
		X+=obj.radius/POINTS;
		Y=sqrt(obj.radius*obj.radius-X*X);
		rrect.setPoint(a, sf::Vector2f(psX+obj.radius-X,psY+spY-obj.radius+Y));
		a++;
	}
	Y=0;
	for(int i=0; i<POINTS; i++)
	{
		Y+=obj.radius/POINTS;
		X=sqrt(obj.radius*obj.radius-Y*Y);
		rrect.setPoint(a, sf::Vector2f(psX-X+obj.radius,psY+obj.radius-Y));
		a++;
	}
	window.draw(rrect);
}

void text_draw(sf::RenderWindow& window, object& obj){
    sf::Text shape;
    shape.setFont(*obj.font);
	shape.setString(obj.text);

    sf::Vector2f pos = set_pos(obj);
	obj.real_pos = pos;
    
	shape.setCharacterSize(obj.size.x);
	shape.setFillColor(obj.color);
	//shape.setOutlineColor(obj.outline_col);
	//shape.setOutlineThickness(obj.outline);

	sf::FloatRect textRect = shape.getLocalBounds(); // получение границ текста
	sf::Vector2f textSize(textRect.width, textRect.height); // размеры текста

    obj.real_size = textSize;
		
	obj.real_pos = pos;
    shape.setPosition(pos);
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


