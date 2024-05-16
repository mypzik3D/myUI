#include <memory>
#include <vector>
#include <math.h>
#include "anim.hpp"

std::vector<std::unique_ptr<animation>> animations;

void animation::calc_transform(){
	float a = *transform_number;
	old_pos = a;
	leight = to - a;
	delay=1/time;
}

void delete_anim(){

}

float smoothly(float a){
	return ((pow((a-1),3))+1);
}

float straight(float a){
	return a;
}

void update_animations(){
	for(const auto & i : animations){
		if(i.get()->progress>=1){
			delete_anim();
			continue;
			i.get()->work = false;
		}
		else{
			i.get()->progress+=i.get()->delay;
			if(i.get()->delay >= 1)
				i.get()->delay = 1;

			if(i.get()->grap == graph::smoothly)
				*i.get()->transform_number=i.get()->leight*smoothly(i.get()->progress);	
			else if(i.get()->grap == graph::smoothly)
				*i.get()->transform_number=i.get()->leight*straight(i.get()->progress);	

		}
	}
}

void add_animation(float* transform,float to, float time, graph grap, tanim type){
	auto anim = std::make_unique<animation>();
	anim->grap = grap;
	anim->type = type;
	anim->time = time;
	anim->to = to;
	anim->transform_number = transform;
	anim->calc_transform();
	animations.push_back(std::move(anim));
}

