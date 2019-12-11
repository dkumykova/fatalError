#pragma once
#include "Object.h"
//#include "PlayerCharacter.h"
#include <EventCollision.h>


using namespace df;
class LispSuper : public df::Object {
private:
	int countdown;
	//int damageSaved;
	//PlayerCharacter* character;
public:
	LispSuper();
	int eventHandler(const df::Event* p_e);
	void collide(const df::EventCollision* p_e);
	void step();
	void setCountdown(int num);
	int getCountdown() const;

};


