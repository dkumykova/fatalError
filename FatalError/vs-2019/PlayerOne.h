#pragma once

#include "Player.h"

class PlayerOne : public Player {

private:
	void kbd(const df::EventKeyboard* p_key_event); // Listen and react to the keyboard inputs

public:
	PlayerOne();
	void handleHealth(int damage); // Handle Health
};