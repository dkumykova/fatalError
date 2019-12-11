#pragma once

#include "Object.h"
#include "EventCollision.h"

class JavaClone : public df::Object {

private:
	
	void hit(const df::EventCollision* p_collision_event);

public:
	JavaClone(df::Vector dir);
	int eventHandler(const df::Event* p_e);
};