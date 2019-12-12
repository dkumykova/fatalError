#pragma once

#include "Object.h"
#include "EventCollision.h"

class Character_C_Pointer : public df::Object {

private:
	void out();
	void hit(const df::EventCollision* p_collision_event);

public:
	Character_C_Pointer(df::Vector hero_position);
	int eventHandler(const df::Event* p_e);
};