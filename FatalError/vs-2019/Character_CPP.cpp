// Implementation of Character - C

// Game Include
#include "Character_CPP.h"
#include "Character_CPP_plus.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_CPP::Character_CPP() {

	//link to ship sprite
	setSprite("Character_CPP");
	setDefaultColor(df::WHITE, true); // Second parameter default as false. If true, update the default color to sprite also.
	setHeightOfSprite(8);

	// Set Attack Related Damage 
	setAttackOneDamage(10);
	setAttackTwoDamage(5);
	setSuperCastTime(2); // 2 secs

	// Set Jump Speed
	setJumpSpeed(INITIAL_JUMP_SPEED);

	// Set Slowdowns (Character Unique) [30 means 1 sec] 
	// [Parameter 2 default as false. If true, means set countdown to slowdown at the same time]
	setHorizontalSlowdown(2, true);
	setJumpSlowdown(30, true);
	setDefenseSlowdown(60, true);
	setAttackOneSlowdown(45, true);
	setSuperAttackSlowdown(150, true); // 5 secs
	setSuperChanelingSlowdown(0, true);

	num_of_pluses = 2;

	setIsHigherLevel(false);
}

void Character_CPP::do_action_move_right() {
	move(2, 0);
}

void Character_CPP::do_action_move_left() {
	move(-2, 0);
}

void Character_CPP::do_action_jump() {
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_CPP::do_action_defense() {
	// TO DO
}

void Character_CPP::do_action_attack_1() {

	for (int i = 0; i < num_of_pluses; i++) {
		Character_CPP_Plus* p = new Character_CPP_Plus(df::Vector(getPosition().getX() + (19 + 5 * i) * getPlayer()->getFacingRight(), 
			getPosition().getY() - (i + 3) * 1.5), (i + 3), 20);
		p->setAcceleration(df::Vector(0, 0.2));
		if (!getOnGroundStatus()) {
			p->setAcceleration(df::Vector(0, 0.5));
		}
	}
}

void Character_CPP::do_action_super_attack() {
	num_of_pluses++;
	if (num_of_pluses > 10)
		num_of_pluses = 10;
	setSuperAttacking(false);
}



void Character_CPP::flipSprite(PlayerCharacter::SpriteStatus sprite_status) {

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_CPP");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_CPP_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_CPP_error");
		break;
	default:
		break;
	}
}

