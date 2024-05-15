#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

void old_size(sf::RenderWindow& window);

class object{
	public:
	    std::string name;
		sf::Color color, outline_col;
	
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Vector2f real_size=sf::Vector2f(0, 0), real_pos=sf::Vector2f(0, 0);
		sf::Vector2f min_size, max_size;
		std::string type = "sprite";

		sf::Font* font;
		sf::String text;

		bool isActive=true, isInput, statusInput, isVisible=true;
		sf::Vector2i stick_pos  = sf::Vector2i(0,0);
		sf::Vector2i origin_pos = sf::Vector2i(-1,-1);
		sf::Vector2i scale_pos  = sf::Vector2i(0,0);
		float rotate_angle = 0;
		int layer;
		float radius, outline;
		object* stick_object;

		object();
		void draw(sf::RenderWindow& window);
};



object* new_object(std::vector<std::unique_ptr<object>>& massive,std::string type, float pos_x, float pos_y, float size_x, float size_y, object* obj_stick,int st_x,int st_y, sf::Color color);

void update_window(sf::RenderWindow& window,std::vector<std::unique_ptr<object>>& objects);
object* get_null_object();
