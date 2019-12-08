#pragma once

#include "PlayerCharacter.h"

class TestCharacter2 : public PlayerCharacter {

public:
	TestCharacter2();
	void kbd(const df::EventKeyboard* p_key_event);
	void collide(const df::EventCollision* p_c_event);
};