#pragma once
enum class tanim{
	finite = 0,
	cycle = 1
};
enum class graph{
	straight = 0,
	smoothly = 1
};

class animation{
	private:
		float time_to_end;
	public:
		graph grap;
		tanim type;
		float time;
		float* transform_number;
		float delay;
		float to;
		bool work = true;

		float old_pos;
		float progress;
		float leight;

		void calc_transform();
};

void update_animations();
void add_animation(float* transform,float to, float time, graph grap = graph::smoothly, tanim type=tanim::finite);
