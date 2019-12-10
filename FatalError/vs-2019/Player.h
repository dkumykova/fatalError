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
	Player* m_p_other_player; // Pointer to the opponent player

public:
	Player(); // Constructor

	int getHealth() const; // Getter for Player Health	
	virtual void handleHealth(int damage); // Handle Health

	virtual void setCharacter(PlayerCharacter* new_char); // Set Character 
	

	void setOpponentPlayer(Player* new_player); // Set opponent player pointer
	Player* getOpponentPlayer() const; // Get opponent player pointer

	float getLeftBoundary(); // Ask the related sprite for left boundary
	float getRightBoundary(); // Ask the related sprite for right boundary
	
	int getFacingRight(); // Return 1 if facing right (relative to the opponent player), else -1
	void swapFacing(); // Swap the facing_right status



};