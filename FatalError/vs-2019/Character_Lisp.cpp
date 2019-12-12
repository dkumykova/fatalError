// Implementation of Character - C

// Game Include
#include "Character_Lisp.h"
#include "Bullet.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_Lisp::Character_Lisp() {

	//link to ship sprite
	setSprite("Character_Lisp");

	// Set Attack Related Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
	setSuperDamage(80);
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

	setIsHigherLevel(false); //C is a lower level language, set for defend function

	//super_countdown = 10;
	super = new LispSuper();
	super->setActive(false);
	//super->setPNum(getPlayer()->getPlayerNum());

}

void Character_Lisp::do_action_move_right() {
	move(1.5, 0);
}

void Character_Lisp::do_action_move_left() {
	move(-1.5, 0);
}

void Character_Lisp::do_action_jump() {
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_Lisp::do_action_defense() {
	//implementation in player character
}

void Character_Lisp::do_action_attack_1() {
	Bullet* p = new Bullet(Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY()));
	p->setSprite("paren");
	p->setVelocity(df::Vector(2 * getPlayer()->getFacingRight(), 0));
}

void Character_Lisp::do_action_super_attack() {
	// To do
	//i want to use a countdown but might need to use a clock since i can't override eventhandler here
	super->setPNum(getPlayer()->getPlayerNum());
	LM.writeLog("Lisp super called");
	//setSprite("Character_Lisp_super");
	super->setPosition(Vector(getPosition().getX(), getPosition().getY()));
	super->setActive(true);

	
	//getAnimation().getSprite()->setColor(df::CYAN);
	//setSprite("Character_Lisp"); //set sprute back to normal


}



void Character_Lisp::flipSprite(PlayerCharacter::SpriteStatus sprite_status) {

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_Lisp");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_Lisp_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_Lisp_error");
		break;
	default:
		break;
	}
}

