// Implementation of Character - C

// Game Include
#include "Character_Java.h"
#include "Bullet.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_Java::Character_Java() {

	//link to ship sprite
	setSprite("Character_Java");

	// Set Attack Related Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
	setSuperDamage(100);
	setSuperCastTime(2); // 2 secs

	// Set Jump Speed
	setJumpSpeed(INITIAL_JUMP_SPEED);

	// Set Slowdowns (Character Unique) [30 means 1 sec] 
	// [Parameter 2 default as false. If true, means set countdown to slowdown at the same time]
	setHorizontalSlowdown(2, true);
	setJumpSlowdown(30, true);
	setDefenseSlowdown(30, true);
	setAttackOneSlowdown(30, true);
	setSuperAttackSlowdown(900, true); // 30 secs
	setSuperChanelingSlowdown(60, true);

	setIsHigherLevel(true); 

	//super_countdown = 10;
	//super = new LispSuper();
	//super->setActive(false);

}

void Character_Java::do_action_move_right() {
	move(1.5, 0);
}

void Character_Java::do_action_move_left() {
	move(-1.5, 0);
}

void Character_Java::do_action_jump() {
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_Java::do_action_defense() {
	//implementation in player character
}

void Character_Java::do_action_attack_1() {
	//normal - jump up and duplicate into 3 versions of self that land, but only 1 does damage - randomly chosen
	setVelocity(df::Vector(0, getJumpSpeed()));

	Vector p1 = Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY());
	
	//getPlayer()->getOpponentPlayer().
	clone1 = new JavaClone(p1);
	clone1->setVelocity(df::Vector(2 * getPlayer()->getFacingRight(), 3));
	
	
	
}

void Character_Java::do_action_super_attack() {
	// To do
	//i want to use a countdown but might need to use a clock since i can't override eventhandler here

	LM.writeLog("Lisp super called");
	//setSprite("Character_Lisp_super");
	//super->setPosition(Vector(getPosition().getX(), getPosition().getY()));
	//super->setActive(true);


	//getAnimation().getSprite()->setColor(df::CYAN);
	//setSprite("Character_Lisp"); //set sprute back to normal


}



void Character_Java::flipSprite(PlayerCharacter::SpriteStatus sprite_status) {

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_Java");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_Java_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_Java_error");
		break;
	default:
		break;
	}
}

