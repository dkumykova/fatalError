#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Reticle.h"
#include <Clock.h>
//#include "Clock.h>
#define TERMINAL_VELOCITY 3

using namespace df;

class PlayerCharacter : public df::Object {
	
	
private:
	
	// Step Event Related
	void step();

	// Move Related
	void move(int dx, int dy);
	int move_slowdown;
	int move_countdown;
	int jump_countdown;

	// Acceleration Related
	Vector acceleration;
	bool on_ground;

	// Mouse Related
	Reticle* p_reticle;
	void mouse(const df::EventMouse* p_mouse_event);
	
	// Keyboard Related
	void kbd(const df::EventKeyboard* p_key_event);

	// Hit Point Related
	int health;

	// Attack Related
	int attack_1_damage;
	int attack_2_damage;

	// Collision Related
	void collide(const df::EventCollision* p_c_event);

	Clock *my_clock;

public:

	// Constructor and Desctructor 
	PlayerCharacter(); 
	~PlayerCharacter();

	// Event Handler
	int eventHandler(const df::Event* p_e);

	// Get for Health Point
	int getHealth() const;

	// Attack Related
	virtual void attack_1();
	virtual void attack_2();
	virtual void specialAttack();

	void handleHealth();
};

