// Implementation of Character - Python

// Game Include
#include "Character_Python.h"
#include "Player.h"
#include "Character_pip.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_Python::Character_Python() {

	//link to ship sprite
	setSprite("Character_Python");
	setDefaultColor(df::WHITE, true); // Second parameter default as false. If true, update the default color to sprite also.
	setHeightOfSprite(5);

	// Set Attack Related Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
	setSuperCastTime(2); // 2 secs

	// Set Jump Speed
	setJumpSpeed(-4);

	// Set Slowdowns (Character Unique) [30 means 1 sec] 
	// [Parameter 2 default as false. If true, means set countdown to slowdown at the same time]
	setHorizontalSlowdown(1, true);
	setJumpSlowdown(15, true);
	setDefenseSlowdown(30, true);
	setAttackOneSlowdown(30, true);
	setAttackTwoDamage(3);
	setSuperAttackSlowdown(900); // 30 secs
	setSuperChanelingSlowdown(1,true);
}

void Character_Python::do_action_move_right() {
	move(2, 0);
}

void Character_Python::do_action_move_left() {
	move(-2, 0);
}

void Character_Python::do_action_jump() {
	LM.writeLog("Python calling jump");
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_Python::do_action_defense() {

}

void Character_Python::do_action_attack_1() {

}

void Character_Python::do_action_super_attack() {
	new Character_Pip(this);
}



void Character_Python::flipSprite(PlayerCharacter::SpriteStatus sprite_status) {

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_Python");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_Python_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_Python_error");
		break;
	default:
		break;
	}
}

void Character_Python::attackingbot(int damage){
	getPlayer()->getOpponentPlayer()->handleHealth(damage);
}

