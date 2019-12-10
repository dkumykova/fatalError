#pragma once

#include "Player.h"

class PlayerTwo : public Player {

private:
	void kbd(const df::EventKeyboard* p_key_event); // Listen and react to the keyboard inputs

public:
	PlayerTwo();
	void handleHealth(int damage); // Handle Health
	void setCharacter(PlayerCharacter* new_char);
};