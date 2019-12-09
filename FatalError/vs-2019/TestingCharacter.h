#pragma once

#include "PlayerCharacter.h"

class TestCharacter : public PlayerCharacter {

public:
	TestCharacter();
	void kbd(const df::EventKeyboard* p_key_event);
	void collide(const df::EventCollision* p_c_event);
};