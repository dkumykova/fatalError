#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "CommentWall.h"

// Defines
#define TERMINAL_VELOCITY_X 3
#define TERMINAL_VELOCITY_Y 3
#define INITIAL_JUMP_SPEED -5

using namespace df;



class Player; // Helps deal with mutual reference
class PlayerCharacter : public df::Object {
	
	
	
private:

	// Step Event Related
	void step(); // General Step Processor
	virtual void stepProcessor(); // Character Specific Step Processor

	// Counter Related
	int horizontal_move_slowdown;
	int horizontal_move_countdown;
	int jump_slowdown;
	int jump_countdown;
	int attack_1_slowdown;
	int attack_1_countdown;
	int attack_2_slowdown;
	int attack_2_countdown;
	int error_attack_channeling_slowdown;
	int error_attack_channeling_countdown;
	int super_attack_slowdown;
	int super_attack_countdown;
	int super_channeling_slowdown;
	int super_channeling_countdown;
	int defense_slowdown;
	int defense_countdown;

	// Move Related
	float jump_speed; // The jump speed
	bool on_ground; // Help Collision only Process Once if on_ground

	// Acceleration Related
	Vector acceleration;

	// Attack Related
	int m_attack_1_damage;
	int m_attack_2_damage;
	int m_super_cast_time;
	bool m_error_attacking;
	bool m_error_channeling;
	bool m_super_channeling;
	bool m_super_attacking;

	bool isHigherLevel; //true if language is higher level, false if not
	CommentWall *wall;

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
	virtual void processRightArrow();
	virtual void processLeftArrow();
	virtual void processUpArrow();
	virtual void processDownArrow();
	void move(float dx, float dy);
	void setCharacterAcceleration(Vector new_a);
	void setOnGroundStatus(bool status);
	void setJumpSpeed(float speed);
	float getJumpSpeed() const;

	// Event Handler
	int virtual eventHandler(const df::Event* p_e);

	// Attack Related
	void attack_1(); // Normal Attack. Character Dependent
	void attack_2(); // Error Attack. A Generalized Form of Attacking
	void specialAttack();
	void setAttackOneDamage(int damage);
	int getAttackOneDamage() const;
	void setAttackTwoDamage(int damage);
	int getAttackTwoDamage() const;
	void setErrorAttacking(bool status);
	bool getErrorAttacking() const;
	bool getErrorChanneling() const;
	void startSuperChanneling();
	void startErrorChanneling();

	// Sprite Related
	enum SpriteStatus { Original, Flipped, Normal_Attacking, Defending, Jumping, Error_Attacking };
	virtual void flipSprite(SpriteStatus sprite_status);

	// Collision Related
	void collide(const df::EventCollision* p_c_event); // General Collision Process
	virtual void processCollision(); // Character Specific Collision Process

	// SlowDown (Counter) Related
	void setHorizontalSlowdown(int slowdown, bool counterAlso = false);
	void setJumpSlowdown(int slowdown, bool counterAlso = false);
	void setDefenseSlowdown(int slowdown, bool counterAlso = false);
	void setAttackOneSlowdown(int slowdown, bool counterAlso = false);
	void setAttackTwoSlowdown(int slowdown, bool counterAlso = false); // Should be private to children. But put here for convenience
	void setSuperAttackSlowdown(int slowdown, bool counterAlso = false);
	void setSuperChanelingSlowdown(int slowdown, bool counterAlso = false);
	void setSuperCastTime(int time);


	// Counter Related
	bool isTimeToJump();
	bool isTimeToHorizontalMove();
	bool isTimeToDefense();
	bool isTimeToAttackOne();
	bool isTimeToAttackTwo(); // Should be private to children. But put here for convenience
	bool isTimeToSuperAttack();
	void getFrozen(int time); // If need to be imobolized for specific time, use this function. Time in seconds.

	// Actions Children Can Do, And Should Do
	virtual void do_action_jump();
	virtual void do_action_defense(bool isHigher);
	virtual void do_action_move_right();
	virtual void do_action_move_left();
	virtual void do_action_attack_1();
	virtual void do_action_attack_2(int damage); // Should be private to children. But put here for convenience
	virtual void do_action_super_attack();

	void setIsHigherLevel(bool is);
	bool getIsHigherLevel() const;

	

};

