#pragma once
#include "Object.h"
#include "EventCollision.h"

class Character_CPP_Plus : public df::Object {

private:
	void out();
	void hit(const df::EventCollision* p_collision_event);
	int time_to_live;
	int m_speed;

public:
	Character_CPP_Plus(df::Vector hero_position, int speed, int time);
	int eventHandler(const df::Event* p_e);
	void step();
};