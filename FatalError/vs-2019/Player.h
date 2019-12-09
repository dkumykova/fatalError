#pragma once
// The Player Class
// Helps Control Player Chracter



// Includes

// Game Includes
#include "Object.h"
#include "PlayerCharacter.h"
#include <Clock.h>

// Event Includes
#include "EventKeyboard.h"

// Engine Includes


// Defines
#define PLAYER_MAX_HEALTH 100

class Player : public df::Object{

private :
	// Attributes
	int m_health; // player health
	bool facing_right;

	// Functions
	int virtual eventHandler(const df::Event* p_e); // Event Hanlder
	void virtual kbd(const df::EventKeyboard* p_key_event); // Listen and react to the keyboard inputs

protected:
	void setHealth(int health); // Setter for health
	Clock* my_clock; // Clock
	PlayerCharacter* m_p_character; // Pointer of the character

public:
	Player(); // Constructor

	int getHealth() const; // Getter for Player Health	
	virtual void handleHealth(int damage); // Handle Health

	void setCharacter(PlayerCharacter* new_char); // Set Character 
	int getFacingRight();
	void swapFacing();

};