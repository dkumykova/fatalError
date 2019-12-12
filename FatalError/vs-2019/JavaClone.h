#pragma once

#include "Object.h"
#include "EventCollision.h"

class JavaClone : public df::Object {

private:
	bool affect;
	void hit(const df::EventCollision* p_collision_event);

public:
	int countdown;

	JavaClone(df::Vector dir);
	int eventHandler(const df::Event* p_e);
	void step();
	void setAffect(bool t);
	bool getAffect() const;

};