// Implementation of Character - C

// Game Include
#include "Character_C.h"
#include "Bullet.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_C::Character_C() {

	//link to ship sprite
	setSprite("Character_C");

	// Set Attack Related Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
	setSuperCastTime(2); // 2 secs
	
	// Set Jump Speed
	setJumpSpeed(INITIAL_JUMP_SPEED);

	// Set Slowdowns (Character Unique) [30 means 1 sec] 
	// [Parameter 2 default as false. If true, means set countdown to slowdown at the same time]
	setHorizontalSlowdown(2,true);
	setJumpSlowdown(30,true);
	setDefenseSlowdown(30,true);
	setAttackOneSlowdown(30,true);
	setSuperAttackSlowdown(900,true); // 30 secs
	setSuperChanelingSlowdown(60,true);

	setIsHigherLevel(false); //C is a lower level language, set for defend function

}

void Character_C::do_action_move_right(){
	move(1.5,0);
}

void Character_C::do_action_move_left(){
	move(-1.5, 0);
}

void Character_C::do_action_jump(){
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_C::do_action_defense(){
	// TO DO
}

void Character_C::do_action_attack_1(){
	Bullet* p = new Bullet(Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY()));
	p->setVelocity(df::Vector(2 * getPlayer()->getFacingRight(), 0));
}

void Character_C::do_action_super_attack(){
	// To do
}



void Character_C::flipSprite(PlayerCharacter::SpriteStatus sprite_status){

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_C");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_C_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_C_error");
		break;
	default:
		break;
	}
}

