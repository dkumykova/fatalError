
// The Player Class
// Helps Control Player Chracter



// Includes

// Game Includes
#include "Object.h"
#include "PlayerCharacter.h"

// Event Includes
#include "EventKeyboard.h"
#include "ControlsDisplay.h"

// Engine Includes

#ifndef __PLAYER_H__
#define __PLAYER_H__
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

	ControlsDisplay* controls;
	int playerNum;

protected:
	void setHealth(int health); // Setter for health
	PlayerCharacter* m_p_character; // Pointer of the character
	Player* m_p_other_player; // Pointer to the opponent player

public:
	Player(); // Constructor

	int getHealth() const; // Getter for Player Health	
	virtual void handleHealth(int damage); // Handle Health

	virtual void setCharacter(PlayerCharacter* new_char); // Set Character 
	PlayerCharacter* getCharacter() const; // Get Character

	void setOpponentPlayer(Player* new_player); // Set opponent player pointer
	Player* getOpponentPlayer() const; // Get opponent player pointer

	float getLeftBoundary(); // Ask the related sprite for left boundary
	float getRightBoundary(); // Ask the related sprite for right boundary
	
	int getFacingRight(); // Return 1 if facing right (relative to the opponent player), else -1
	void swapFacing(); // Swap the facing_right status

	ControlsDisplay* getControls() const;
	
	int getPlayerNum() const;
	void setPlayerNum(int n);



};

#endif