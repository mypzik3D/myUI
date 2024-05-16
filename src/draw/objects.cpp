#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "myUI.hpp"
#include <math.h>

sf::Vector2u old_size_window;
sf::Vector2f mouse_pos;

void old_size(sf::RenderWindow& window){
    old_size_window = window.getSize();
}
object* null;
object* get_null_object(){
	return null;
}


object::object(){	
	min_size = sf::Vector2f(1,1);
	real_size=sf::Vector2f(0, 0); real_pos=sf::Vector2f(0, 0);
	type = "sprite";

    isActive=true; isVisible=true;
	stick_pos  = sf::Vector2i(0,0);
	origin_pos = sf::Vector2i(-1,-1);
	scale_pos  = sf::Vector2i(0,0);
	rotate_angle = 0;
}

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
	sf::Vector2f size = sf::Vector2f(spX,spY);
	if(size.x > obj.max_size.x && obj.max_size.x!=0)
		size.x = obj.max_size.x;
	if(size.y > obj.max_size.y && obj.max_size.y!=0)
		size.y = obj.max_size.y;
	if(size.x < obj.min_size.x && obj.min_size.x!=0)
		size.x = obj.min_size.x;
	if(size.y < obj.min_size.y && obj.min_size.y!=0)
		size.y = obj.min_size.y;
	return size;
}

void calc_layer(std::vector<std::unique_ptr<object>>& massive){
    for(int i = 0; i < massive.size(); i++){
		object* obj = massive.at(i).get();
    	int a = 0;
		while(true){
		    if(obj->stick_object == null){
			     break;   
			}else{
				obj = obj->stick_object;
				a++;
			}
		}
		massive.at(i)->layer = a;
	}
}

bool get_input;

//------------------------------------------------------------------------

void RoundedRectangle(object& obj,sf::RenderWindow& window){
    int POINTS = (int)obj.radius;
	
	sf::Vector2f size = set_size(obj, window);
    obj.real_size = size;

    sf::Vector2f pos = set_pos(obj);
	obj.real_pos = pos;
    
    float psX=pos.x;
	float psY=pos.y;
    float spX=size.x;
    float spY=size.y;

	/* https://en.sfml-dev.org/forums/index.php?topic=973.0 */
    if(obj.isVisible){
		sf::ConvexShape rrect;
		rrect.setPointCount(POINTS*4);
		rrect.setOutlineThickness(obj.outline);
		rrect.setOutlineColor(obj.outline_col);
		rrect.setFillColor(obj.color);
		float X=0,Y=0;
		int a = 0;
		for(int i=0; i<POINTS; i++){
			X+=(int)obj.radius/POINTS;
			Y=sqrt((int)obj.radius*obj.radius-X*X);
			rrect.setPoint(a, sf::Vector2f(X+psX+spX-obj.radius,psY-Y+obj.radius));
			a++;
		}
		Y=0;
		for(int i=0; i<POINTS; i++){
			Y+=(int)obj.radius/POINTS;
			X=sqrt((int)obj.radius*obj.radius-Y*Y);
			rrect.setPoint(a, sf::Vector2f(psX+spX+X-obj.radius,psY+spY-obj.radius+Y));
			a++;
		}
		X=0;
		for(int i=0; i<POINTS; i++){
			X+=(int)obj.radius/POINTS;
			Y=sqrt((int)obj.radius*obj.radius-X*X);
			rrect.setPoint(a, sf::Vector2f(psX+obj.radius-X,psY+spY-obj.radius+Y));
			a++;
		}
		Y=0;
		for(int i=0; i<POINTS; i++){
			Y+=(int)obj.radius/POINTS;
			X=sqrt((int)obj.radius*obj.radius-Y*Y);
			rrect.setPoint(a, sf::Vector2f(psX-X+obj.radius,psY+obj.radius-Y));
			a++;
		}
		window.draw(rrect);
	}
}

void rectangle_draw(sf::RenderWindow& window, object& obj){
    if(obj.isActive)	
	if(obj.radius == 0){    
		sf::Vector2f size = set_size(obj, window);
		obj.real_size = size;

		sf::Vector2f pos = set_pos(obj);
		obj.real_pos = pos;
		
		if(obj.isVisible){
			sf::RectangleShape shape;
			shape.setOutlineThickness(obj.outline);
			shape.setOutlineColor(obj.outline_col);
			shape.setSize(size);
			shape.setPosition(pos);
			shape.setFillColor(obj.color);
			window.draw(shape);
		}
	}else{
		RoundedRectangle(obj, window);
	}
}

void text_draw(sf::RenderWindow& window, object& obj){
    if(obj.isActive){	
		sf::Text shape;
		shape.setFont(*obj.font);
		shape.setString(obj.text);

		sf::Vector2f pos = set_pos(obj);
		obj.real_pos = pos;
	
		sf::FloatRect textRect = shape.getLocalBounds();
		sf::Vector2f textSize(textRect.width, textRect.height);

		obj.real_size = textSize;	
		obj.real_pos = pos;
		if(obj.isVisible){
			shape.setCharacterSize(obj.size.x);
			shape.setFillColor(obj.color);
			shape.setOutlineColor(obj.outline_col);
			shape.setOutlineThickness(obj.outline);
			shape.setPosition(pos);
		    window.draw(shape);
		}
	}
}

//-draw---

void object::draw(sf::RenderWindow& window){
	if(type == "sprite")
		rectangle_draw(window, *this);
	if(type == "text")
	    text_draw(window, *this);
}

//-----------------------------------------------------------------------

object* new_object(std::vector<std::unique_ptr<object>>& massive,std::string type, float pos_x, float pos_y, float size_x, float size_y, object* obj_stick = null,int st_x=2,int st_y=0, sf::Color color=sf::Color::White){
	auto obj = std::make_unique<object>();
	obj->type = type;
	obj->position.x = pos_x;
	obj->position.y = pos_y;
	obj->size.x = size_x;
	obj->size.y = size_y;
	obj->color = color;
	obj->stick_pos.x = st_x;
	obj->stick_pos.y = st_y;
	obj->stick_object = obj_stick;
	massive.push_back(std::move(obj));
	calc_layer(massive);
	return massive.back().get();
}

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
