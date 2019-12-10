#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

// Defines
#define TERMINAL_VELOCITY_X 3
#define TERMINAL_VELOCITY_Y 3
#define JUMP_VELOCITY -5

using namespace df;



class Player; // Helps deal with mutual reference
class PlayerCharacter : public df::Object {
	
	
	
private:

	// Step Event Related
	void step(); // General Step Processor
	virtual void stepProcessor(); // Character Specific Step Processor

	// Move Related
	int move_slowdown;
	int move_countdown;
	int jump_countdown;
	bool on_ground; // Help Collision only Process Once if on_ground

	// Acceleration Related
	Vector acceleration;

	// Attack Related
	int m_attack_1_damage;
	int m_attack_2_damage;

	// Player Pointer
	Player* m_p_player;

public:
	// Constructor and Desctructor 
	PlayerCharacter();
	~PlayerCharacter();

	// Get Player
	void setPlayer(Player* n_player);
	Player* getPlayer() const;
	
	// Move Related
	virtual void moveRight();
	virtual void moveLeft();
	virtual void jump();
	void move(int dx, int dy);
	void setCharacterAcceleration(Vector new_a);
	void swapOnGroundStatus();

	// Event Handler
	int virtual eventHandler(const df::Event* p_e);

	// Attack Related
	virtual void attack_1();
	virtual void attack_2();
	virtual void specialAttack();
	void setAttackOneDamage(int damage);
	int getAttackOneDamage() const;
	void setAttackTwoDamage(int damage);
	int getAttackTwoDamage() const;

	// Sprite Related
	enum SpriteStatus { Original, Flipped, Attacking, Defending, Jumping };
	virtual void flipSprite(SpriteStatus sprite_status);

	// Collision Related
	void collide(const df::EventCollision* p_c_event); // General Collision Process
	void virtual processCollision(); // Character Specific Collision Process
};

